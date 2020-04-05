

# TODO: replace with c++ realization
def detect(classifier_set, random_ferns, frame, detection_set):
    pass


def test_step(classifier_set, random_ferns, frame, detection_set):
    number_classifiers = classifier_set.get_num_classifiers()

    if number_classifiers > 0:
        detect(classifier_set, random_ferns, frame, detection_set)