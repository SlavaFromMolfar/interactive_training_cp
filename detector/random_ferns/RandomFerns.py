import numpy as np
from numpy import random as rnd


class RandomFerns:
    def __init__(self, pool_size=5, fern_size=4, num_feats=5, fern_depth=3):
        self.__pool_size = pool_size
        self.__fern_size = fern_size
        self.__num_feats = num_feats
        self.__fern_depth = fern_depth

        self.__data = None

    @property
    def pool_size(self):
        return self.__pool_size

    @pool_size.setter
    def pool_size(self, size):
        self.__pool_size = size

    @property
    def fern_size(self):
        return self.__fern_size

    @fern_size.setter
    def fern_size(self, size):
        self.__fern_size = size

    @property
    def num_feats(self):
        return self.__num_feats

    @num_feats.setter
    def num_feats(self, num):
        self.__num_feats = num

    @property
    def fern_depth(self):
        return self.__fern_depth

    @fern_depth.setter
    def fern_depth(self, depth):
        self.__fern_depth = depth

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        self.__data = data

    def compute(self, r, m, s, c):
        # r: num. ferns parameters (pool size)
        # m: num. binary features
        # s: fern size
        # c: num. image channels (e.g color channels
        self.pool_size = r
        self.num_feats = m
        self.fern_size = s
        self.fern_depth = c

        print('ps - {}, nf - {}, fs - {}, fd - {}'.format(self.pool_size, self.num_feats, self.fern_size,
                                                          self.fern_depth))

        temp = []

        for i in range(r):
            for j in range(m):
                ua = np.floor(s * rnd.random())
                va = np.floor(s * rnd.random())
                ca = np.floor(c * rnd.random())

                ub = np.floor(s * rnd.random())
                vb = np.floor(s * rnd.random())
                cb = np.floor(c * rnd.random())

                row = [ua, va, ca, ub, vb, cb]
                temp.append(row)

        self.data = np.vstack(temp)
        self.data = self.data.reshape(r, m, 6)
        return self.data

    def print(self):
        print('\n*********************************************************')
        print('* Random Fern Parameters : ')
        print('* num. ferns parameters: {}'.format(self.pool_size))
        print('* num. binary features: {}'.format(self.num_feats))
        print('* fern size: {} x {}'.format(self.fern_size, self.fern_size))
        print('* fern depth: {}'.format(self.fern_depth))
        print('*********************************************************\n')

#
# if __name__ == '__main__':
#     rf = RandomFerns()
#     comp = rf.compute(10, 10, 10, 3)
#     print(comp)
#     rf.print()