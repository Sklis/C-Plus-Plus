#include <gtest/gtest.h>

#include <deque>
#include <list>
#include <stack>
#include <vector>

#include "../../vector/s21_vector.h"
#include "../item.h"
#include "../vector_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(vector, T0Insert) {
  s21::Vector<Item> s21_vector;
  auto s21_it = s21_vector.begin();
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector;
  auto it = vector.begin();
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T00Insert) {
  s21::Vector<Item> s21_vector;
  auto s21_it = s21_vector.end();
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector;
  auto it = vector.end();
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T1Insert) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto s21_it = s21_vector.begin();
  s21_it += 2;
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto it = vector.begin();
  it += 2;
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T2Insert) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto s21_it = s21_vector.end();
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto it = vector.end();
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T3Insert) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto s21_it = s21_vector.begin();
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto it = vector.begin();
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T4Insert) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto s21_it = s21_vector.begin();
  s21_it = s21_vector.insert(s21_it, Item(10));
  s21_it += 2;
  s21_vector.insert(s21_it, Item(10));

  std::vector<Item> vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  auto it = vector.begin();
  it = vector.insert(it, Item(10));
  it += 2;
  vector.insert(it, Item(10));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T0InsertMany) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  s21::Vector<Item> s21_vector_result = {Item(10), Item(20), Item(1), Item(2),
                                         Item(3),  Item(4),  Item(5)};
  auto s21_it = s21_vector.begin();
  s21_it = s21_vector.insert_many(s21_it, Item(10), Item(20));

  EXPECT_EQ(s21_vector, s21_vector_result);
}

TEST(vector, T1InsertMany) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  s21::Vector<Item> s21_vector_result = {Item(1), Item(2), Item(10), Item(20),
                                         Item(3), Item(4), Item(5)};
  auto s21_it = s21_vector.begin() + 2;
  s21_it = s21_vector.insert_many(s21_it, Item(10), Item(20));

  EXPECT_EQ(s21_vector, s21_vector_result);
}

TEST(vector, T2InsertMany) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  s21::Vector<Item> s21_vector_result = {Item(1),  Item(2),   Item(10),
                                         Item(20), Item(100), Item(200),
                                         Item(3),  Item(4),   Item(5)};
  auto s21_it = s21_vector.begin() + 2;
  s21_it = s21_vector.insert_many(s21_it, Item(10), Item(20));
  s21_vector.insert_many(s21_it, Item(100), Item(200));

  EXPECT_EQ(s21_vector, s21_vector_result);
}

TEST(vector, T3InsertMany) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  s21::Vector<Item> s21_vector_result = {Item(1), Item(2),  Item(3),  Item(4),
                                         Item(5), Item(10), Item(20), Item(30)};
  s21_vector.insert_many_back(Item(10), Item(20), Item(30));

  EXPECT_EQ(s21_vector, s21_vector_result);
}

TEST(vector, T4InsertMany) {
  s21::Vector<Item> s21_vector = {Item(1), Item(2), Item(3), Item(4), Item(5)};
  s21::Vector<Item> s21_vector_result = {Item(1), Item(2),  Item(3), Item(4),
                                         Item(5), Item(10), Item(20)};
  auto s21_it = s21_vector.end();
  s21_vector.insert_many(s21_it, Item(10), Item(20));

  EXPECT_EQ(s21_vector, s21_vector_result);
}

}  // namespace

// GCOVR_EXCL_STOP