#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>

namespace s21 {
template <typename T>
class Vector {
 private:
  T* data_;
  size_t size_;
  size_t capacity_;
  void allocate();

 public:
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  // rules of 5
  Vector();
  Vector(size_t initialSize);
  Vector(const Vector& v);
  Vector(std::initializer_list<T> const& items);
  ~Vector();
  Vector(Vector&& v) noexcept;
  Vector& operator=(Vector&& v) noexcept;
  Vector& operator=(const Vector& v);
  // methods
  void reserve(size_t newCapacity);
  void push_back(const T& value);
  bool empty() const;
  size_t size() const;
  size_t max_size() const;
  size_t capacity() const;
  void pop_back();
  void shrink_to_fit();
  void clear() noexcept;
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  iterator data();
  const_iterator data() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator insert(const_iterator pos, const_reference value);
  iterator erase(const_iterator pos);
  void erase(const_iterator first, const_iterator last);
  void swap(Vector<T>& other);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

  // debug
  void print() const;
  bool operator==(const Vector<T>& other) const noexcept;
  bool operator!=(const Vector<T>& other) const noexcept;
  iterator& operator++();
  iterator& operator--();
  const_iterator& operator++() const;
  const_iterator& operator--() const;
  bool operator==(const iterator& other) const;
  bool operator!=(const iterator& other) const;
};
}  // namespace s21

#include "s21_vector_impl.tpp"
#endif  // S21_VECTOR_H
