#include <gtest/gtest.h>

#include <map>

#include "../../map/s21_map.h"

// template <typename Key, typename Value>
// bool s21::Map::operator==(const typename s21::Map<const Key, const Value>&
// left,
//                 const typename s21::Map<const Key, const Value>& right) {
//   bool res = true;
//   auto l_it = left.begin();
//   auto r_it = right.begin();
//   for (; l_it != left.end() && res; ++l_it, ++r_it) {
//     res = *l_it == *r_it;
//   }
//   return res;
// }

// template <typename Key, typename Value>
// bool s21::Map::operator==(const typename s21::Map<const Key, const Value>&
// left,
//                 const typename std::map<const Key, const Value>& right) {
//   bool res = true;
//   auto l_it = left.begin();
//   auto r_it = right.begin();
//   for (; l_it != left.end() && res; ++l_it, ++r_it) {
//     res = *l_it == r_it->second;
//   }
//   return res;
// }

// GCOVR_EXCL_START

TEST(map, T0ConstructorDef) {
  s21::Map<int, char> my_map;
  std::map<int, char> orig_map;
  EXPECT_EQ(my_map.empty(), orig_map.empty());
  my_map.insert(1, 'a');
  EXPECT_EQ(my_map.size(), 1);
}

TEST(map, T1Constructor) {
  s21::Map<int, char> my_map({{1, 'a'}, {2, 'b'}, {3, 'c'}});
  EXPECT_EQ(my_map.size(), 3);
  my_map.insert(4, 'd');
  EXPECT_EQ(my_map.size(), 4);
}

TEST(map, T2Constructor) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> orig_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(my_map.size(), orig_map.size());
  my_map.insert(4, 'd');
  orig_map.insert(std::make_pair(4, 'd'));
  EXPECT_EQ(my_map.size(), orig_map.size());
}

TEST(map, T0BeginEnd) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map.insert(4, 'd');

  EXPECT_EQ(*(my_map.begin()), 'a');
  EXPECT_EQ(*(my_map.end()), 'd');
}

TEST(map, T1BeginEndIncDec) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map.insert(4, 'd');

  EXPECT_EQ(*(++my_map.begin()), 'b');
  EXPECT_EQ(*(--my_map.end()), 'c');

  EXPECT_EQ(*(my_map.begin()++), 'b');
  EXPECT_EQ(*(my_map.end()--), 'c');
  EXPECT_THROW(*(++my_map.end()), std::range_error);
}

TEST(map, T0IteratorCompare) {
  s21::Map<int, char> my_map = {{1, 'a'}};

  EXPECT_EQ(my_map.begin(), my_map.end());
}

TEST(map, T0MaxSize) {
  s21::Map<int, char> my_map = {{1, 'a'}, {1, 'a'}};
  std::map<int, char> or_map = {{1, 'a'}, {1, 'a'}};

  EXPECT_EQ(my_map.max_size(), or_map.max_size());
}

TEST(map, T0CopyConstructor) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> movedMap(std::move(my_map));
  EXPECT_EQ(movedMap.size(), 3);
}

TEST(map, T0MoveConstructor) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> copyMap(my_map);
  EXPECT_EQ(copyMap.size(), 3);
  EXPECT_EQ(my_map.size(), 3);
}

// TEST(map, T0Insert) {
//   s21::Map<int, char> my_map({{5,'a'}, {16, 'b'}, {3, 'c'}, {-3, 'd'}});
//   std::map<int, char> orig_map({{5,'a'}, {16, 'b'}, {3, 'c'}, {-3, 'd'}});
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   my_map.insert(4, 'e');
//   orig_map.insert(std::make_pair(4, 'e'));
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   my_map.insert(-40, 'f');
//   orig_map.insert(std::make_pair(-40, 'f'));
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   my_map.insert(40, 'g');
//   orig_map.insert(std::make_pair(40, 'g'));
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   my_map.insert(16, 'h');
//   orig_map.insert(std::make_pair(16, 'h'));
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   auto my_it = my_map.begin();
//   auto orig_it = orig_map.begin();
//   for (; orig_it != orig_map.end(); ++my_it, ++orig_it) {
//     std::cout << *my_it << ' ' << orig_it->second << "  ";
//     EXPECT_TRUE(*my_it == orig_it->second);
//   }
//   std::cout << '\n';
// }

// TEST(map, T1Insert) {
//   s21::Map<int, char> my_map({{5,'a'}, {16, 'b'}, {3, 'c'}, {-3, 'd'}});
//   std::map<int, char> orig_map({{5,'a'}, {16, 'b'}, {3, 'c'}, {-3, 'd'}});
//   EXPECT_EQ(my_map.size(), orig_map.size());
//   my_map.insert(5, 'e');
//   orig_map.insert(std::make_pair(5, 'e'));
//   EXPECT_EQ(*(my_map.find(5)), orig_map.find(5)->second);
// }

