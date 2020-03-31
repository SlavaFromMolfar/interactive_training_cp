#ifndef DET_RANDOMFERNS_H
#define DET_RANDOMFERNS_H

class RandomFerns {
private:
    cv::Mat data;  // ferns parameters data
    int poolSize;  // num. random ferns parameters (R)
    int numFeats;  // num. binary features per fern (M)
    int fernSize;  // spatial fern size (S)
    int fernDepth;  // num. image channels (C)
public:
    RandomFerns();  // constructor
    RandomFerns(int poolSize, int numFeats, int fernSize, int fernDepth);  // constructor
    ~RandomFerns();  // destructor
    void print();  // print fern parameters
    cv::Mat get_data();  // get ferns data
    pybind11::array_t<unsigned char> get_data_np();
    int get_pool_size();  // return num. ferns paramaters (R)
    int get_fern_size();  // return fern size (S)
    int get_fern_depth();  // return fern depth (C)
    int get_num_features();  // return num. binary features (M)
    void compute(int R, int M, int S, int C);  // create random ferns
};


#endif //DET_RANDOMFERNS_H
