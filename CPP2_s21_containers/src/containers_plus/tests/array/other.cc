#include <gtest/gtest.h>

#include <array>

#include "../../array/s21_array.h"
#include "../array_helpers.h"
#include "../item.h"

// GCOVR_EXCL_START

namespace {

TEST(Array, T0OperatorEqual) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  EXPECT_EQ(s21_source, source);
}

TEST(Array, T1OperatorEqual) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(55, 'e', 0.55555555)};

  EXPECT_NE(s21_source, source);
}

TEST(Array, T2OperatorEqual) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(6666), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  EXPECT_TRUE(s21_source != source);
}

TEST(Array, T3OperatorEqual) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  s21::Array<Item, 3> source{Item(6666), Item(22, 'b'), Item(44, 'd', 0.44444)};

  EXPECT_TRUE(s21_source != source);
}

TEST(Array, T0IndexOut) {
  s21::Array<Item, 4> a{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                        Item(44, 'd', 0.44444)};

  EXPECT_THROW(a[4] = Item(1), std::out_of_range);
}

TEST(Array, T0Swap0) {
  s21::Array<Item, 9> s21_array1{Item(0),   Item(111), Item(222, 'q', 0.222),
                                 Item(333), Item(454), Item(555),
                                 Item(666), Item(777), Item(888)};
  s21::Array<Item, 9> s21_array2{Item(0),   Item(111), Item(221),
                                 Item(333), Item(444), Item(555),
                                 Item(676), Item(777), Item(888)};

  const s21::Array<Item, 9> s21_array1_copy = s21_array1;
  const s21::Array<Item, 9> s21_array2_copy = s21_array2;

  s21_array1.swap(s21_array2);

  EXPECT_EQ(s21_array1, s21_array2_copy);
  EXPECT_EQ(s21_array2, s21_array1_copy);
}

// TEST(Array, T0Empty) {
//   s21::Array<Item, 0> arr;

//   EXPECT_TRUE(arr.empty());
// }

TEST(Array, T0MaxSize) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  EXPECT_EQ(s21_source.max_size(), source.max_size());
}

TEST(Array, T0Fill) {
  s21::Array<Item, 4> arr;
  s21::Array<Item, 4> check{Item(22, 'b'), Item(22, 'b'), Item(22, 'b'),
                            Item(22, 'b')};
  arr.fill(Item(22, 'b'));

  EXPECT_EQ(arr, check);
}

}  // namespace

// GCOVR_EXCL_STOP
