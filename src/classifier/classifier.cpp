#include "Classifier.cpp"
#include "ClassifierSet.cpp"

void classifier(py::module &m) {
    py::class_<Classifier> (m, "Classifier")
            .def_property("beta", &Classifier::get_threshold, &Classifier::set_threshold)
            .def("getNumFerns", &Classifier::get_num_ferns)
            .def("getData", &Classifier::get_data)
            .def("get_object_model", &Classifier::get_object_model)
            .def("set_object_model", &Classifier::set_object_model,
                    py::arg("object_model"))
            .def("get_pos_np", &Classifier::get_posHstms_np)
            .def("get_neg_np", &Classifier::get_negHstms_np)
            .def("get_rat_np", &Classifier::get_ratHstms_np)
            .def("set_object_size", &Classifier::set_object_size,
                    py::arg("Bu"),
                    py::arg("Bv"))
            .def("get_object_height", &Classifier::get_object_height)
            .def("set_object_height", &Classifier::set_object_height,
                    py::arg("height"))
            .def("get_object_width", &Classifier::get_object_width)
            .def("set_object_width", &Classifier::set_object_width,
                    py::arg("width"))
            .def(py::init<>())
            .def("compute", &Classifier::compute,
                    py::arg("J"),
                    py::arg("R"),
                    py::arg("M"),
                    py::arg("S")
            )
            .def("update", &Classifier::update_py,
                    py::arg("fernMaps"),
                    py::arg("label")
            ).def("print", &Classifier::print);
    py::class_<ClassifierSet> (m, "ClassifierSet")
            .def(py::init<>())
            .def("get_num_classifiers", &ClassifierSet::get_num_classifiers)
            .def("get_num_max_classifiers", &ClassifierSet::get_num_max_classifiers)
            .def("set_num_classifiers", &ClassifierSet::set_num_classifiers,
                    py::arg("K"))
            .def("get_classifier", &ClassifierSet::get_classifier,
                    py::arg("K"), py::return_value_policy::reference);
}
