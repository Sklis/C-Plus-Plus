#include <gtest/gtest.h>

#include <deque>
#include <iterator>
#include <list>
#include <stack>
#include <vector>

// #include "../../s21_list.h"
#include "../../vector/s21_vector.h"
#include "../item.h"
// #include "../list_helpers.h"
#include "../vector_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(vector, T0PushBackMove) {
  s21::Vector<Item> s21_vector;
  s21_vector.push_back(Item(111));
  s21_vector.push_back(Item(222, 'b'));
  s21_vector.push_back(Item(333, 'c', 0.333));

  std::vector<Item> vector;
  vector.push_back(Item(111));
  vector.push_back(Item(222, 'b'));
  vector.push_back(Item(333, 'c', 0.333));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T1PushBackMove) {
  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.push_back(Item(111));
  s21_vector.push_back(Item(111));
  s21_vector.push_back(Item(222, 'b'));
  s21_vector.push_back(Item(222, 'b'));
  s21_vector.push_back(Item(333, 'c', 0.333));
  s21_vector.push_back(Item(333, 'c', 0.333));

  vector.push_back(Item(111));
  vector.push_back(Item(111));
  vector.push_back(Item(222, 'b'));
  vector.push_back(Item(222, 'b'));
  vector.push_back(Item(333, 'c', 0.333));
  vector.push_back(Item(333, 'c', 0.333));

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T2PushBack) {
  const Item item1(111);
  const Item item2(222, 'b');
  const Item item3(333, 'c', 0.333);

  s21::Vector<Item> s21_vector;
  s21_vector.push_back(item1);
  s21_vector.push_back(item2);
  s21_vector.push_back(item3);

  std::vector<Item> vector;
  vector.push_back(item1);
  vector.push_back(item2);
  vector.push_back(item3);

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T3PushBack) {
  const Item item1(111);
  const Item item2(222, 'b');
  const Item item3(333, 'c', 0.333);

  s21::Vector<Item> s21_vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};
  std::vector<Item> vector{Item(11), Item(22, 'b'), Item(33, 'c', 0.3333)};

  s21_vector.push_back(item1);
  s21_vector.push_back(item1);
  s21_vector.push_back(item2);
  s21_vector.push_back(item2);
  s21_vector.push_back(item3);
  s21_vector.push_back(item3);

  vector.push_back(item1);
  vector.push_back(item1);
  vector.push_back(item2);
  vector.push_back(item2);
  vector.push_back(item3);
  vector.push_back(item3);

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T5Insert) {
  const Item item(666);

  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin() + 1;
  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);

  // s21::Vector<Item>::const_iterator s21_it = s21_vector.begin();  // TODO:
  // так тоже должно работать, но не работает

  std::vector<Item>::const_iterator it = vector.cbegin() + 1;
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T0InsertThrow) {
  const Item item(666);
  s21::Vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};
  s21::Vector<Item>::const_iterator it = vector.cbegin() + 100;

  EXPECT_THROW(vector.insert(it, item), std::out_of_range);
}

TEST(vector, T6InsertBegin) {
  const Item item(666);

  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin();
  std::vector<Item>::const_iterator it = vector.cbegin();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T7InsertEnd) {
  const Item item(666);

  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend();
  std::vector<Item>::const_iterator it = vector.cend();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T8Insert) {
  const Item item(666);

  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend() - 2;
  std::vector<Item>::const_iterator it = vector.cend() - 2;

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T9InsertEmptyBegin) {
  const Item item(666);

  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin();
  std::vector<Item>::const_iterator it = vector.cbegin();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T10InsertEmptyEnd) {
  const Item item(666);

  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend();
  std::vector<Item>::const_iterator it = vector.cend();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, item);
  const std::vector<Item>::iterator result = vector.insert(it, item);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T11InsertMove) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin() + 1;
  std::vector<Item>::const_iterator it = vector.cbegin() + 1;

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T12InsertMoveBegin) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin();
  std::vector<Item>::const_iterator it = vector.cbegin();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T13InsertMoveEnd) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend();
  std::vector<Item>::const_iterator it = vector.cend();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T14InsertNove) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend() - 2;
  std::vector<Item>::const_iterator it = vector.cend() - 2;

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T15InsertMoveEmptyBegin) {
  const Item item(666);

  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin();
  std::vector<Item>::const_iterator it = vector.cbegin();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T16InsertMoveEmptyEnd) {
  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cend();
  std::vector<Item>::const_iterator it = vector.cend();

  const s21::Vector<Item>::iterator s21_result =
      s21_vector.insert(s21_it, Item(666));
  const std::vector<Item>::iterator result = vector.insert(it, Item(666));

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T50EraseBegin) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin();
  std::vector<Item>::const_iterator it = vector.cbegin();

  const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
  const std::vector<Item>::iterator result = vector.erase(it);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T501Erase) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::iterator s21_it = s21_vector.begin();
  std::vector<Item>::iterator it = vector.begin();

  const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
  const std::vector<Item>::iterator result = vector.erase(it);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T51Erase) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin() + 1;
  std::vector<Item>::const_iterator it = vector.cbegin() + 1;

  const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
  const std::vector<Item>::iterator result = vector.erase(it);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T52Erase) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin() + 2;
  std::vector<Item>::const_iterator it = vector.cbegin() + 2;

  const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
  const std::vector<Item>::iterator result = vector.erase(it);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T53Erase) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  std::vector<Item> vector{Item(0), Item(111), Item(222), Item(333)};

  s21::Vector<Item>::const_iterator s21_it = s21_vector.cbegin() + 3;
  std::vector<Item>::const_iterator it = vector.cbegin() + 3;

  const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
  const std::vector<Item>::iterator result = vector.erase(it);

  EXPECT_EQ(s21_vector, vector);
  EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T54Erase) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  s21::Vector<Item>::const_iterator it = s21_vector.cbegin() + 30;

  EXPECT_THROW(s21_vector.erase(it), std::out_of_range);
}

