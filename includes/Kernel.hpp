#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <vector>
#include <iostream>
#include <cmath> // for std::exp

template <typename T>
class Kernel {
public:
    Kernel(int size);
    virtual void fill() = 0;
    const std::vector<std::vector<T>>& data() const;
  
    int getSize() const {
        return size_;
    }
  
    virtual void print() const {
        for (const auto& row : data_) {
            for (const auto& value : row) {
                std::cout << value << ' ';
            }
            std::cout << '\n';
        }
    }
protected:
    int size_;
    std::vector<std::vector<T>> data_;
};

template <typename T>
Kernel<T>::Kernel(int size) : size_(size), data_(size, std::vector<T>(size)) {}

template <typename T>
const std::vector<std::vector<T>>& Kernel<T>::data() const { return data_; }

template <typename T>
class GaussianKernel : public Kernel<T> {
public:
    GaussianKernel(int size, double sigma) 
        : Kernel<T>(size),
          sigma_(sigma)
    {
        this->fill();
    }

    void fill() {
        int halfSize = this->size_ / 2;
        double sum = 0.0;

        for (int i = -halfSize; i <= halfSize; ++i) {
            for (int j = -halfSize; j <= halfSize; ++j) {
                double value = (1.0 / (2.0 * M_PI * sigma_ * sigma_)) * std::exp(-(i * i + j * j) / (2 * sigma_ * sigma_));
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
    void print() const override {
        Kernel <T>::print();
    }
    private :
        double sigma_;
};

template <typename T>
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

#endif // KERNEL_HPP