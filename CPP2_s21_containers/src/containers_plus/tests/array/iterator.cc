#include <gtest/gtest.h>

#include <array>

#include "../../array/s21_array.h"
// #include "../../s21_vector.h"
#include "../array_helpers.h"
#include "../item.h"

// GCOVR_EXCL_START

namespace {

TEST(Vector, T10IteratorOperatorPlus) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::iterator s21_it = s21_source.begin();
  std::array<Item, 4>::iterator it = source.begin();

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(++s21_it), *(++it));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T11IteratorOperatorPlusPostfix) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::iterator s21_it = s21_source.begin();
  std::array<Item, 4>::iterator it = source.begin();

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(s21_it++), *(it++));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T12IteratorOperatorMinus) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::iterator s21_it = s21_source.end() - 1;
  std::array<Item, 4>::iterator it = source.end() - 1;

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(--s21_it), *(--it));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T13IteratorOperatorMinusPostfix) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::iterator s21_it = s21_source.end() - 1;
  std::array<Item, 4>::iterator it = source.end() - 1;

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(s21_it--), *(it--));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T15IteratorOperatorSubscript) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  Item s21_item = s21_source.begin()[2];
  Item item = source.begin()[2];

  EXPECT_EQ(s21_item, item);
}

TEST(Vector, T16IteratorOperatorSubscript) {
  s21::Array<Item, 4> s21_source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                                 Item(44, 'd', 0.44444)};
  std::array<Item, 4> source{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333),
                             Item(44, 'd', 0.44444)};

  Item s21_item = s21_source.end()[-2];
  Item item = source.end()[-2];

  EXPECT_EQ(s21_item, item);
}

TEST(Vector, T25ConstIteratorOperatorPlus) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::const_iterator s21_it = s21_source.begin();
  std::array<Item, 4>::const_iterator it = source.begin();

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(++s21_it), *(++it));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T26ConstIteratorOperatorPlusPostfix) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::const_iterator s21_it = s21_source.begin();
  std::array<Item, 4>::const_iterator it = source.begin();

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(s21_it++), *(it++));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T27ConstIteratorOperatorMinus) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::const_iterator s21_it = s21_source.end() - 1;
  std::array<Item, 4>::const_iterator it = source.end() - 1;

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(--s21_it), *(--it));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T28ConstIteratorOperatorMinusPostfix) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  s21::Array<Item, 4>::const_iterator s21_it = s21_source.end() - 1;
  std::array<Item, 4>::const_iterator it = source.end() - 1;

  EXPECT_EQ(*s21_it, *it);
  EXPECT_EQ(*(s21_it--), *(it--));
  EXPECT_EQ(*s21_it, *it);
}

TEST(Vector, T30ConstIteratorOperatorSubscript) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  Item s21_item = s21_source.begin()[2];
  Item item = source.begin()[2];

  EXPECT_EQ(s21_item, item);
}

TEST(Vector, T31IteratorOperatorSubscript) {
  const s21::Array<Item, 4> s21_source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};
  const std::array<Item, 4> source{
      Item(11), Item(22, 'b'), Item(33, 'c', 0.3333), Item(44, 'd', 0.44444)};

  Item s21_item = s21_source.end()[-2];
  Item item = source.end()[-2];

  EXPECT_EQ(s21_item, item);
}

}  // namespace

// GCOVR_EXCL_STOP
