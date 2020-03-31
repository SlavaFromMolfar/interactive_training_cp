#ifndef DET_CLASSIFIER_H
#define DET_CLASSIFIER_H

#include <opencv2/core.hpp>
#include <pybind11/numpy.h>

class Classifier {
private:
    float beta;  // classifier threshold (beta)
    int numBins;  // number of histogram bins
    cv::Mat data;  // classifier data
    int numFerns;  // number of random ferns (J)
    int objWidth;  // object image width (Bv)
    int objHeight;  // object image height (Bu)
    cv::Mat posHstms;  // positive fern histograms
    cv::Mat negHstms;  // negative fern histograms
    cv::Mat ratHstms;  // ratio of fern histograms
public:
    Classifier();
    Classifier(float beta, int numBins, int numFerns, int objWidth, int objHeight);
    ~Classifier();
    void print();  // print classifier parameters
    cv::Mat objModel;  // object model (image)
    cv::Mat get_data();  // pointer to classifier data
    int get_num_ferns();  // get num. random ferns (J)
    float get_threshold();  // return classifier threshold (beta)
    cv::Mat get_posHstms();  // pointer to positive fern distributions
    pybind11::array_t<double> get_posHstms_np();  // pointer to positive fern distributions
    cv::Mat get_negHstms();  // pointer to negative fern distributions
    pybind11::array_t<double> get_negHstms_np();  // pointer to negative fern distributions
    cv::Mat get_ratHstms();  // pointer to ratio of fern distributions
    pybind11::array_t<double> get_ratHstms_np();  // pointer to ratio of fern distributions
    void set_threshold(float beta);  // set detector threshold (beta)
    void update(cv::Mat &mapx, float y);  // update the object classifier
    void set_object_size(int Bu, int Bv);  // set object size (Bu,Bv)
    void get_object_size(int& Bu, int& Bv);  // return object size (Bu,Bv)
    void compute(int J, int R, int M, int S);  // compute the object classifier
};


#endif //DET_CLASSIFIER_H
