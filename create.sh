git clone https://github.com/pybind/pybind11.git
mkdir "build"
cd build || exit
cmake ..
make
# Копировать *.so файл в папку detector