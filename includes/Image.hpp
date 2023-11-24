#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include "File.hpp"
#include "Kernel.hpp"
#include "gaussian_blur.h"
#include "PNGFile.hpp"


class Image {
public:
    Image(const File& file) {
        pixels_ = file.read(*this);
    }

    void filter(const GaussianKernel<double>& kernel) {
    int halfSize = kernel.getSize() / 2;
    auto outputImage = std::vector<std::vector<t_Pixel>>(height_, std::vector<t_Pixel>(width_));
    const auto& kernelData = kernel.data();
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            double red = 0.0, green = 0.0, blue = 0.0;
            for (int i = -halfSize; i <= halfSize; i++) {
                for (int j = -halfSize; j <= halfSize; j++) {
                    int xi = std::min(std::max(x + i, 0), width_ - 1);
                    int yj = std::min(std::max(y + j, 0), height_ - 1);
                    t_Pixel &pixel = pixels_[yj][xi];
                    red += pixel.red * kernelData[i + halfSize][j + halfSize];
                    green += pixel.green * kernelData[i + halfSize][j + halfSize];
                    blue += pixel.blue * kernelData[i + halfSize][j + halfSize];
                }
            }
            outputImage[y][x] = {static_cast<unsigned char>(red), static_cast<unsigned char>(green), static_cast<unsigned char>(blue), 255};
        }
    }
    pixels_ = outputImage;
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