#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include "../File/File.hpp"
#include "../Kernel/Kernel.hpp"
#include "../gaussian_blur.h"
#include "../File/PNGFile.hpp"


class Image {
public:
    Image(const File& file) {
        pixels_ = file.read(*this);
    }

    void filter(const GaussianKernel<double>& kernel) {
        // Apply the Gaussian filter to the image
    }

    int getHeight() const {
        return height_;
    }

    int getWidth() const {
        return width_;
    }

    const std::vector<std::vector<t_Pixel>>& getPixels() const {
        return pixels_;
    }

    void setHeight(int height) {
        height_ = height;
    }

    void setWidth(int width) {
        width_ = width;
    }

    void setPixels(const std::vector<std::vector<t_Pixel>>& pixels) {
        pixels_ = pixels;
    }

private:
    std::vector<std::vector<t_Pixel>> pixels_;
    int height_;
    int width_;
};

#endif // IMAGE_HPP