TEST(vector, T0Erase_cut) {
  s21::Vector<Item> s21_vector{Item(0), Item(111), Item(222), Item(333)};
  s21::Vector<Item> s21_vector_result{Item(222), Item(333)};

  s21::Vector<Item>::const_iterator it1 = s21_vector.cbegin();
  s21::Vector<Item>::const_iterator it2 = it1 + 2;

  s21_vector.erase(it1, it2);

  EXPECT_FALSE(s21_vector != s21_vector_result);
  // EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T1Erase_cut) {
  s21::Vector<Item> s21_vector{Item(0), Item(11), Item(22), Item(33), Item(44)};
  s21::Vector<Item> s21_vector_result{Item(0), Item(11), Item(44)};

  s21::Vector<Item>::const_iterator it1 = s21_vector.cbegin() + 2;
  s21::Vector<Item>::const_iterator it2 = it1 + 2;

  s21_vector.erase(it1, it2);

  EXPECT_FALSE(s21_vector != s21_vector_result);
  // EXPECT_EQ(*s21_result, *result);
}

TEST(vector, T2Erase_cut) {
  s21::Vector<Item> s21_vector{Item(0),  Item(11), Item(22),
                               Item(33), Item(44), Item(55)};
  s21::Vector<Item> s21_vector_result{Item(0), Item(11), Item(22)};

  s21::Vector<Item>::const_iterator it1 = s21_vector.begin() + 3;
  s21::Vector<Item>::const_iterator it2 = it1 + 3;

  s21_vector.erase(it1, it2);

  EXPECT_FALSE(s21_vector != s21_vector_result);
}

TEST(vector, T3Erase_cut) {
  s21::Vector<Item> s21_vector{Item(0),  Item(11), Item(22),
                               Item(33), Item(44), Item(55)};

  s21::Vector<Item>::const_iterator it1 = s21_vector.begin() + 30;
  s21::Vector<Item>::const_iterator it2 = it1 + 3;

  EXPECT_THROW(s21_vector.erase(it2, it1), std::out_of_range);
}

TEST(vector, T4Erase_cut) {
  s21::Vector<Item> s21_vector{Item(0),  Item(11), Item(22),
                               Item(33), Item(44), Item(55)};

  s21::Vector<Item>::const_iterator it1 = s21_vector.begin();
  s21::Vector<Item>::const_iterator it2 = it1 + 4;

  EXPECT_THROW(s21_vector.erase(it2, it1), std::out_of_range);
}

// TEST(vector, T54EraseEnd) {
//   s21::Vector<Item> s21_vector { Item(0), Item(111), Item(222), Item(333)
//   }; std::vector<Item> vector { Item(0), Item(111), Item(222), Item(333) };

//   s21::Vector<Item>::const_iterator s21_it = s21_vector.cend();
//   std::vector<Item>::const_iterator it = vector.cend();

//   const s21::Vector<Item>::iterator s21_result = s21_vector.erase(s21_it);
//   const std::vector<Item>::iterator result = vector.erase(it);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(s21_result, s21_it);
//   EXPECT_EQ(result, it);
// }

