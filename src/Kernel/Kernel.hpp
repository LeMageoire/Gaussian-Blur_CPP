#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <vector>
#include <iostream>
//#include "../Concepts.hpp"

template </*Arithmetic*/typename T>
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
class GaussianKernel;

template <typename T>
class BoxKernel;

#include "Kernel.cpp"

#endif // KERNEL_HPP