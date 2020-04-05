#ifndef DET_NUMPYTOCVMAT_H
#define DET_NUMPYTOCVMAT_H

class NumpyToCvMat {
public:
    cv::Mat numpyToMat(py::array_t<unsigned char> &image);
    cv::Mat numpyToMatShortInt(py::array_t<unsigned short int> &image);
    cv::Mat numpyToMatShort(py::array_t<short int> &image);
};

#endif //DET_NUMPYTOCVMAT_H