// TEST(vector, T55EraseRange) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin();
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cbegin() + 3;
//   std::vector<Item>::const_iterator it1 = vector.cbegin();
//   std::vector<Item>::const_iterator it2 = vector.cbegin() + 3;

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T56EraseRange) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin() + 1;
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cbegin() + 3;
//   std::vector<Item>::const_iterator it1 = vector.cbegin() + 1;
//   std::vector<Item>::const_iterator it2 = vector.cbegin() + 3;

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T57EraseRange) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin() + 2;
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cbegin() + 6;
//   std::vector<Item>::const_iterator it1 = vector.cbegin() + 2;
//   std::vector<Item>::const_iterator it2 = vector.cbegin() + 6;

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T58EraseRange) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin() + 4;
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cend();
//   std::vector<Item>::const_iterator it1 = vector.cbegin() + 4;
//   std::vector<Item>::const_iterator it2 = vector.cend();

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T59EraseRange) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cend() - 4;
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cend();
//   std::vector<Item>::const_iterator it1 = vector.cend() - 4;
//   std::vector<Item>::const_iterator it2 = vector.cend();

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T60EraseRangeFull) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin();
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cend();
//   std::vector<Item>::const_iterator it1 = vector.cbegin();
//   std::vector<Item>::const_iterator it2 = vector.cend();

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(*s21_result, *result);
// }

// TEST(vector, T61EraseRangeEmpty) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cbegin();
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cbegin();
//   std::vector<Item>::const_iterator it1 = vector.cbegin();
//   std::vector<Item>::const_iterator it2 = vector.cbegin();

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(s21_result, s21_it1);
//   EXPECT_EQ(result, it1);
// }

// TEST(vector, T62EraseRangeEmpty) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cend();
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cend();
//   std::vector<Item>::const_iterator it1 = vector.cend();
//   std::vector<Item>::const_iterator it2 = vector.cend();

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(s21_result, s21_it1);
//   EXPECT_EQ(result, it1);
// }

// TEST(vector, T63EraseRangeEmpty) {
//   s21::Vector<Item> s21_vector{Item(0),   Item(111), Item(222),
//                                Item(333), Item(444), Item(555),
//                                Item(666), Item(777), Item(888)};
//   std::vector<Item> vector{Item(0),   Item(111), Item(222),
//                            Item(333), Item(444), Item(555),
//                            Item(666), Item(777), Item(888)};

//   s21::Vector<Item>::const_iterator s21_it1 = s21_vector.cend() - 2;
//   s21::Vector<Item>::const_iterator s21_it2 = s21_vector.cend() - 2;
//   std::vector<Item>::const_iterator it1 = vector.cend() - 2;
//   std::vector<Item>::const_iterator it2 = vector.cend() - 2;

//   const s21::Vector<Item>::iterator s21_result =
//       s21_vector.erase(s21_it1, s21_it2);
//   const std::vector<Item>::iterator result = vector.erase(it1, it2);

//   EXPECT_EQ(s21_vector, vector);
//   EXPECT_EQ(s21_result, s21_it1);
//   EXPECT_EQ(result, it1);
// }

TEST(vector, T64Swap) {
  s21::Vector<Item> s21_vector1{Item(0),   Item(111), Item(222),
                                Item(333), Item(444), Item(555),
                                Item(666), Item(777), Item(888)};
  s21::Vector<Item> s21_vector2{Item(0),   Item(111), Item(222),
                                Item(333), Item(444), Item(555),
                                Item(666), Item(777), Item(888)};

  const s21::Vector<Item> s21_vector1_copy = s21_vector1;
  const s21::Vector<Item> s21_vector2_copy = s21_vector2;

  s21_vector1.swap(s21_vector2);

  EXPECT_EQ(s21_vector1, s21_vector2_copy);
  EXPECT_EQ(s21_vector2, s21_vector1_copy);
}

TEST(vector, T65SwapEmpty) {
  s21::Vector<Item> s21_vector1;
  s21::Vector<Item> s21_vector2{Item(0),   Item(111), Item(222),
                                Item(333), Item(444), Item(555),
                                Item(666), Item(777), Item(888)};

  const s21::Vector<Item> s21_vector1_copy = s21_vector1;
  const s21::Vector<Item> s21_vector2_copy = s21_vector2;

  s21_vector1.swap(s21_vector2);

  EXPECT_EQ(s21_vector1, s21_vector2_copy);
  EXPECT_EQ(s21_vector2, s21_vector1_copy);
}

TEST(vector, T66SwapEmpty) {
  s21::Vector<Item> s21_vector1{Item(0),   Item(111), Item(222),
                                Item(333), Item(444), Item(555),
                                Item(666), Item(777), Item(888)};
  s21::Vector<Item> s21_vector2;

  const s21::Vector<Item> s21_vector1_copy = s21_vector1;
  const s21::Vector<Item> s21_vector2_copy = s21_vector2;

  s21_vector1.swap(s21_vector2);

  EXPECT_EQ(s21_vector1, s21_vector2_copy);
  EXPECT_EQ(s21_vector2, s21_vector1_copy);
}

