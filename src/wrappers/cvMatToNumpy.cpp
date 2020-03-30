#include <opencv2/core/mat.hpp>


py::array_t<double> cvMatToNumpyDouble(const cv::Mat& array) {
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

py::array_t<unsigned char> cvMatToNumpyInt(const cv::Mat& array) {
    py::array_t<unsigned char> input = py::array_t<unsigned char>({array.rows, array.cols, 3}, array.data);
    return py::array_t<unsigned char>(input);
}

