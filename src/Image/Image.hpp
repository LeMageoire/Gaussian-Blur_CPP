#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include "../File/File.hpp"
#include "../Kernel/Kernel.hpp"
#include "../gaussian_blur.h"

class Image {
public:
    Image(const File& file) {
        pixels = file.read();
    }

    void filter(const GaussianKernel<double>& kernel) {
        // Apply the Gaussian filter to the image
    }
private:
    std::vector<std::vector<t_Pixel>> pixels;
};

#include "Image.tpp"

#endif // IMAGE_HPP