#ifndef _TESTS_QUEUE_HELPERS_H_
#define _TESTS_QUEUE_HELPERS_H_

#include <queue>

#include "../queue/s21_queue.h"

// GCOVR_EXCL_START

template <typename T>
bool operator==(s21::Queue<T> s21_queue, std::queue<T> queue) {
  if (s21_queue.size() != queue.size()) return false;

  while (!s21_queue.empty()) {
    if (s21_queue.front() != queue.front()) return false;

    s21_queue.pop();
    queue.pop();
  }
  return true;
}

template <typename T>
bool operator==(std::queue<T> queue, s21::Queue<T> s21_queue) {
  return s21_queue == queue;
}

template <typename T>
bool operator==(s21::Queue<T> left, s21::Queue<T> right) {
  if (left.size() != right.size()) return false;

  while (!left.empty()) {
    if (left.front() != right.front()) return false;

    left.pop();
    right.pop();
  }
  return true;
}

template <typename T>
bool operator!=(s21::Queue<T> left, s21::Queue<T> right) {
  return !(left == right);
}

// GCOVR_EXCL_STOP

#endif  //  _TESTS_QUEUE_HELPERS_H_
