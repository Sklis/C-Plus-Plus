#include <gtest/gtest.h>

#include <list>
#include <set>

#include "../../multiset/s21_multiset.h"

// GCOVR_EXCL_START

namespace {
TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> mySet;
  ASSERT_TRUE(mySet.empty());
  ASSERT_EQ(mySet.size(), 0);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> mySet = {1, 2, 3};
  auto it = mySet.begin();
  mySet.erase(it);
  ASSERT_EQ(mySet.size(), 2);
  ASSERT_EQ(*mySet.begin(), 2);
}

TEST(MultisetTest, LowerUpperBound) {
  s21::multiset<int> mySet = {1, 2, 2, 3, 3, 3};
  auto lower = mySet.lower_bound(2);
  auto upper = mySet.upper_bound(2);

  ASSERT_EQ(*lower, 2);  // Первое вхождение 2
  ASSERT_EQ(*upper, 3);  // Первое вхождение, не равное 2
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> originalSet = {1, 2, 3};
  s21::multiset<int> copySet(originalSet);
  ASSERT_EQ(originalSet.size(), copySet.size());
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> originalSet = {1, 2, 3};
  s21::multiset<int> moveSet(std::move(originalSet));
  ASSERT_TRUE(originalSet.empty());
  ASSERT_FALSE(moveSet.empty());
}

TEST(multiset, init) {
  s21::multiset<int> test = {52, 52, 45, 48, 53};
  std::multiset<int> test2 = {52, 52, 45, 48, 53};
  std::multiset<int>::iterator it;
  s21::multiset<int>::iterator it2 = test.begin();
  for (it = test2.begin(); it != test2.end(); it++) {
    ASSERT_EQ(*it, *it2);
    it2++;
  }
}

TEST(multiset, lower) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  s21::multiset<int>::iterator it2;
  it2 = test.lower_bound(-2);
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::multiset<int>::iterator it3;
  it3 = test2.lower_bound(-2);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, upper) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  s21::multiset<int>::iterator it2;
  it2 = test.upper_bound(52);
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::multiset<int>::iterator it3;
  it3 = test2.upper_bound(52);
  EXPECT_EQ(*it2, *it3);
}

TEST(multiset, range) {
  s21::multiset<int> test = {52, 54, 45, 48, 53};
  std::multiset<int> test2 = {52, 54, 45, 48, 53};
  std::pair<s21::multiset<int>::iterator, s21::multiset<int>::iterator> check =
      test.equal_range(2);
  std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> check2 =
      test2.equal_range(2);
  EXPECT_EQ(*check.first, *check2.first);
  EXPECT_EQ(*check.second, *check2.second);
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> mySet;
  auto result1 = mySet.insert(42);
  ASSERT_TRUE(result1.second);
  ASSERT_EQ(result1.first, mySet.begin());
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> mySet = {1, 2, 3};
  ASSERT_FALSE(mySet.empty());

  mySet.clear();
  ASSERT_TRUE(mySet.empty());
  ASSERT_EQ(mySet.size(), 0);
}
}  // namespace