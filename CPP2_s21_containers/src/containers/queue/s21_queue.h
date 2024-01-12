#ifndef S21_Queue_H
#define S21_Queue_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {
template <typename T>
class Queue {
 private:
  struct Node {
    T data;
    Node *next;
    Node(const T &value);
  };
  Node *front_;
  Node *rear_;
  void clear();

 public:
  using const_reference = const T &;
  using size_type = size_t;
  // rule of 5
  Queue();
  Queue(std::initializer_list<T> const &items);
  Queue(const Queue &other);
  Queue(Queue &&other);
  ~Queue();
  Queue &operator=(const Queue &other);
  Queue &operator=(Queue &&other) noexcept;
  // methods
  const_reference front() const;
  const_reference back() const;
  void push(const T &value);
  void pop();
  bool empty() const;
  size_type size() const;
  void swap(Queue &other) noexcept;
  template <class... Args>
  void insert_many_back(Args &&...args);
  // debug
  void print() const;
};
}  // namespace s21

#include "s21_queue_impl.tpp"
#endif  // s21_Queue_H