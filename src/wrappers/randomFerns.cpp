#include "../randomFerns/RandomFerns.h"
#include "../randomFerns/RandomFerns.cpp"

void randomFerns(py::module &module) {
    py::class_<RandomFerns>(module, "RandomFerns")
            .def(py::init<>())
            .def(py::init<int, int, int, int>(),
                    py::arg("poolSize") = 5,
                    py::arg("fernSize") = 4,
                    py::arg("numFeats") = 5,
                    py::arg("fernDepth") = 3)
            .def("getPoolSize", &RandomFerns::get_pool_size, py::return_value_policy::copy)
            .def("getFernSize", &RandomFerns::get_fern_size, py::return_value_policy::copy)
            .def("getNumFeats", &RandomFerns::get_num_features, py::return_value_policy::copy)
            .def("getFernDepth", &RandomFerns::get_fern_depth, py::return_value_policy::copy)
            .def("getData", &RandomFerns::get_data_np)
            .def("compute", &RandomFerns::compute,
                    py::arg("R"),
                    py::arg("M"),
                    py::arg("S"),
                    py::arg("C"))
            .def("print", &RandomFerns::print);
}
