import time

import cv2
import numpy as np

import detect


def update_negative_samples(frame, rectangle, classifier, random_ferns, train_samples, varphi):
    start_time = time.time()
    min_size = 20
    neg_label = -1.0

    cols, rows = classifier.get_object_height(), classifier.get_object_width()

    height, width, channel = frame.shape

    for i in range(train_samples):
        v1 = np.round(rows * np.random.uniform())
        v2 = np.round(rows * np.random.uniform())
        u1 = np.round(cols * np.random.uniform())
        u2 = np.round(cols * np.random.uniform())

        va = min(v1, v2)
        vb = max(v1, v2)
        ua = min(u1, u2)
        ub = max(u1, u2)

        if va < 0:
            va = 0
        if ua < 0:
            ua = 0
        if vb >= rows:
            vb = rows - 1
        if ub >= cols:
            ub = cols - 1

        if vb - va > min_size and ub - ua > min_size:
                patch = cv2.resize(frame[va: vb, ua: ub], (width, height))

                f_map = detect.fern_maps(patch, random_ferns)
                classifier.update(f_map, neg_label)
        end_time = time.time() - start_time
        print('update_neg_samples time - {}'.format(end_time))


def update_positive_samples(frame, rectangle, classifier, random_ferns, train_samples, varphi):
    start_time = time.time()
    min_size = 20
    pos_label = 1.0

    cols, rows = classifier.get_object_height(), classifier.get_object_width()

    height, width, channel = frame.shape

    for i in range(train_samples):
        ua = rectangle[1] + round(varphi * rectangle[3] * (np.random.uniform(-0.5, 0.5)))
        va = rectangle[0] + round(varphi * rectangle[2] * (np.random.uniform(-0.5, 0.5)))
        ub = rectangle[1] + rectangle[3] + round(varphi * rectangle[3] * (np.random.uniform(-0.5, 0.5)))
        vb = rectangle[0] + rectangle[2] + round(varphi * rectangle[2] * (np.random.uniform(-0.5, 0.5)))

        if va < 0:
            va = 0
        if ua < 0:
            ua = 0
        if vb >= height:
            vb = height - 1
        if ub >= width:
            ub = width - 1

        if vb - va > min_size and ub - ua > min_size:
            patch = cv2.resize(frame[ua: ub, va: vb], (rows, cols))
            f_maps = detect.fern_maps(patch, random_ferns)
            classifier.update(f_maps, pos_label)
        end_time = time.time() - start_time
        print('update_pos_samples time - {}'.format(end_time))


def train_classifier(parameters, classifier, random_ferns, frame, rectangle):
    varphi = parameters.get_image_shift()
    train_samples = parameters.get_num_train_samples()
    object_model_size = 100

    ratio = float(rectangle[2] / rectangle[3])
    object_height = parameters.get_object_height()
    object_width = round(ratio * object_height)

    classifier.set_object_size(object_height, object_width)
    classifier.beta = parameters.get_threshold()

    classifier.compute(parameters.get_num_ferns(), random_ferns.getPoolSize(), random_ferns.getNumFeats(),
                       random_ferns.getFernSize())
    classifier.print()

    object_model = cv2.resize(frame[rectangle[1]:rectangle[1] + rectangle[3],
                              rectangle[0]: rectangle[0] + rectangle[2]],
                              (object_model_size, object_model_size))
    classifier.set_object_model(object_model)

    update_positive_samples(frame, rectangle, classifier, random_ferns, train_samples, varphi)

    update_negative_samples(object_model, rectangle, classifier, random_ferns, train_samples, varphi)


def train_step(parameters, classifier_set, random_ferns, frame, rectangle):
    num_classifiers = classifier_set.get_num_classifiers()
    max_num_classifiers = classifier_set.get_num_max_classifiers()

    if num_classifiers >= max_num_classifiers:
        print('The maximum number of classifiers has been achieved')
        return

    current_classifier = classifier_set.get_classifier(num_classifiers)

    num_classifiers += 1

    print('\n*********************************************************')
    print('new classifier: {}'.format(num_classifiers))
    print('*********************************************************')

    classifier_set.set_num_classifiers(num_classifiers)

    train_classifier(parameters, current_classifier, random_ferns, frame, rectangle)
