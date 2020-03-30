#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/core.hpp>

#include "update/update.cpp"
#include "wrappers/wrappers.cpp"

namespace py = pybind11;

PYBIND11_MODULE(detect, m) {
    update_samples(m);
    init_wrappers(m);
    classifier(m);
}