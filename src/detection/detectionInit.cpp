#include "Detection.cpp"
#include "DetectionSet.cpp"

void detectionInit(py::module &m) {
    py::class_<Detection>(m, "Detection").def(py::init())
            .def("set_u1", &Detection::set_u1,
                 py::arg("u1"))
            .def("set_v1", &Detection::set_v1,
                 py::arg("v1"))
            .def("set_u1", &Detection::set_u2,
                 py::arg("u2"))
            .def("set_v2", &Detection::set_v2,
                 py::arg("v2"))
            .def("set_score", &Detection::set_score,
                 py::arg("score"))
            .def("set_ide", &Detection::set_ide,
                 py::arg("ide"))
            .def("get_u1", &Detection::get_u1)
            .def("get_v1", &Detection::get_v1)
            .def("get_u2", &Detection::get_u2)
            .def("get_v2", &Detection::get_v2)
            .def("get_score", &Detection::get_score)
            .def("get_ide", &Detection::get_ide);

    py::class_<DetectionSet>(m, "DetectionSet")
            .def(py::init())
            .def("release", &DetectionSet::release)
            .def("get_num_detections", &DetectionSet::get_num_detections)
            .def("get_num_max_detections", &DetectionSet::get_num_max_detections)
            .def("non_maxima_supression", &DetectionSet::non_maxima_supression)
            .def("scaling", &DetectionSet::scaling,
                 py::arg("scaleFactor"))
            .def("set_num_detections", &DetectionSet::set_num_detections,
                 py::arg("value"))
            .def("get_detection", &DetectionSet::get_detection,
                 py::arg("index"), py::return_value_policy::reference)
//            .def("remove_detections", &DetectionSet::remove_detections,
//                 py::arg("det"))
            .def("add_detections", &DetectionSet::add_detections,
                 py::arg("dets"))
            .def("get_max_detection", &DetectionSet::get_max_detection,
                 py::arg("maxDet"))
            .def("set_detection", &DetectionSet::set_detection,
                 py::arg("det"),
                 py::arg("index"));
}