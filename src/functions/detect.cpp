
#include "../integralImage/IntegralImage.h"

void scanning_window(cv::Mat &fernMap, ClassifierSet* classifierSet, DetectionSet* detectionSet) {}

// object detection
void detect(ClassifierSet* clfrs, RandomFerns* RFs, py::array_t<unsigned char> &img, DetectionSet* detSet){
    // inputs:
    // prms: program parameters
    // clfrs: classifiers
    // RFs: fern features parameters
    // img: image (I)
    // detSet: detection set

    // parameters
    int minCell = 3;  // min. cell size
    int maxCell = 20;  // min. cell size
    int poolSize = RFs->get_pool_size();  // num. ferns parameters (R)

    // variables
    IntegralImage II;  // integral image
    int numMaxDets;  // number of detections
    int imgWidth,imgHeight;  // image size (Iv,Iu)
    int objHeight,objWidth;  // object size (Bu,Bv)

    // num. max. output detections
    numMaxDets = detSet->get_num_max_detections();

    auto mat = new NumpyToCvMat();
    auto image = mat->numpyToMat(img);

    // compute integral image
    II.integral_image(image);

    // image levels (scales)
    for (int cellSize=minCell; cellSize<maxCell; cellSize++){

        // temporal detections
        auto* dets = new DetectionSet;

        // compute image from II
        II.compute_image(cellSize);
        imgWidth = II.get_image_width();
        imgHeight = II.get_image_height();

        // ferns maps (convolve ferns with the image)
        cv::Mat fernMaps = fern_maps(II.get_image(), RFs);

        // test the classifiers
        scanning_window(fernMaps, clfrs, dets);

        // non maxima supression
        dets->non_maxima_supression();

        // scaling detection coordinates
        dets->scaling(cellSize);

        // adding detections
        detSet->add_detections(dets);

        // release image
        II.release_image();

        // release
        delete dets;
    }

    // non maxima supression
    detSet->non_maxima_supression();
};


void detectionFunctionInit(py::module &module) {
    module.def("detecting", &detect);
}