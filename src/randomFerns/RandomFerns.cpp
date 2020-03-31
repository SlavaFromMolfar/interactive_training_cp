#include "RandomFerns.h"

RandomFerns::RandomFerns() {
    // initialize default parameters
    this->poolSize = 5;  // num. ferns parameters (R)
    this->fernSize = 4;  // fern size (S)
    this->numFeats = 5;  // num. binary features per fern (M)
    this->fernDepth = 3;  // fern depth (num. image channels (C))
}

RandomFerns::RandomFerns(int poolSize, int numFeats, int fernSize, int fernDepth) {
    this->poolSize = poolSize;
    this->numFeats = numFeats;
    this->fernSize = fernSize;
    this->fernDepth = fernDepth;
}

RandomFerns::~RandomFerns() = default;

// get num. ferns parameters (R)
int RandomFerns::get_pool_size(){
    return this->poolSize;
}

// get num. binary features (M)
int RandomFerns::get_num_features(){
    return this->numFeats;
}

// get fern size (S)
int RandomFerns::get_fern_size(){
    return this->fernSize;
}

// get fern depth (image channels (C))
int RandomFerns::get_fern_depth(){
    return this->fernDepth;
}

// get ferns parameters data
cv::Mat RandomFerns::get_data(){
    return this->data;
}

py::array_t<unsigned char> RandomFerns::get_data_np() {
    py::array_t<unsigned char > result = py::array_t<unsigned char>({ this->data.rows, this->data.cols, 3}, this->data.data);
    return result;
}

// compute random ferns
void RandomFerns::compute(int R, int M, int S, int C){
    // inputs:
    // R: num. ferns parameters (pool size)
    // M: num. binary features
    // S: fern size
    // C: num. image channels (e.g color channels)
    // variables
    int ua,va,ca,ub,vb,cb;

    // set random ferns values
    this->poolSize = R;  // num. ferns parameters
    this->numFeats = M;  // num. binary features
    this->fernSize = S;  // spatial fern size
    this->fernDepth = C;  // fern depth (num. image channels)

    // allocate data
    this->data = cv::Mat(R, M, CV_8UC(6));

    // pointer to ferns data
    auto *dataPtr = (unsigned char*)(data.data);

    // random ferns parameters
    for (int r = 0; r<R; r++ ){
        for (int m = 0; m<M; m++){
            // feature a coordinates
            ua = floor(S*((double)rand()/RAND_MAX));
            va = floor(S*((double)rand()/RAND_MAX));
            ca = floor(C*((double)rand()/RAND_MAX));

            // feature b coordinates
            ub = floor(S*((double)rand()/RAND_MAX));
            vb = floor(S*((double)rand()/RAND_MAX));
            cb = floor(C*((double)rand()/RAND_MAX));

            // save
            *(dataPtr + r*M*6 + m*6 + 0) = ua;
            *(dataPtr + r*M*6 + m*6 + 1) = va;
            *(dataPtr + r*M*6 + m*6 + 2) = ca;
            *(dataPtr + r*M*6 + m*6 + 3) = ub;
            *(dataPtr + r*M*6 + m*6 + 4) = vb;
            *(dataPtr + r*M*6 + m*6 + 5) = cb;
        }
    }
}

void RandomFerns::print() {
    std::cout << "\n*********************************************************" << std::endl;
    std::cout << "* Random Fern Parameters : " << std::endl;
    std::cout << "* num. ferns parameters -> " << this->poolSize << std::endl;
    std::cout << "* num. binary features -> " << this->numFeats << std::endl;
    std::cout << "* fern size ->  " << this->fernSize << "x" << this->fernSize << std::endl;
    std::cout << "* fern depth ->  " << this->fernDepth << std::endl;
    std::cout << "*********************************************************\n" << std::endl;
}
