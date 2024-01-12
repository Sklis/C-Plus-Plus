#ifndef _TESTS_STACK_HELPERS_H_
#define _TESTS_STACK_HELPERS_H_

#include <iostream>
#include <stack>

#include "../stack/s21_stack.h"

// GCOVR_EXCL_START

template <typename T>
bool operator==(s21::Stack<T> s21_stack, std::stack<T> stack) {
  if (s21_stack.size() != stack.size()) return false;

  while (!s21_stack.empty()) {
    if (s21_stack.top() != stack.top()) return false;

    s21_stack.pop();
    stack.pop();
  }
  return true;
}

template <typename T>
bool operator==(std::stack<T> stack, s21::Stack<T> s21_stack) {
  return s21_stack == stack;
}

template <typename T>
bool operator==(s21::Stack<T> left, s21::Stack<T> right) {
  if (left.size() != right.size()) return false;

  while (!left.empty()) {
    if (left.top() != right.top()) return false;

    left.pop();
    right.pop();
  }
  return true;
}

template <typename T>
bool operator!=(s21::Stack<T> left, s21::Stack<T> right) {
  return !(left == right);
}

// GCOVR_EXCL_STOP

#endif  //  _TESTS_STACK_HELPERS_H_
