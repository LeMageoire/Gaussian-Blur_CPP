#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <vector>
//#include "../Concepts.hpp"

template </*Arithmetic*/typename T>
class Kernel {
public:
    Kernel(int size);
    virtual void fill() = 0;
    const std::vector<std::vector<T>>& data() const;

protected:
    int size_;
    std::vector<std::vector<T>> data_;
};

template </*Arithmetic*/ typename T>
class GaussianKernel : public Kernel<T> {
public:
    GaussianKernel(int size, double sigma);

    void fill() override;
    
    // ...

private:
    double sigma_;
};

#include "Kernel.tpp"

#endif // KERNEL_HPP