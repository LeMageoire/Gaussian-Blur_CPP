#!/bin/sh
g++ -o Gaussian_Blur_CLI ./src/main.cpp ./src/File/PNGFile.cpp -lpng -I/third-party/libpng/ -L/third-party/libpng/build

