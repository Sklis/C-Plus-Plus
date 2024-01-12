#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <iostream>
#include <utility>

namespace s21 {
template <typename T>
class Stack final {
 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value);
  };
  Node* top_;
  void clear();

 public:
  using size_type = size_t;
  // rule of 5
  Stack();
  Stack(std::initializer_list<T> const& items);
  Stack(const Stack& other);
  Stack(Stack&& other) noexcept;
  ~Stack();
  Stack& operator=(const Stack& other);
  Stack& operator=(Stack&& other) noexcept;
  // methods
  void push(const T& value);
  void pop();
  const T& top() const;
  bool empty() const;
  size_type size() const;
  void swap(Stack& other) noexcept;
  template <class... Args>
  void insert_many_front(Args&&... args);
  // debug
  void print() const;
};
}  // namespace s21

#include "s21_stack_impl.tpp"

#endif  // S21_STACK_H_