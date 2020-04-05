#include "NumpyToCvMat.h"

cv::Mat NumpyToCvMat::numpyToMat(py::array_t<unsigned char> &image) {
    py::buffer_info buffer = image.request();
    cv::Mat result(buffer.shape[0], buffer.shape[1], CV_16UC(3), (unsigned char*) buffer.ptr);
    return result;
}

cv::Mat NumpyToCvMat::numpyToMatShortInt(py::array_t<unsigned short int> &image) {
    py::buffer_info buffer = image.request();
    cv::Mat result(buffer.shape[0], buffer.shape[1], CV_16UC(3), (unsigned short int*) buffer.ptr);
    return result;
}

cv::Mat NumpyToCvMat::numpyToMatShort(py::array_t<short int> &image) {
    py::buffer_info buffer = image.request();
    cv::Mat result(buffer.shape[0], buffer.shape[1], CV_16UC(3), (unsigned short int*) buffer.ptr);
    return result;
}