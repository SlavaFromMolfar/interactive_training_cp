#ifndef DET_DETECTIONSET_H
#define DET_DETECTIONSET_H


class DetectionSet {
private:
    int numDets{};  // num. detections
    int numMaxDets{}; // num. max. detections
    Detection* dets{}; // array of detections
public:
    DetectionSet();  // constructor
    ~DetectionSet();  // destructor
    void release();  // release memory
    int get_num_detections();  // return num. detections
    int get_num_max_detections();  // return num. max. detections
    void non_maxima_supression();  // return maxima detections
    void scaling(float scaleFactor);  // scale detection coordinates
    void set_num_detections(int value);  // set number of detections
    Detection* get_detection(int index);  // return indexed detection
    void remove_detections(Detection* det);  // remove detections using overlapping measure
    void add_detections(DetectionSet* dets);  // add new detections
    void get_max_detection(Detection* maxDet);  // return max. detection
    void set_detection(Detection* det, int index);  // set indexed detection
};


#endif //DET_DETECTIONSET_H
