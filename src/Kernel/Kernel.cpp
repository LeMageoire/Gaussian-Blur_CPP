
#include <cmath> // for std::exp
#include "Kernel/Kernel.hpp"


template </*Arithmetic*/typename T>
class GaussianKernel : public Kernel<T> {
public:
    GaussianKernel(int size, double sigma) : Kernel<T>(size), sigma_(sigma) {}

    void fill() override {
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
    private :
        double sigma_;
};

template </*Arithmetic*/ T>
class BoxKernel : public Kernel<T> {
public:
    BoxKernel(int size) : Kernel<T>(size) {}

    void fill() override {
        int value = 1 / (this->size_ * this->size_);
        for (int i = 0; i < this->size_; ++i) {
            for (int j = 0; j < this->size_; ++j) {
                this->data_[i][j] = value;
            }
        }
    }
};