mkdir "build"
cd build || exit
cmake ..
make
# Копировать *.so файл в папку detector