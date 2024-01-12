#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <list>
#include <stack>

#include "../../array/s21_array.h"
#include "../array_helpers.h"
#include "../item.h"

// GCOVR_EXCL_START

namespace {

TEST(ArrayTest, CopyConstructorFromChatGPT) {
  s21::Array<int, 5> arr1;
  s21::Array<int, 5> arr2(arr1);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
  arr1[0] = 42;
  EXPECT_NE(arr1[0], arr2[0]);
  s21::Array<int, 5> arr3(arr1);
  EXPECT_EQ(arr1, arr3);
  s21::Array<int, 5> arr4;
  EXPECT_NE(arr1, arr4);
  s21::Array<int, 5> arr5;
  std::copy(arr1.begin(), arr1.end(), arr5.begin());
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], arr5[i]);
  }
}

TEST(Array, T00ConstructorInitializer) {
  s21::Array<int, 4> a1{1, 2, 3};
  s21::Array<int, 4> a2{1, 2, 3};
  a1.print();
  EXPECT_EQ(a1, a2);
}

TEST(Array, T01ConstructorInitializer) {
  s21::Array<int, 4> a1;
  s21::Array<int, 4> a2;
  // std::cout << a1[3] << '\n';
  // std::cout << a2[3] << '\n';
  EXPECT_EQ(a1, a2);
}

TEST(Array, T02ConstructorInitializer) {
  s21::Array<Item, 0> a1;
  s21::Array<Item, 0> a2;
  // std::cout << a1[3] << '\n';
  // std::cout << a2[3] << '\n';
  EXPECT_EQ(a1, a2);
  EXPECT_TRUE(a1.empty());
}

TEST(Array, T0ConstructorInitializer) {
  s21::Array<int, 3> a1{1, 2};
  std::array<int, 3> array{1, 2};
  std::cout << a1[2] << '\n';
  std::cout << array[2] << '\n';
  EXPECT_EQ(a1, array);
}

TEST(Array, T1ConstructorInitializer) {
  s21::Array<Item, 3> s21_array{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::array<Item, 3> array{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T2ConstructorInitializer) {
  s21::Array<Item, 3> s21_array{Item(11), Item(22, 'b')};
  std::array<Item, 3> array{Item(11), Item(22, 'b'), Item()};

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T0ConstructorCopy) {
  const s21::Array<Item, 3> s21_source{Item(11), Item(22, 'b'),
                                       Item(33, 'c', 0.3333)};
  const std::array<Item, 3> source{Item(11), Item(22, 'b'),
                                   Item(33, 'c', 0.3333)};

  s21::Array<Item, 3> s21_array(s21_source);
  std::array<Item, 3> array(source);

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T1ConstructorCopy) {
  const s21::Array<Item, 2> s21_source{Item(33, 'i', 0.3333),
                                       Item(33, 'c', 0.3333)};
  const std::array<Item, 2> source{Item(33, 'i', 0.3333),
                                   Item(33, 'c', 0.3333)};

  s21::Array<Item, 2> s21_array(s21_source);
  std::array<Item, 2> array(source);

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T2ConstructorCopy) {
  const s21::Array<Item, 2> s21_source;
  const std::array<Item, 2> source;

  s21::Array<Item, 2> s21_array(s21_source);
  std::array<Item, 2> array(source);

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T0ConstructorMove) {
  s21::Array<Item, 3> s21_source{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};
  std::array<Item, 3> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21::Array<Item, 3> s21_array(std::move(s21_source));
  std::array<Item, 3> array(std::move(source));

  EXPECT_EQ(s21_array, array);
  EXPECT_EQ(s21_source, source);
  // s21_array.print();
  // s21_source.print();
  // EXPECT_TRUE(s21_source.empty());
  // EXPECT_TRUE(source.empty());
}

TEST(Array, T1ConstructorMove) {
  s21::Array<Item, 3> s21_source;
  std::array<Item, 3> source;

  s21::Array<Item, 3> s21_array(std::move(s21_source));
  std::array<Item, 3> array(std::move(source));

  EXPECT_EQ(s21_array, array);
  EXPECT_EQ(s21_source, source);
  // EXPECT_TRUE(s21_source.empty());
  // EXPECT_TRUE(s21_array.empty());
}

TEST(Array, T11OperatorCopy) {
  const s21::Array<Item, 3> s21_source{Item(11), Item(22, 'b'),
                                       Item(33, 'c', 0.3333)};
  const std::array<Item, 3> source{Item(11), Item(22, 'b'),
                                   Item(33, 'c', 0.3333)};

  s21::Array<Item, 3> s21_array;
  s21_array = s21_source;
  std::array<Item, 3> array;
  array = source;

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T13OperatorCopy) {
  const s21::Array<Item, 3> s21_source{Item(11), Item(22, 'b'),
                                       Item(33, 'c', 0.3333)};
  const std::array<Item, 3> source{Item(11), Item(22, 'b'),
                                   Item(33, 'c', 0.3333)};

  s21::Array<Item, 3> s21_array{Item(1999), Item(22, 'h'),
                                Item(33, 'c', 0.3333)};
  s21_array = s21_source;
  std::array<Item, 3> array{Item(1999), Item(22, 'h'), Item(33, 'c', 0.3333)};
  array = source;

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T0OperatorMove) {
  const s21::Array<Item, 3> s21_source{Item(11), Item(22, 'b'),
                                       Item(33, 'c', 0.3333)};
  const std::array<Item, 3> source{Item(11), Item(22, 'b'),
                                   Item(33, 'c', 0.3333)};

  s21::Array<Item, 3> s21_array{Item(1999), Item(22, 'h'),
                                Item(33, 'c', 0.3333)};
  s21_array = std::move(s21_source);
  std::array<Item, 3> array{Item(1999), Item(22, 'h'), Item(33, 'c', 0.3333)};
  array = std::move(source);

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T15ConstructorCopySelf) {
  s21::Array<Item, 3> s21_array{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  auto &a = s21_array;
  s21_array = a;
  std::array<Item, 3> array{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  auto &b = array;
  array = b;
  // array = array;

  EXPECT_EQ(s21_array, array);
}

TEST(Array, T16Constructor) {
  s21::Array<Item, 5> s21_array{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::array<Item, 5> s21_array_expected{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(), Item(),
  };

  EXPECT_EQ(s21_array, s21_array_expected);
}

}  // namespace

// GCOVR_EXCL_STOP
