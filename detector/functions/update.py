import time

import cv2
import numpy as np

import detect


def update_positive_samples(frame, rectangle, classifier, random_ferns, train_samples, varphi):
    start_time = time.time()
    min_size = 20
    pos_label = 1.0

    cols, rows = classifier.get_object_size()

    height, width, channel = frame.shape

    for i in range(train_samples):
        ua = rectangle.y + round(varphi * rectangle.height * (np.random.uniform(-0.5, 0.5)))
        va = rectangle.x + round(varphi * rectangle.width * (np.random.uniform(-0.5, 0.5)))
        ub = rectangle.y + rectangle.height + round(varphi * rectangle.height * (np.random.uniform(-0.5, 0.5)))
        vb = rectangle.x + rectangle.width + round(varphi * rectangle.width * (np.random.uniform(-0.5, 0.5)))

        if va < 0:
            va = 0
        if ua < 0:
            ua = 0
        if vb >= height:
            vb = height - 1
        if ub >= width:
            ub = width - 1

        # print('pos: va - {}, ua - {}, vb - {}, ub - {}, vb - va > min_size - {}, ub - ua > min_size - {}'
        #       .format(va, ua, vb, ub, vb - va > min_size, ub - ua > min_size))

        if vb - va > min_size and ub - ua > min_size:
            patch = cv2.resize(frame[ua: ub, va: vb], (rows, cols))
            f_maps = detect.fern_maps(patch, random_ferns)
            classifier.update(f_maps, pos_label)
        end_time = time.time() - start_time
        print('update_pos_samples time - {}'.format(end_time))
