import detect


if __name__ == '__main__':
    random_fern = detect.RandomFerns()
    random_fern.compute(5, 5, 5, 5)
    random_fern.print()
