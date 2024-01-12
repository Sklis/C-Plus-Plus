#ifndef _TESTS_VECTOR_HELPERS_H_
#define _TESTS_VECTOR_HELPERS_H_

#include <iostream>
#include <vector>

#include "../vector/s21_vector.h"

// GCOVR_EXCL_START

template <typename T>
bool operator==(const s21::Vector<T>& s21_vector,
                const std::vector<T>& vector) {
  if (s21_vector.size() != vector.size()) return false;

  auto s21_it = s21_vector.cbegin();
  auto it = vector.cbegin();
  while (s21_it != s21_vector.cend()) {
    if (*s21_it != *it) return false;
    ++s21_it;
    ++it;
  }

  return true;
}

template <typename T>
bool operator==(std::vector<T> vector, s21::Vector<T> s21_vector) {
  return s21_vector == vector;
}

template <typename T>
bool operator!=(const s21::Vector<T>& s21_vector,
                const std::vector<T>& vector) {
  return !(s21_vector == vector);
}

template <typename T>
bool operator!=(std::vector<T> vector, s21::Vector<T> s21_vector) {
  return !(s21_vector == vector);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const s21::Vector<T>& object) {
  out << "vector: ";
  for (auto it = object.cbegin(); it != object.cend() - 1; ++it)
    out << *it << ' ';
  // for (const auto& element : object) out << element << ' ';
  return out;
}

// GCOVR_EXCL_STOP

#endif  //  _TESTS_VECTOR_HELPERS_H_
