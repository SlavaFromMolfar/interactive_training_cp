#include <opencv2/core/mat.hpp>
#include "cvMatToNumpy.h"


py::array_t<double> cvMatToNumpy::cvMatToNumpyDouble(const cv::Mat& array) {
        std::vector<ssize_t> shape(3);
        shape[0] = array.rows;
        shape[1] = array.cols;
        shape[2] = array.channels();
        return py::array_t<double>(
                shape,
                {shape[1] * shape[2] * sizeof(double), shape[2] * sizeof(double),
                 sizeof(double)},
                reinterpret_cast<const double *>(array.data));
}

py::array_t<unsigned short int> cvMatToNumpy::cvMatToNumpyUnsignedShortInt(const cv::Mat& array) {
        std::vector<ssize_t> shape(3);
        shape[0] = array.rows;
        shape[1] = array.cols;
        shape[2] = array.channels();
        return py::array_t<unsigned short int>(
                shape,
                {shape[1] * shape[2] * sizeof(unsigned short int), shape[2] * sizeof(unsigned short int),
                 sizeof(unsigned short int)},
                reinterpret_cast<const unsigned short int*>(array.data));
}

py::array_t<unsigned char> cvMatToNumpy::cvMatToNumpyInt(const cv::Mat& array) {
    py::array_t<unsigned char> input = py::array_t<unsigned char>({array.rows, array.cols, 3}, array.data);
    return py::array_t<unsigned char>(input);
}

