#ifndef _TESTS_ARRAY_HELPERS_H_
#define _TESTS_ARRAY_HELPERS_H_

#include <array>
#include <iostream>

#include "../array/s21_array.h"

// GCOVR_EXCL_START

namespace s21 {

template <typename T, size_t N1, size_t N2>
bool operator==(const s21::Array<T, N1>& left, const s21::Array<T, N2>& right) {
  if (left.size() != right.size()) return false;

  auto l_it = left.cbegin();
  auto r_it = right.cbegin();
  while (l_it != left.cend()) {
    if (*l_it != *r_it) return false;
    ++l_it;
    ++r_it;
  }

  return true;
}

template <typename T, size_t N1, size_t N2>
constexpr bool operator!=(const s21::Array<T, N1>& left,
                          const s21::Array<T, N2>& right) {
  return !(left == right);
}

template <typename T, size_t N1, size_t N2>
bool operator==(const s21::Array<T, N1>& s21_array,
                const std::array<T, N2>& array) {
  if (s21_array.size() != array.size()) return false;

  auto s21_it = s21_array.cbegin();
  auto it = array.cbegin();
  while (s21_it != s21_array.cend()) {
    if (*s21_it != *it) return false;
    ++s21_it;
    ++it;
  }

  return true;
}

template <typename T, size_t N>
bool operator==(const std::array<T, N>& array,
                const s21::Array<T, N>& s21_array) {
  return s21_array == array;
}

template <typename T, size_t N>
bool operator!=(const s21::Array<T, N>& s21_array,
                const std::array<T, N>& array) {
  return !(s21_array == array);
}

template <typename T, size_t N>
bool operator!=(const std::array<T, N>& array,
                const s21::Array<T, N>& s21_array) {
  return !(s21_array == array);
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const s21::Array<T, N>& object) {
  out << "Array: ";
  for (auto it = object.cbegin(); it != object.cend(); ++it) out << *it << ' ';
  std::cout << '\n';
  // for (const auto& element : object) out << element << ' ';
  return out;
}

}  // namespace s21

// GCOVR_EXCL_STOP

#endif  //  _TESTS_ARRAY_HELPERS_H_
