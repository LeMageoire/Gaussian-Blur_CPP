template <Arithmetic T>
Kernel<T>::Kernel(int size) : size_(size), data_(size, std::vector<T>(size)) {}

template <Arithmetic T>
const std::vector<std::vector<T>>& Kernel<T>::data() const { return data_; }