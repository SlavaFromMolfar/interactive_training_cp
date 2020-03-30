#include <pybind11/pybind11.h>

namespace py = pybind11;

void update_pos_samples() {
    std::cout << "update_pos_samples" << std::endl;
}

void update_neg_samples() {
    std::cout << "update_neg_samples" << std::endl;
}

void update_samples(py::module &m) {
    m.def("update_positive_samples", &update_pos_samples);
    m.def("update_negative_samples", &update_neg_samples);
}