// TEST(map, T0MoveOperator) {
//   s21::Map<int, char> my_map = {{1,'a'}, {2, 'b'}, {3, 'c'}};
//   s21::Map<int, char> r_map = {{1,'a'}, {2, 'b'}, {3, 'c'}};
//   s21::Map<int, char> movedMap = {{1,'a'}};
//   movedMap = std::move(my_map);
//   EXPECT_EQ(movedMap.size(), 3);
//   EXPECT_EQ(*(my_map.begin()), 'b');
//   EXPECT_EQ(*(my_map.end()), 'c');
// }

// TEST(map, T0CopyOperator) {
//   s21::Map<int, char> my_map = {{1,'a'}, {2, 'b'}, {3, 'c'}};
//   s21::Map<int, char> r_map = {{1,'a'}, {2, 'b'}, {3, 'c'}};
//   s21::Map<int, char> copy_map = {{15,'a'}};
//   copy_map = my_map;
//   EXPECT_EQ(copy_map.size(), 3);
//   EXPECT_EQ(copy_map.size(), 3);
//   EXPECT_EQ(*(copy_map.begin()), *(copy_map.begin()));
//   EXPECT_EQ(*(my_map.end()), *(copy_map.end()));
// }

TEST(map, T0Merge) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> forMerge = {{5, 'e'}, {6, 'f'}, {7, 'g'}, {1, 'a'}};
  my_map.merge(forMerge);
  EXPECT_EQ(my_map.size(), 6);
  EXPECT_EQ(*(my_map.find(2)), 'b');
  EXPECT_EQ(*(my_map.find(7)), 'g');
}

TEST(map, T1Merge) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map.merge(my_map);
  EXPECT_EQ(my_map.size(), 3);
}

TEST(map, T0MergeContains) {
  s21::Map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::Map<int, int> my_map_merge = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_merge = {{3, 3}, {4, 4}};

  my_map.merge(my_map_merge);
  orig_map.merge(orig_map_merge);

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != ++my_map.end(); ++my_it, ++orig_it) {
    // EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE(*my_it == orig_it->second);
  }

  my_map.print();
  EXPECT_TRUE(my_map.contains(4));
  EXPECT_FALSE(my_map.contains(44));
}

TEST(map, T0Swap) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> for_swap = {{5, 'e'}, {6, 'f'}, {7, 'g'}, {1, 'a'}};
  s21::Map<int, char> swap_map_check = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> my_map_check = {{5, 'e'}, {6, 'f'}, {7, 'g'}, {1, 'a'}};
  for_swap.swap(my_map);
  {
    auto my_it = my_map.begin();
    auto orig_it = my_map_check.begin();
    for (; my_it != ++my_map.end(); ++my_it, ++orig_it) {
      EXPECT_TRUE(*my_it == *orig_it);
    }
  }
  my_map.print();
  for_swap.print();
  {
    auto my_it = for_swap.begin();
    auto orig_it = swap_map_check.begin();
    for (; my_it != ++for_swap.end(); ++my_it, ++orig_it) {
      std::cout << *my_it << ' ' << *orig_it << "  ";
      EXPECT_TRUE(*my_it == *orig_it);
    }
    std::cout << '\n';
  }
}

TEST(map, T0Erase) {
  s21::Map<int, char> my_map({{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'h'}});
  my_map.erase(my_map.find(3));
  EXPECT_FALSE(my_map.contains(3));
}

TEST(map, T1Erase) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'h'}};
  s21::Map<int, char> my_map_check = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'h'}};
  my_map.erase(my_map.find(-3));
  auto my_it = my_map.begin();
  auto orig_it = my_map_check.begin();
  for (; my_it != ++my_map.end(); ++my_it, ++orig_it)
    EXPECT_TRUE(*my_it == *orig_it);
}

TEST(map, T2Erase) {
  s21::Map<int, char> my_map = {{39, 'a'}, {22, 'b'}, {-3, 'c'}, {5, 'h'}};
  s21::Map<int, char> my_map_check = {{39, 'a'}, {22, 'b'}, {-3, 'c'}};
  my_map.erase(my_map.find(5));
  {
    auto my_it = my_map.begin();
    auto orig_it = my_map_check.begin();
    for (; my_it != ++my_map.end(); ++my_it, ++orig_it) {
      EXPECT_TRUE(*my_it == *orig_it);
    }
  }
}

TEST(map, T3Erase) {
  s21::Map<int, char> my_map = {{3, 'a'}};
  my_map.erase(my_map.find(3));
  EXPECT_TRUE(my_map.empty());
}

TEST(map, T4Erase) {
  s21::Map<int, char> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {-1, 'h'}};
  // s21::Map<int, char> my_map_check = { {2, 'b'}, {3, 'c'}, {-1, 'h'}};
  my_map.erase(my_map.find(1));
  EXPECT_FALSE(my_map.contains(1));
  // my_map.print();
  // my_map_check.print();
  // auto my_it = my_map.begin();
  // auto orig_it = my_map_check.begin();
  // for (; my_it != nullptr; ++my_it, ++orig_it) {
  //   std::cout << *my_it << ' ' << *orig_it << "  ";
  //   EXPECT_TRUE(*my_it == *orig_it);
  // }
  // std::cout << '\n';
}

