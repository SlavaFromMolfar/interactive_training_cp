#include "Classifier.h"

Classifier::Classifier() {
    // initialize default parameters
    this->beta = 0.5;  // classifier threshold (beta)
    this->numBins = 128;  // num. histogram bins
    this->numFerns = 100;  // num. random ferns (J)
    this->objWidth = 24;  // object width (Bv)
    this->objHeight = 24;  // object height (Bu)
}

Classifier::~Classifier() = default;

Classifier::Classifier(float beta, int numBins, int numFerns, int objWidth, int objHeight) {
    this->beta = beta;
    this->numBins = numBins;
    this->numFerns = numFerns;
    this->objWidth = objWidth;
    this->objHeight = objHeight;
}

// get threshold (beta)
float Classifier::get_threshold(){
    return this->beta;
}

// set threshold (beta)
void Classifier::set_threshold(float thr){
    // inputs:
    // thr: classifier threshold
    this->beta = thr;
}

// set object size (Bu,Bv)
void Classifier::set_object_size(int Bu, int Bv){
    // inputs:
    // Bu: object size (image) in u (y)
    // Bv: object size (image) in v (x)
    this->objHeight = Bu;
    this->objWidth = Bv;
}

// get object size (Bu,Bv)
void Classifier::get_object_size(int& Bu, int& Bv){
    // inputs:
    // Bu: object size (image) in u (y)
    // Bv: object size (image) in v (x)
    Bu = this->objHeight;
    Bv = this->objWidth;
}

// get num. random ferns (J)
int Classifier::get_num_ferns(){
    return this->numFerns;
}

// get classifier data
cv::Mat Classifier::get_data(){
    return this->data;
}

// get positive fern distributions
cv::Mat Classifier::get_posHstms(){
    return this->posHstms;
}

py::array_t<double> Classifier::get_posHstms_np(){
    py::array_t<double> result = cvMatToNumpyDouble(this->posHstms);
    return result;
}

// get negative fern distributions
cv::Mat Classifier::get_negHstms(){
    return this->negHstms;
}

py::array_t<double> Classifier::get_negHstms_np() {
    py::array_t<double> result = cvMatToNumpyDouble(this->negHstms);
    return result;
}

// get ratio of fern distributions
cv::Mat Classifier::get_ratHstms(){
    return this->ratHstms;
}

py::array_t<double> Classifier::get_ratHstms_np(){
    py::array_t<double> result = cvMatToNumpyDouble(this->ratHstms);
    return result;
}

// compute the classifier
void Classifier::compute(int J, int R, int M, int S){
    // inputs:
    // J: num. random ferns
    // R: fern pool size
    // M: num. binary features
    // S: fern size

    // variables
    int u,v,w;  // fern location (u,v) and fern parameter (omega)
    int Bu = this->objHeight;  // object height
    int Bv = this->objWidth;  // object width

    // set the number of ferns and histogram bins
    this->numFerns = J;
    this->numBins = (int)pow(2, M);

    // classifier data (random ferns parameters)
    this->data = cv::Mat(J, 3, CV_8UC1);

    // pointer to data
    auto *dataPtr = (unsigned char*)(this->data.data);

    // random ferns
    for (int j = 0; j<J; j++){
        // fern parameters
        u = floor((Bu-S)*((double)rand()/RAND_MAX));
        v = floor((Bv-S)*((double)rand()/RAND_MAX));
        w = floor(R*((double)rand()/RAND_MAX));

        // save
        *(dataPtr + j*3 + 0) = u;  // fern location in u
        *(dataPtr + j*3 + 1) = v;  // fern location in v
        *(dataPtr + j*3 + 2) = w;  // features parameters (omega)
    }

    // distributions
    this->posHstms = cv::Mat(this->numFerns, this->numBins, CV_32FC1, cv::Scalar::all(1.0));
    this->negHstms = cv::Mat(this->numFerns, this->numBins, CV_32FC1, cv::Scalar::all(1.0));
    this->ratHstms = cv::Mat(this->numFerns, this->numBins, CV_32FC1, cv::Scalar::all(0.5));
}

// update the classifier
void Classifier::update(cv::Mat &fernMaps, float label){
    // inputs:
    // fernMaps: ferns outputs over an image sample x
    // label: class label (y = {+1,-1}) for the sample x

    // variables
    int u,v,w,z;  // fern location (u,v), fern parameters (omega), fern output (z)
    float pos,neg;  // positive and negative values

    // fern map size
    int poolSize = fernMaps.channels();  // pool size (num. fern features parameters)
    int imgWidth = fernMaps.cols;  // image width (Iv)
    int imgHeight = fernMaps.rows;  // image height (Iu)

    // pointer to classifier data, ferns maps, and positive, negative and ratio ferns distributions
    auto *dataPtr = (unsigned char*)(this->data.data);
    auto *mapsPtr = (unsigned short*)(fernMaps.data);
    auto* posPtr = this->posHstms.ptr<float>(0);
    auto* negPtr = this->negHstms.ptr<float>(0);
    auto* ratPtr = this->ratHstms.ptr<float>(0);

    // update random ferns
    for (int j=0; j<this->numFerns; j++){

        // fern parameters
        u = (int)*(dataPtr + j*3 + 0);  // location u
        v = (int)*(dataPtr + j*3 + 1);  // location v
        w = (int)*(dataPtr + j*3 + 2);  // features parameters

        // fern output
        z = (int)*(mapsPtr + u*imgWidth*poolSize + v*poolSize + w);

        // update positive fern distribution
        if (label==1.0) {
            *(posPtr + j*this->numBins + z)+= 1.0;
        }

        // update negative fern distribution
        if (label==-1.0) {
            *(negPtr + j*this->numBins + z)+= 1.0;
        }

        // ratio fern distribution
        pos = *(posPtr + j*this->numBins + z);
        neg = *(negPtr + j*this->numBins + z);
        std::cout << "pos: " << pos << " neg: " << neg << " pos/(pos+neg): " << pos / (pos + neg) << std::endl;
        *(ratPtr + j*this->numBins + z) = pos/(pos+neg);
    }
}

// print classifier parameters
void Classifier::print(){
    std::cout << "\n*********************************************************" << std::endl;
    std::cout << "* Classifier Parameters : " << std::endl;
    std::cout << "* object size ->  " << this->objHeight << "x" << this->objWidth << std::endl;
    std::cout << "* num. random ferns -> " << this->numFerns << std::endl;
    std::cout << "* classifier threshold -> " << this->beta << std::endl;
    std::cout << "*********************************************************\n" << std::endl;
}