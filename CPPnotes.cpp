#include <type_traits>
#include <vector>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
class Kernel {
public:
    Kernel(int size) : size_(size), data_(size, std::vector<T>(size)) {}

    virtual void fill() = 0;

    const std::vector<std::vector<T>>& data() const { return data_; }

protected:
    int size_;
    std::vector<std::vector<T>> data_;
};

template <Arithmetic T>
class GaussianKernel : public Kernel<T> {
public:
    GaussianKernel(int size) : Kernel<T>(size) {}

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
};
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

int main() {
    GaussianKernel<double> kernel(5);
    kernel.fill();
    BoxKernel<int> kernel2(5);
    kernel2.fill();
}