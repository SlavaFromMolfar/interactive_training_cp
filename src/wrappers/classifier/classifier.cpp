#include "Classifier.cpp"

void classifier(py::module &m) {
    py::class_<Classifier> (m, "Classifier")
            .def_property("beta", &Classifier::get_threshold, &Classifier::set_threshold)
            .def("getNumFerns", &Classifier::get_num_ferns)
            .def("getData", &Classifier::get_data)
            .def("get_pos_np", &Classifier::get_posHstms_np)
            .def("get_neg_np", &Classifier::get_negHstms_np)
            .def("get_rat_np", &Classifier::get_ratHstms_np)
            .def(py::init<>())
            .def(py::init<float, int, int, int, int>(),
                    py::arg("beta") = 0.5,
                    py::arg("numBins") = 128,
                    py::arg("numFerns") = 100,
                    py::arg("objWidth") = 24,
                    py::arg("objHeight") = 24
            )
            .def("compute", &Classifier::compute,
                    py::arg("J"),
                    py::arg("R"),
                    py::arg("M"),
                    py::arg("S")
            )
            .def("update", &Classifier::update,
                    py::arg("fernMaps"),
                    py::arg("label")
            ).def("print", &Classifier::print);
}
