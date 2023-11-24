#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <type_traits>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

#endif // CONCEPTS_HPP