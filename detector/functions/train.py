import cv2


def train_classifier(parameters, classifier, random_ferns, frame, rectangle):
    varphi = parameters.get_image_shift()
    train_samples = parameters.get_num_train_samples()
    object_model_size = 100

    ratio = float(rectangle[2] / rectangle[3])
    object_height = parameters.get_object_height()
    object_width = round(ratio * object_height)

    classifier.set_object_size(object_height, object_width)
    classifier.threshold = parameters.get_threshold()

    classifier.compute(parameters.get_num_ferns(), random_ferns.pool_size, random_ferns.num_feats,
                       random_ferns.fern_size)
    classifier.print()
    # cv2.waitKey(0)

    object_model = cv2.resize(frame[rectangle[1]:rectangle[1] + rectangle[3],
                              rectangle[0]: rectangle[0] + rectangle[2]],
                              (object_model_size, object_model_size))
    classifier.object_model = object_model

    # TODO: replace with c++
    # update_positive_samples(frame, rectangle, classifier, random_ferns, train_samples, varphi)

    # update_negative_samples(object_model, rectangle, classifier, random_ferns, train_samples, varphi)


def train_step(parameters, classifier_set, random_ferns, frame, rectangle):
    num_classifiers = classifier_set.number_classifiers
    max_num_classifiers = classifier_set.max_number_classifiers

    if num_classifiers >= max_num_classifiers:
        print('The maximum number of classifiers has been achieved')
        return

    current_classifier = classifier_set.get_classifier(num_classifiers)

    num_classifiers += 1

    print('\n*********************************************************')
    print('new classifier: {}'.format(num_classifiers))
    print('*********************************************************')

    classifier_set.set_number_classifiers(num_classifiers)

    train_classifier(parameters, current_classifier, random_ferns, frame, rectangle)
