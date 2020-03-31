#include "NumpyToCvMat.h"

static cv::Mat NumpyToCvMat::numpyToMat(py::array_t<unsigned char> &image) {
    py::buffer_info buffer = image.request();
    cv::Mat result(buffer.shape[0], buffer.shape[1], CV_16UC(3), (unsigned char*) buffer.ptr);
    return result;
}