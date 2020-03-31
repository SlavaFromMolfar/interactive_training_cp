#include "listToCvRect.cpp"
#include "cvMatToNumpy.cpp"
#include "classifier/classifier.cpp"


void init_wrappers(py::module &module) {
    module.def("listToCvRect", &listToCvRect);
    module.def("cvMatToNumpyDouble", &cvMatToNumpyDouble);
    module.def("cvMatToNumpyInt", &cvMatToNumpyInt);
    module.def("cvMatToNumpyUnsignedShortInt", &cvMatToNumpyUnsignedShortInt);
}