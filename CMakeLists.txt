cmake_minimum_required(VERSION 3.15)
project(det)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)
pybind11_add_module(detect src/main.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(detect PRIVATE ${OpenCV_LIBS})
