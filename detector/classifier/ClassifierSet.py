from classifier.Classifier import Classifier


class ClassifierSet:
    def __init__(self, number_classifiers=0, max_number_classifiers=30):
        self.__number_classifiers = number_classifiers
        self.__max_number_classifiers = max_number_classifiers

        self.__classifier_set = [Classifier() for i in range(max_number_classifiers)]

    def __str__(self):
        return '\n'.join(str(item) for item in self.__classifier_set)

    @property
    def number_classifiers(self):
        return self.__number_classifiers

    @number_classifiers.setter
    def number_classifiers(self, num):
        self.__number_classifiers = num

    @property
    def max_number_classifiers(self):
        return self.__max_number_classifiers

    @property
    def classifier_set(self):
        return self.__classifier_set

    def get_classifier(self, index):
        classifier = self.classifier_set[index]
        return classifier

    def set_number_classifiers(self, number):
        self.number_classifiers = number


if __name__ == '__main__':
    set = ClassifierSet()
    print(set)