TEST(vector, T67Swap) {
  s21::Vector<Item> s21_vector1{Item(0),   Item(111), Item(333), Item(444),
                                Item(555), Item(666), Item(777), Item(888)};
  s21::Vector<Item> s21_vector2{Item(0),   Item(222), Item(333), Item(444),
                                Item(555), Item(666), Item(777), Item(888)};

  const s21::Vector<Item> s21_vector1_copy = s21_vector1;
  const s21::Vector<Item> s21_vector2_copy = s21_vector2;

  s21_vector1.swap(s21_vector2);

  EXPECT_EQ(s21_vector1, s21_vector2_copy);
  EXPECT_EQ(s21_vector2, s21_vector1_copy);
}

TEST(vector, T68Swap) {
  s21::Vector<Item> s21_vector1{Item(0), Item(555), Item(666), Item(777),
                                Item(888)};
  s21::Vector<Item> s21_vector2{Item(0),   Item(222), Item(333), Item(444),
                                Item(555), Item(666), Item(777), Item(888)};

  const s21::Vector<Item> s21_vector1_copy = s21_vector1;
  const s21::Vector<Item> s21_vector2_copy = s21_vector2;

  s21_vector1.swap(s21_vector2);

  EXPECT_EQ(s21_vector1, s21_vector2_copy);
  EXPECT_EQ(s21_vector2, s21_vector1_copy);
}

TEST(vector, T69Clear) {
  s21::Vector<Item> s21_vector{Item(0), Item(555), Item(666), Item(777),
                               Item(888)};
  std::vector<Item> vector{Item(0),   Item(555), Item(666),
                           Item(777), Item(888), Item(999)};

  s21_vector.clear();
  vector.clear();
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T70Clear) {
  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  s21_vector.clear();
  vector.clear();
  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T71Clear) {
  s21::Vector<Item> s21_vector{Item(0), Item(555), Item(666), Item(777),
                               Item(888)};
  std::vector<Item> vector{Item(0),   Item(555), Item(666),
                           Item(777), Item(888), Item(999)};

  s21_vector.clear();
  EXPECT_NE(s21_vector, vector);
}

TEST(vector, T72Empty) {
  s21::Vector<Item> s21_vector{Item(0), Item(555), Item(666), Item(777),
                               Item(888)};
  std::vector<Item> vector{Item(0),   Item(555), Item(666),
                           Item(777), Item(888), Item(999)};

  EXPECT_EQ(s21_vector.empty(), vector.empty());
}

TEST(vector, T73Empty) {
  s21::Vector<Item> s21_vector;
  std::vector<Item> vector;

  EXPECT_EQ(s21_vector.empty(), vector.empty());
}

TEST(vector, T74Pop_back) {
  s21::Vector<Item> s21_vector{
      Item(0), Item(555), Item(666), Item(777), Item(888),
  };
  std::vector<Item> vector{
      Item(0), Item(555), Item(666), Item(777), Item(888),
  };

  s21_vector.pop_back();
  s21_vector.pop_back();

  vector.pop_back();
  vector.pop_back();

  EXPECT_EQ(s21_vector, vector);
}

TEST(vector, T75Pop_back) {
  s21::Vector<Item> s21_vector{Item(0)};
  std::vector<Item> vector{Item(0)};

  s21_vector.pop_back();
  s21_vector.pop_back();

  vector.pop_back();
  // vector.pop_back();

  EXPECT_EQ(s21_vector, vector);
}

// TEST(vector, T75Resize) {
//   s21::Vector<Item> s21_vector{
//       Item(0), Item(555), Item(666), Item(777), Item(888),
//   };
//   std::vector<Item> vector{
//       Item(0), Item(555), Item(666), Item(777), Item(888),
//   };

//   s21_vector.resize(5);
//   vector.resize(5);

//   EXPECT_EQ(s21_vector, vector);
// }

// TEST(vector, T82Resize) {
//   s21::Vector<Item> s21_vector{
//       Item(0), Item(555), Item(666), Item(777), Item(888),
//   };
//   std::vector<Item> vector{
//       Item(0), Item(555), Item(666), Item(777), Item(888),
//   };

//   const Item item(6666, 'h', 0.66666);
//   s21_vector.resize(20, item);
//   vector.resize(20, item);

//   EXPECT_EQ(s21_vector, vector);
// }

}  // namespace

// GCOVR_EXCL_STOP
