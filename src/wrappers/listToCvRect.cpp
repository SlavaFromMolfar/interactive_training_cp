//TODO: replace void with cv::Rect type
void listToCvRect(const py::list &list) {
    int x = list[0].cast<int>();
    int y = list[1].cast<int>();
    int width = list[2].cast<int>();
    int height = list[3].cast<int>();
    auto rect = new cv::Rect(x, y, width, height);
    std::cout << "x: " << rect->x << " y: " << rect->y << " width: " << rect->width << " height: "
              << rect->height << std::endl;
}