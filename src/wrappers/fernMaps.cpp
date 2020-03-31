#include "../wrappers/NumpyToCvMat.h"
//#include "../wrappers/cvMatToNumpy.cpp"

// fern maps
cv::Mat fern_maps(const cv::Mat &img, RandomFerns* RFs){
    // inputs:
    // img: image sample x
    // RFs: shared random ferns

    // detector parameters
    int imgChans = img.channels();  // num. image channels (C)
    int imgWidth = img.cols;  // image width (Iv)
    int imgHeight = img.rows;  // image height (Iu)
    int poolSize = RFs->get_pool_size();  // num. fern features parameters (R)
    int fernSize = RFs->get_fern_size();  // fern size (S)
    int numFeats = RFs->get_num_features();  // num. features per fern (M)
    cv::Mat fernsData = RFs->get_data();  // pointer to random ferns

    // create ferns maps for image sample x
    cv::Mat fernMaps = cv::Mat(cvSize(imgWidth, imgHeight), CV_16UC(poolSize));

    // pointers
    auto *imgPtr = (unsigned char*)(img.data);  // image data
    auto *fernsPtr = (unsigned char*)(fernsData.data);  // fern parameters data
    auto *mapsPtr = (unsigned short*)(fernMaps.data);  // fern maps data

    // variables
    float xa,xb; // image pixel values
    int tmp1 = numFeats*6;  // tmp. variable
    int tmp5 = imgWidth*poolSize;  // tmp. variable
    int tmp4 = imgWidth*imgChans;  // tmp. variable
    int tmp2,tmp3;  // tmp. variables
    int vm,um,cm,z;  // feature parameters (u,v,c) and fern output (z)

    // scanning
    for (int u=0; u<imgHeight-fernSize; u++) {
        for (int v=0; v<imgWidth-fernSize; v++) {
            for (int r=0; r<poolSize; r++){

                // temp. variable
                tmp2 = r*tmp1;

                // fern output
                z = 0;

                // fern features
                for (int m=0; m<numFeats; m++){

                    // temp. variable
                    tmp3 = tmp2 + m*6;

                    // point a coordinates (u,v,c)
                    um = u + (int)*(fernsPtr + tmp3 + 0);
                    vm = v + (int)*(fernsPtr + tmp3 + 1);
                    cm =     (int)*(fernsPtr + tmp3 + 2);

                    // image pixel value in location a
                    xa = *(imgPtr + um*tmp4 + vm*imgChans + cm);

                    // point b coordinates (u,v,c)
                    um = u + (int)*(fernsPtr + tmp3 + 3);
                    vm = v + (int)*(fernsPtr + tmp3 + 4);
                    cm =     (int)*(fernsPtr + tmp3 + 5);

                    // image pixel value in location b
                    xb = *(imgPtr + um*tmp4 + vm*imgChans + cm);

                    // update fern output
                    //z += (1 << m) & (0 - (xa > xb));
                    z += (1 << m) & (0 - (xa > xb + 0.01));
                }

                // fern output
                *(mapsPtr + u*tmp5 + v*poolSize + r) = z;
            }
        }
    }
    return fernMaps;
};


//py::array_t<unsigned short int> fern_maps_np(py::array_t<unsigned char> &image, RandomFerns* randomFerns) {
//    cv::Mat img = NumpyToCvMat::numpyToMat(image);
//    cv::Mat fern_map = fern_maps(img, randomFerns);
//    py::array_t<unsigned short int> result = cvMatToNumpyUnsignedShortInt(fern_map);
//    return result;
//}


void fernMaps(py::module &module) {
//    module.def("fern_maps", &fern_maps_np);
}
