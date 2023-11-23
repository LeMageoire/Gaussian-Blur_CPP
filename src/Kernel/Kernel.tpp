#include <vector>
#include <cmath>
#include "Kernel.hpp"


template </*Arithmetic*/typename T>
Kernel<T>::Kernel(int size) : size_(size), data_(size, std::vector<T>(size)) {}

template </*Arithmetic*/typename T>
const std::vector<std::vector<T>>& Kernel<T>::data() const { return data_; }

template <typename T>
GaussianKernel<T>::GaussianKernel(int size, double sigma) : Kernel<T>(size), sigma_(sigma) {}

template <typename T>
void GaussianKernel<T>::fill() {
    int halfSize = this->size_ / 2;
        double sum = 0.0;

        for (int i = -halfSize; i <= halfSize; ++i) {
            for (int j = -halfSize; j <= halfSize; ++j) {
                double value = std::exp(-(i * i + j * j) / (2 * sigma_ * sigma_)) / (2 * M_PI * sigma_ * sigma_);
                this->data_[i + halfSize][j + halfSize] = value;
                sum += value;
            }
        }
        for (int i = 0; i < this->size_; ++i) {
            for (int j = 0; j < this->size_; ++j) {
                this->data_[i][j] /= sum;
            }
        }
}