#include "DetectionSet.h"

DetectionSet::DetectionSet() {
    // default values
    this->numDets = 0;  // num. detections
    this->numMaxDets = 1000;  // num. max. detections

    // array of detections
    this->dets = new Detection[this->numMaxDets];
}

// Destructor
DetectionSet::~DetectionSet(){
    // relase memory
    release();
}

// release
void DetectionSet::release(){
    delete[]this->dets;
}

// get num. detections
int DetectionSet::get_num_detections(){
    return this->numDets;
}
// set num. detections
void DetectionSet::set_num_detections(int value){
    // inputs:
    // value: num. detections
    this->numDets = value;
}

// get num. max. detections
int DetectionSet::get_num_max_detections(){
    return this->numMaxDets;
}

// get detection
Detection* DetectionSet::get_detection(int index){
    // inputs:
    // index: detection index in the list of all detections
    Detection* det = &this->dets[index];
    return det;
}

// set a new detection
void DetectionSet::set_detection(Detection* det, int index){
    // inputs:
    // det: detection
    // index: detection index

    // variable
    float score;
    int u1,v1,u2,v2,ide;

    // get input detection values
    u1 = det->get_u1();
    v1 = det->get_v1();
    u2 = det->get_u2();
    v2 = det->get_v2();
    score = det->get_score();
    ide = det->get_ide();

    // set detection values
    this->dets[index].set_u1(u1);
    this->dets[index].set_v1(v1);
    this->dets[index].set_u2(u2);
    this->dets[index].set_v2(v2);
    this->dets[index].set_score(score);
    this->dets[index].set_ide(ide);
}

// scaling
void DetectionSet::scaling(float scaleFactor){
    // inputs:
    // scale factor: scaling factor for detections coordinates

    // variables
    float score;
    int u1,v1,u2,v2,ide;

    // scaling detection coordinates
    for (int iter=0; iter<this->numDets; iter++){

        // scaling spatial coordinates
        this->dets[iter].get_u1();
        u1 = (int)round(this->dets[iter].get_u1() * scaleFactor);
        v1 = (int)round(this->dets[iter].get_v1() * scaleFactor);
        u2 = (int)round(this->dets[iter].get_u2() * scaleFactor);
        v2 = (int)round(this->dets[iter].get_v2() * scaleFactor);

        score = this->dets[iter].get_score();
        ide = this->dets[iter].get_ide();

        this->dets[iter].set_u1(u1);
        this->dets[iter].set_v1(v1);
        this->dets[iter].set_u2(u2);
        this->dets[iter].set_v2(v2);
        this->dets[iter].set_score(score);
        this->dets[iter].set_ide(ide);
    }
}

// add detections
void DetectionSet::add_detections(DetectionSet* newDets){
    // inputs:
    // newDets: new detections

    // variables
    int numNewDets;

    // num. new detections
    numNewDets = newDets->get_num_detections();

    // check
    if (this->numDets + numNewDets >= this->numMaxDets){
        std::cout << "ERROR: num. max. detections"  << std::endl;
    }
    else{
        // add detections
        for (int iter=0; iter<numNewDets; iter++){
            this->dets[this->numDets+iter] = newDets->dets[iter];
        }
        // updates num. detections
        this->numDets += numNewDets;
    }
}

// maxima detection
void DetectionSet::get_max_detection(Detection* maxDet){
    // inputs:
    // maxDet: maxima detection

    // variables
    int u1,v1,u2,v2,ide;
    float score,maxScore = 0;

    // detections
    for (int iter=0; iter<this->numDets; iter++){

        // get detection values
        u1 = this->dets[iter].get_u1();
        v1 = this->dets[iter].get_v1();
        u2 = this->dets[iter].get_u2();
        v2 = this->dets[iter].get_v2();
        score = this->dets[iter].get_score();
        ide = this->dets[iter].get_ide();

        // best score
        if (score>maxScore){

            // set max. detection
            maxDet->set_u1(u1);
            maxDet->set_v1(v1);
            maxDet->set_u2(u2);
            maxDet->set_v2(v2);
            maxDet->set_score(score);
            maxDet->set_ide(ide);

            // update max. score
            maxScore = score;
        }
    }
}

// remove detections
void DetectionSet::remove_detections(Detection* det){
    // inputs:
    // det: detection

    // parameters
    float thr = 0.01;  // overlapping rate threshold

    // variables
    int counter = 0;  // counter
    int ua,va,ub,vb;  // overlapping coordinates
    Detection empty;  // empty detection
    float score,rscore;  // detection scores
    int u1,v1,u2,v2,ide;  // detection coordinates
    float w,h,area,rarea;  // overlapping variables
    int ru1,rv1,ru2,rv2,ride;  // reference detection coordinates

    // num. initial detections
    this->numDets = get_num_detections();

    // get reference detection values
    ru1 = det->get_u1();
    rv1 = det->get_v1();
    ru2 = det->get_u2();
    rv2 = det->get_v2();
    rscore = det->get_score();
    ride = det->get_ide();

    // reference area
    rarea = (ru2 - ru1) * (rv2-rv1);

    // check each detection
    for (int iter=0; iter<this->numDets; iter++){

        // get detection values
        this->dets[iter].get_u1();
        this->dets[iter].get_v1();
        this->dets[iter].get_u2();
        this->dets[iter].get_v2();
        this->dets[iter].get_score();
        this->dets[iter].get_ide();

        // overlapping values
        ua = std::max(ru1, u1);
        va = std::max(rv1, v1);
        ub = std::min(ru2, u2);
        vb = std::min(rv2, v2);
        w = vb - va;  // width
        h = ub - ua;  // height
        area = w*h;  // area

        // remove detections
        if (w<=0 || h<=0 || (area/rarea)<thr){
            // no intersection
            this->dets[counter].set_u1(u1);
            this->dets[counter].set_v1(v1);
            this->dets[counter].set_u2(u2);
            this->dets[counter].set_v2(v2);
            this->dets[counter].set_score(score);
            this->dets[counter].set_ide(ide);
            counter++;
        }
    }

    // delete detections
    for (int iter=counter; iter<this->numDets; iter++){
        this->dets[iter] = empty;
    }

    // update num. detections
    set_num_detections(counter);

}

// non-maxima suppresion
void DetectionSet::non_maxima_supression(){

    // variables
    int counter = 0;   // detection counter

    // temporal detection set
    auto detSet = new DetectionSet;

    // num. initial detections
    this->numDets = get_num_detections();

    // check detections
    if (this->numDets>0){

        // remove detections
        while (this->get_num_detections()!=0){

            // max. detection
            auto maxDet = new Detection;

            // get max. detection
            this->get_max_detection(maxDet);

            // get non-intersection detections
            this->remove_detections(maxDet);

            // add detection: max. detection
            detSet->set_detection(maxDet, counter);

            // update counter
            counter++;

            // set num. detections
            detSet->set_num_detections(counter);

            // release
            delete maxDet;
        }
    }

    // add max. detections: non-maxima suppression
    this->add_detections(detSet);

    // release
    delete detSet;
};