#include "IntegralImage.cpp"


void integralImage(py::module &module) {
    py::class_<IntegralImage>(module, "IntegralImage")
            .def(py::init())
            .def(py::init<int, int, int, int, int, int>(),
                    py::arg("width"),
                    py::arg("height"),
                    py::arg("imgChans"),
                    py::arg("imgWidth"),
                    py::arg("imgHeight"),
                    py::arg("cellSize"))
            .def("get_image", &IntegralImage::get_image_py)
            .def("release_image", &IntegralImage::release_image)
            .def("get_image_width", &IntegralImage::get_image_width)
            .def("get_image_height", &IntegralImage::get_image_height)
            .def("compute_image", &IntegralImage::compute_image,
                    py::arg("size"))
            .def("integral_image", &IntegralImage::integral_image,
                    py::arg("img"));
}