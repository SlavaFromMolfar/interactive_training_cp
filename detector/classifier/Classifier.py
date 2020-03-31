import time

import numpy as np
from numpy import random as rnd


class Classifier:
    def __init__(self, beta=0.5, num_bins=128, num_ferns=100, object_width=24, object_height=24):
        self.__beta = beta
        self.__num_bins = num_bins
        self.__num_ferns = num_ferns
        self.__object_width = object_width
        self.__object_height = object_height

        self.__data = np.ones((self.__num_ferns, self.__num_bins), dtype=float)
        self.__pos_hstms = None
        self.__neg_hstms = None
        self.__rat_hstms = None

        self.__object_model = None

    def __str__(self):
        return 'threshold - {}, num_bins - {}, num_ferns - {}, object_width - {}, object_height - {}, \ndata - \n{},' \
               ' \npos_hstms - \n{}, \nneg_hstms - \n{}, \nrat_hstms - \n{}'\
            .format(self.threshold, self.num_bins, self.num_ferns, self.object_width, self.object_height, self.data,
                    self.pos_hstms, self.neg_hstms, self.rat_hstms)

    @property
    def object_model(self):
        return self.__object_model

    @object_model.setter
    def object_model(self, model):
        self.__object_model = model

    @property
    def threshold(self):
        return self.__beta

    @threshold.setter
    def threshold(self, beta):
        self.__beta = beta

    @property
    def num_bins(self):
        return self.__num_bins

    @num_bins.setter
    def num_bins(self, num_bins):
        self.__num_bins = num_bins

    @property
    def object_height(self):
        return self.__object_height

    @object_height.setter
    def object_height(self, object_height):
        self.__object_height = object_height

    @property
    def object_width(self):
        return self.__object_width

    @object_width.setter
    def object_width(self, object_width):
        self.__object_width = object_width

    def get_object_size(self):
        return self.object_height, self.object_width

    def set_object_size(self, object_height, object_width):
        self.object_height = object_height
        self.object_width = object_width

    @property
    def num_ferns(self):
        return self.__num_ferns

    @num_ferns.setter
    def num_ferns(self, num_ferns):
        self.__num_ferns = num_ferns

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        self.__data = data

    @property
    def pos_hstms(self):
        return self.__pos_hstms

    @pos_hstms.setter
    def pos_hstms(self, pos):
        self.__pos_hstms = pos

    @property
    def neg_hstms(self):
        return self.__neg_hstms

    @neg_hstms.setter
    def neg_hstms(self, neg):
        self.__neg_hstms = neg

    @property
    def rat_hstms(self):
        return self.__rat_hstms

    @rat_hstms.setter
    def rat_hstms(self, rat):
        self.__rat_hstms = rat

    # TODO: rewrite in TensorFlow
    def compute(self, j, r, m, s):
        # j: num. random ferns
        # r: fern pool size
        # m: num. binary features
        # s: fern size
        start_time = time.time()

        self.num_ferns = j
        self.num_bins = 2 ** m()

        self.data = np.ndarray((j, 3, 1), dtype=int)
        data_ptr = self.data.flat

        for i in range(j):
            u = np.floor((self.object_height - s()) * rnd.random())
            v = np.floor((self.object_width - s()) * rnd.random())
            w = np.floor(r() * rnd.random())

            data_ptr[i * 3 + 0] = u
            data_ptr[i * 3 + 1] = v
            data_ptr[i * 3 + 2] = w

            self.pos_hstms = np.full((self.num_ferns, self.num_bins, 1), dtype=float, fill_value=1.0)
            self.neg_hstms = np.full((self.num_ferns, self.num_bins, 1), dtype=float, fill_value=1.0)
            self.rat_hstms = np.full((self.num_ferns, self.num_bins, 1), dtype=float, fill_value=0.5)

        end_time = (time.time() - start_time)
        print('end time - {}'.format(end_time))

        return data_ptr

    # TODO: rewrite in TensorFlow
    def update(self, fern_maps, labels):
        fern_maps_ptr = fern_maps.flat

        for i in range(self.num_ferns):
            z = np.random.choice(fern_maps_ptr)

            if labels == 1.0:
                self.pos_hstms[i, z] += 1
            if labels == -1.0:
                self.neg_hstms[i, z] += 1

            self.rat_hstms[i, z] = self.pos_hstms[i, z] / (self.pos_hstms[i, z] + self.neg_hstms[i, z])

    def print(self):
        print('\n*********************************************************')
        print('* Classifier Parameters : ')
        print('* object size - {}x{}'.format(self.object_height, self.object_width))
        print('num. random ferns - {}'.format(self.num_ferns))
        print('* classifier threshold - {}'.format(self.threshold))
        print('*********************************************************\n')
