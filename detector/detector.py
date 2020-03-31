import cv2

import concurrent.futures

from classifier.ClassifierSet import ClassifierSet
from functions.train import train_step
from parameters.Parameters import Parameters
from random_ferns.RandomFerns import RandomFerns

import detect

flag_drawing = False
flag_training = False
flag_detection = False
rectangle = None


def mouse_callback(event, x, y, flags, param):
    global rectangle, flag_drawing, flag_training
    if event == cv2.EVENT_LBUTTONDOWN:
        rectangle = [x, y, 1, 1]
        flag_drawing = True
    if event == cv2.EVENT_MOUSEMOVE:
        if flag_drawing:
            rectangle[2] = x - rectangle[0]
            rectangle[3] = y - rectangle[1]
    if event == cv2.EVENT_LBUTTONUP:
        if rectangle[2] < 0:
            rectangle[0] += rectangle[2]
            rectangle[2] *= -1
        if rectangle[3] < 0:
            rectangle[1] += rectangle[3]
            rectangle[3] *= -1
        flag_drawing = False
        flag_training = True


if __name__ == '__main__':

    cap = cv2.VideoCapture(0)
    cv2.namedWindow('Video')

    # Parameters initialization
    parameters = Parameters()
    parameters.fun_load()
    parameters.fun_print()

    img_width = parameters.get_image_width()
    img_height = parameters.get_image_height()

    # Random ferns initialization
    random_ferns = detect.RandomFerns()
    random_ferns.compute(parameters.get_pool_size(), parameters.get_num_features(), parameters.get_fern_size(),
                         parameters.get_num_image_channels())
    random_ferns.print()

    # Classifier set initialization
    classifier_set = ClassifierSet()

    while True:
        ret, frame = cap.read()

        cv2.imshow('Video', frame)

        with(concurrent.futures.ThreadPoolExecutor()) as executor:
            executor.map(cv2.setMouseCallback('Video', mouse_callback))

        if flag_drawing:
            rect = cv2.rectangle(img=frame, pt1=(rectangle[0], rectangle[1]),
                                 pt2=(rectangle[0] + rectangle[2], rectangle[1] + rectangle[3]),
                                 color=(0, 255, 0), thickness=2)
            cv2.imshow('Video', rect)

        if flag_training:
            detect.listToCvRect(rectangle)
            flag_training = False
            flag_detection = True
            train_step(parameters, classifier_set, random_ferns, frame, rectangle)

        if cv2.waitKey(1) & 0xff is ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
