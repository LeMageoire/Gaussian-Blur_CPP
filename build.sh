#!/bin/sh
g++ -o Gaussian_Blur_CLI main.cpp ./File/PNGFile.cpp -lpng -I/third-party/libpng/ -L/third-party/libpng/build