TEST(map, T5Erase) {
  s21::Map<int, char> my_map = {{1, 'a'}, {-1, 'b'}, {2, 'c'}, {4, 'h'}};
  s21::Map<int, char> my_map_check = {{-1, 'b'}, {2, 'c'}, {4, 'h'}};
  my_map.erase(my_map.find(1));
  auto my_it = my_map.begin();
  auto orig_it = my_map_check.begin();
  for (; my_it != ++my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*my_it == *orig_it);
  }
}

TEST(map, T0InsertOrAssign) {
  s21::Map<int, char> my_map({{1, 'a'}, {2, 'b'}, {3, 'c'}, {5, 'h'}});
  s21::Map<int, char> my_map_check(
      {{1, 'u'}, {2, 'b'}, {3, 'c'}, {5, 'h'}, {10, 'l'}});
  my_map.insert_or_assign(1, 'u');
  EXPECT_EQ(*(my_map.find(1)), 'u');
  my_map.insert_or_assign(10, 'l');
  auto my_it = my_map.begin();
  auto orig_it = my_map_check.begin();
  for (; my_it != ++my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*my_it == *orig_it);
  }
}

/*
int main() {
        s21::Map<int, char> my_map({{1,'a'}, {2, 'b'}, {3, 'c'}}); // здесь на
то, что инициализирована размером 3 s21::Map<int, char> my_map1 = {{1,'a'}, {2,
'b'}, {3, 'c'}}; // здесь на то, что инициализирована размером 3. Так же как и
выше, просто одно - initializer list через конструктор второе через оператор
        my_map.print();
        my_map1.print();
        my_map.insert(4, 'd'); // здесь, что вставилась 4
        my_map.print();
  std::cout << "SetInt.begin(): " << *(my_map.begin()) << std::endl; // здесь
проверку на то, что разыменование выводит значение a(ну или просто значение
минимального ключа) std::cout << "SetInt.end(): " <<  *(my_map.end()) <<
std::endl; // здесь проверку на то, что разыменование выводит значение d (ну или
просто значение максимального ключа) std::cout << "SetInt.begin() ++: " <<
*(++my_map.begin()) << std::endl; // здесь проверку на то, что разыменование
выводит значение b (ну или просто значение последующего минимальному ключа) не
добавляй сравнение с оригиналом, потому что там какая то хитрая инкрементация,
глянул у других - уних как и у меня std::cout << "SetInt.end() --: " <<
*(--my_map.end()) << std::endl; // здесь проверку на то, что разыменование
выводит значение c (ну или просто значение предшествуующего максимального ключа)
не добавляй сравнение с оригиналом, потому что там какая то хитрая
инкрементация, глянул у других - уних как и у меня s21::Map<int, char>
movedMap(my_map1); std::cout << "moved map" << std::endl; movedMap.print();
        s21::Map<int, char> copiedMap(my_map); // здесь проверку на size() = 3
        std::cout << "copiedMap" << std::endl;
        copiedMap.print();

  s21::Map<int, char> movedMapOperator = my_map1;
        std::cout << "movedMapOperator" << std::endl; // здесь просто проверку
на size() = 3 такой же тест и на swap movedMapOperator.print(); s21::Map<int,
char> copiedMapOperator(my_map); // здесь просто проверку на size() = 4 или на
то, что у нее есть какое либо значение по ключу std::cout << "copiedMapOperator"
<< std::endl; copiedMapOperator.print();

        s21::Map<int, char> forMerge = {{5,'e'}, {6, 'f'}, {7, 'g'}, {1, 'a'}};
        copiedMapOperator.merge(forMerge);

        std::cout << "copiedMapOperator after merge" << std::endl; // здесь
просто проверку на size() = 7 или на то, что у нее есть какое либо значение по
ключу copiedMapOperator.print(); std::cout << "contains: " << std::boolalpha <<
copiedMapOperator.contains(5) << std::endl; std::cout << "contains: " <<
std::boolalpha << copiedMapOperator.contains(51) << std::endl;

        s21::Map<int, char> forSwap = {{5,'e'}, {6, 'f'}, {7, 'g'}, {1, 'a'}};
        forSwap.swap(my_map);
        std::cout << "copiedMapOperator after swapped" << std::endl; // здесь на
то, что у нас нет по 5 ключу (при создании инициализации он был 2 строки выше),
но есть значение по другому ключу map, которую свапнули forSwap.print();

  forSwap.erase(forSwap.find(2));
        std::cout << "copiedMapOperator after erase(2)" << std::endl;  // здесь
на то, что у него больше нет значения по ключу 2 forSwap.print();

        forSwap.insert_or_assign(1, 'u'); // тут проверить что реально значение
обновилось forSwap.print(); forSwap.insert_or_assign(10, 'l'); // а тут то, что
вставилось forSwap.print(); return 0;
}

*/

// GCOVR_EXCL_STOP