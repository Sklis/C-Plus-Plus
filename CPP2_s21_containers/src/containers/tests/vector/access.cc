#include <gtest/gtest.h>

#include <vector>

#include "../../vector/s21_vector.h"
#include "../item.h"
#include "../vector_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(vector, T0Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[0], vector[0]);
}

TEST(vector, T1Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[1], vector[1]);
}

TEST(vector, T2Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[2], vector[2]);
}

TEST(vector, T3Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const Item item(666, 'h', 0.666666);
  s21_vector[0] = item;
  vector[0] = item;
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T4Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const Item item(666, 'h', 0.666666);
  s21_vector[1] = item;
  vector[1] = item;
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T5Operator) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const Item item(666, 'h', 0.666666);
  s21_vector[2] = item;
  vector[2] = item;
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T6Operator) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[0], vector[0]);
}

TEST(vector, T7Operator) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[1], vector[1]);
}

TEST(vector, T8Operator) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector[2], vector[2]);
}

TEST(vector, T9At) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(0), vector.at(0));
}

TEST(vector, T10At) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(1), vector.at(1));
}

TEST(vector, T11At) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(2), vector.at(2));
}

TEST(vector, T12AtOutOfRange) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_THROW(s21_vector.at(99), std::out_of_range);
}

TEST(vector, T13At) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const Item item0(6666, 'h', 0.666666);
  const Item item1(7777, 'j', 0.777777);
  const Item item2(8888, 'k', 0.888888);
  s21_vector.at(0) = item0;
  s21_vector.at(1) = item1;
  s21_vector.at(2) = item2;
  vector.at(0) = item0;
  vector.at(1) = item1;
  vector.at(2) = item2;

  EXPECT_EQ(s21_vector.at(0), vector.at(0));
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T14AtOutOfRange) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  const Item item0(6666, 'h', 0.666666);
  EXPECT_THROW(s21_vector.at(99) = item0, std::out_of_range);
}

TEST(vector, T15AtOutOfRange) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};

  EXPECT_THROW(s21_vector.at(99), std::out_of_range);
}

TEST(vector, T16At) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(0), vector.at(0));
}

TEST(vector, T17At) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(1), vector.at(1));
}

TEST(vector, T18At) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.at(2), vector.at(2));
}

TEST(vector, T19AtOutOfRange) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  EXPECT_THROW(s21_vector.at(10), std::out_of_range);
}

TEST(vector, T20AtOutOfRange) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  EXPECT_THROW(s21_vector.at(-1), std::out_of_range);
}

TEST(vector, T21AtOutOfRange) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  EXPECT_THROW(s21_vector.at(123), std::out_of_range);
}

TEST(vector, T22Front) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.front(), vector.front());
}

// TEST(vector, T23Front) {
//   s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c',
//   0.3333)}; std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c',
//   0.3333)};

//   s21_vector.front() = Item(666);
//   vector.front() = Item(666);

//   EXPECT_EQ(s21_vector, vector);
// }

TEST(vector, T24Back) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  EXPECT_EQ(s21_vector.back(), vector.back());
}

// TEST(vector, T25Back) {
//   s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c',
//   0.3333)}; std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c',
//   0.3333)};

//   s21_vector.back() = Item(666);
//   vector.back() = Item(666);

//   EXPECT_EQ(s21_vector, vector);
// }

TEST(vector, T26Data) {
  const s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'),
                                     Item(33, 'c', 0.3333)};
  const std::vector<Item> vector{Item(11), Item(22, 'b'),
                                 Item(33, 'c', 0.3333)};

  const Item* s21_data = s21_vector.data();
  const Item* data = vector.data();

  EXPECT_EQ(s21_data[0], data[0]);
  EXPECT_EQ(s21_data[1], data[1]);
  EXPECT_EQ(s21_data[2], data[2]);
}

TEST(vector, T27Data) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  Item* s21_data = s21_vector.data();
  Item* data = vector.data();

  s21_data[1] = Item(666);
  data[1] = Item(666);

  EXPECT_EQ(s21_data[0], data[0]);
  EXPECT_EQ(s21_data[1], data[1]);
  EXPECT_EQ(s21_data[2], data[2]);
}

}  // namespace

// GCOVR_EXCL_STOP
