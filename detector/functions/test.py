
import detect


def test_step(classifier_set, random_ferns, frame, detection_set):
    number_classifiers = classifier_set.get_num_classifiers()

    if number_classifiers > 0:
        detect.detecting(classifier_set, random_ferns, frame, detection_set)