#ifndef DET_CMMATTONUMPY_H
#define DET_CMMATTONUMPY_H

class cvMatToNumpy {
public:
    py::array_t<double> cvMatToNumpyDouble(const cv::Mat& array);
    py::array_t<unsigned short int> cvMatToNumpyUnsignedShortInt(const cv::Mat& array);
    py::array_t<unsigned char> cvMatToNumpyInt(const cv::Mat& array);
};

#endif //DET_CMMATTONUMPY_H
