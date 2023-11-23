#include <vector>
#include "../Concepts.hpp"

template <Arithmetic T>
class File {
public:
    File(int width, int height) : width_(width), height_(height), pixels_(height, std::vector<t_pixel>(width)) {}

    void filter(Kernel<T>& kernel) {
        // Implement the filter method here
        // This method should apply the kernel to the pixels_
    }

    const std::vector<std::vector<t_pixel>>& pixels() const { return pixels_; }

private:
    int width_, height_;
    std::vector<std::vector<t_pixel>> pixels_;
};