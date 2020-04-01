#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/imgproc.hpp>

#include "update/update.cpp"
#include "wrappers/fernMaps.cpp"
#include "wrappers/wrappers.cpp"
#include "wrappers/randomFerns.cpp"
#include "wrappers/cvMatToNumpy.h"
#include "wrappers/cvMatToNumpy.cpp"
#include "wrappers/NumpyToCvMat.cpp"

namespace py = pybind11;

PYBIND11_MODULE(detect, m) {
    update_samples(m);
    init_wrappers(m);
    classifier(m);
    randomFerns(m);
    fernMaps(m);
}