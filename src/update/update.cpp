#include <pybind11/pybind11.h>
#include "../wrappers/classifier/Classifier.h"
#include "../randomFerns/RandomFerns.h"

namespace py = pybind11;


// update classifier using positive smaples
void fun_update_positive_samples(const cv::Mat &img, CvRect rec, Classifier* clfr, RandomFerns* RFs, int updSamps, float varphi){
    // inputs:
    // img: image (I)
    // rec: image box
    // clfr: classifier
    // RFs: fern parameters
    // updSamps: num. new (updating) samples (Nu)
    // varphi: image shift rate

    // parameters
    int minSize = 20;  // min. image size
    float posLabel = 1.0; // sample label (y=+1)

    // variables
    CvRect newRec;  // new bounding box
    int ua,va,ub,vb;  // image coordinates
    int objHeight,objWidth;  // object heigth and width (Bu,Bv)

    // object size
    clfr->get_object_size(objHeight, objWidth);

    // updating positive samples
    for (int iter=0; iter<updSamps; iter++){

        // new rectangle coordinates
        ua = rec.y + round(varphi*rec.height*((float)rand()/RAND_MAX - 0.5));
        va = rec.x + round(varphi*rec.width*((float)rand()/RAND_MAX  - 0.5));
        ub = rec.y + rec.height + round(varphi*rec.height*((float)rand()/RAND_MAX - 0.5));
        vb = rec.x + rec.width + round(varphi*rec.width*((float)rand()/RAND_MAX  - 0.5));

        // check limits
        if (va<0){va = 0;}
        if (ua<0){ua = 0;}
        if (vb>=img.cols){vb = img.cols-1;}
        if (ub>=img.rows){ub = img.rows-1;}

        // check min. size
        if ((vb-va)>minSize && (ub-ua)>minSize){
            std::cout << "rec.y - " << rec.y << ", rec.x - " << rec.x << ", rec.height - " << rec.height << ", rec.width" << rec.width << std::endl;
            std::cout << "min size " << minSize << " vb-va " << (vb - va) << " ub - ua  "
                      << (ub - ua) << " va " << va << " ua " << ua << " vb " << vb << " ub " << ub << std::endl;

            // new bounding box
            newRec = cvRect(va, ua, vb-va, ub-ua);

            // image patch using ROI
            cv::Mat patch = cv::Mat(cvSize(objWidth, objHeight), CV_8UC3);
            cv::resize(img(newRec), patch, cvSize(objWidth, objHeight));

            // fern maps (convolve ferns with the image)
//            cv::Mat fernMaps = fern_maps(patch, RFs);

            // update classifier
//            clfr->update(fernMaps, posLabel);

        }
    }
};


void update_pos_samples(py::array_t<unsigned short int> &fern_map, float label) {
    std::cout << "update_pos_samples" << std::endl;
}

void update_neg_samples() {
    std::cout << "update_neg_samples" << std::endl;
}

void update_samples(py::module &m) {
    m.def("update_positive_samples", &update_pos_samples,
            py::arg("image"),
            py::arg("rectangle"));
    m.def("update_negative_samples", &update_neg_samples);
}
