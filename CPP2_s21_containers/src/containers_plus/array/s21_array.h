#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // rule of 5
  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a) noexcept;
  Array &operator=(const Array &a);
  Array &operator=(Array &&a) noexcept;
  ~Array();
  // iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin(void) const;
  const_iterator cend(void) const;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;
  // methods
  bool empty();
  size_type size() const;
  size_type max_size();
  void swap(Array &a);
  void fill(const_reference value);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  iterator data();
  const_iterator data() const;
  // debug function
  void print();

 private:
  value_type elems_[N];
  size_type size_ = N;
};
}  // namespace s21

#include "s21_array_impl.tpp"

#endif  // S21_ARRAY_H