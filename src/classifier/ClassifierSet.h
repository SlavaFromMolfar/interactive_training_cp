#ifndef DET_CLASSIFIERSET_H
#define DET_CLASSIFIERSET_H

#include "Classifier.h"

class ClassifierSet {
private:
    int numClfrs;  // num. classifiers (K)
    int numMaxClfrs;  // num. max. classifiers
    Classifier* clfrs;  // array of classifiers
public:
    ClassifierSet();  // constructor
    ~ClassifierSet();  // destructor
    void init();  // initialize
    void release();  // release memory
    int get_num_classifiers();  // return num. classifiers (K)
    int get_num_max_classifiers();  // return num. max. classifiers
    void set_num_classifiers(int K);  // set num. classifiers (K)
    Classifier* get_classifier(int k);  // return indexed classifier
};

#endif //DET_CLASSIFIERSET_H
