import detect

if __name__ == '__main__':
    classifier = detect.Classifier(0.5, 128, 100, 24, 24)
    print(classifier.get_pos_np())
    print(classifier.get_neg_np())
    print(classifier.get_rat_np())
    classifier.compute(5, 5, 5, 5)
    print(classifier.get_pos_np())
    print(classifier.get_neg_np())
    print(classifier.get_rat_np())
    classifier.print()
