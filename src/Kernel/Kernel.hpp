#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <vector>

template <Arithmetic T>
class Kernel {
public:
    Kernel(int size);
    virtual void fill() = 0;
    const std::vector<std::vector<T>>& data() const;

protected:
    int size_;
    std::vector<std::vector<T>> data_;
};

#include "kernel.tpp"

#endif // KERNEL_HPP