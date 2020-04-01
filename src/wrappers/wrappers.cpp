#include "listToCvRect.cpp"
#include "cvMatToNumpy.h"
#include "classifier/classifier.cpp"


void init_wrappers(py::module &module) {
    module.def("listToCvRect", &listToCvRect);
    module.def("cvMatToNumpyDouble", &cvMatToNumpy::cvMatToNumpyDouble);
    module.def("cvMatToNumpyInt", &cvMatToNumpy::cvMatToNumpyInt);
    module.def("cvMatToNumpyUnsignedShortInt", &cvMatToNumpy::cvMatToNumpyUnsignedShortInt);
}