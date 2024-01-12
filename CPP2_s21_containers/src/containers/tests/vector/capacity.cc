#include <gtest/gtest.h>

#include <vector>

#include "../../vector/s21_vector.h"
#include "../item.h"
#include "../vector_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(vector, T0Capacity) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.reserve(100);
  vector.reserve(100);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), 100ull);  // 2^n - 1
}

TEST(vector, T1Capacity) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const auto s21_capacity_old = s21_vector.capacity();
  s21_vector.reserve(2);

  EXPECT_EQ(s21_vector.capacity(), s21_capacity_old);
}

TEST(vector, T2Size) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  EXPECT_EQ(s21_vector.size(), 3ull);
}

TEST(vector, T3Reserve) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.reserve(10);
  vector.reserve(10);
  // std::cout << s21_vector.capacity() << ' ' << vector.capacity() << '\n';

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), 10ull);  // 2^n - 1
}

TEST(vector, T4Reserve) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.reserve(2);
  vector.reserve(2);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());
}

TEST(vector, T5Reserve) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.reserve(0);
  vector.reserve(0);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());
}

TEST(vector, T6Reserve) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const auto s21_capacity = s21_vector.capacity();
  const auto capacity = vector.capacity();
  s21_vector.reserve(s21_capacity);
  vector.reserve(capacity);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());
}

TEST(vector, T7Shrink_to_fit) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.pop_back();
  s21_vector.pop_back();
  vector.pop_back();
  vector.pop_back();

  s21_vector.shrink_to_fit();
  vector.shrink_to_fit();

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());
}

TEST(vector, T8Shrink_to_fit) {
  s21::Vector<Item> s21_vector{Item(0), Item(11), Item(22, 'b'),
                               Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(0), Item(11), Item(22, 'b'),
                           Item(33, 'c', 0.3333)};

  s21_vector.pop_back();
  s21_vector.pop_back();
  vector.pop_back();
  vector.pop_back();

  s21_vector.shrink_to_fit();
  vector.shrink_to_fit();

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());

  s21_vector.shrink_to_fit();
  vector.shrink_to_fit();

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(s21_vector.capacity(), vector.capacity());
}

}  // namespace

// GCOVR_EXCL_STOP
