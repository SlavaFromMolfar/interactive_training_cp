#include "ClassifierSet.h"

// ClassifierSet
// constructor
ClassifierSet::ClassifierSet(){
    // initialize
    init();
};
// Destructor
ClassifierSet::~ClassifierSet(){
    // relase memory
    release();
};
// initialize
void ClassifierSet::init(){

    // default values
    this->numClfrs = 0;  // num. classifiers (K)
    this->numMaxClfrs = 30;  // num. max. classifiers

    // array of classifiers
    this->clfrs = new Classifier[this->numMaxClfrs];

};
// release
void ClassifierSet::release(){
    delete[]this->clfrs;
};
// get num. classifiers (K)
int ClassifierSet::get_num_classifiers(){
    return this->numClfrs;
};
// get num. max. classifiers
int ClassifierSet::get_num_max_classifiers(){
    return this->numMaxClfrs;
};
// get classifier
Classifier* ClassifierSet::get_classifier(int k){
    // inputs:
    // k: classifier index in the list of all classifiers
    Classifier *clfr = &this->clfrs[k];
    return clfr;
};
// set num. classifiers (K)
void ClassifierSet::set_num_classifiers(int K){
    // inputs:
    // K: num. classifiers
    this->numClfrs = K;
};