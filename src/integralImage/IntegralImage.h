#ifndef DET_INTEGRALIMAGE_H
#define DET_INTEGRALIMAGE_H


class IntegralImage {
private:
    int width;  // integral image width
    int height;  // integral image height
    cv::Mat II;  // integral image
    cv::Mat img;  // image (I)
    int imgChans;  // num. image channels (C)
    int cellSize;  // cell size -pixelsxpixels-
    int imgWidth;  // image width (Iv)
    int imgHeight;  // image height (Iu)
public:
    IntegralImage();  // constructor
    IntegralImage(int width, int height, int imgChans, int imgWidth, int imgHeight, int cellSize);  // constructor
    ~IntegralImage();  // destructor
    cv::Mat get_image();  // return the image pointer
    py::array_t<unsigned char> get_image_py();  // return the image pointer
    void release_image();  // release image
    void compute_image(int size);  // compute image from II
    void integral_image(const cv::Mat& img);  // compute integral image
    int get_image_width();  // return image size
    int get_image_height();  // return image size
};


#endif //DET_INTEGRALIMAGE_H
