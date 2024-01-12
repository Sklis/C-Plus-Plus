#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include "../Tree/AVLTree.h"
namespace s21 {
template <typename Key, typename Value>
class Map : public AVLTree<Key, Value> {
 private:
  AVLTree<Key, Value> tree;

 public:
  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const Key &;
  using size_type = typename AVLTree<Key, bool>::size_type;
  using iterator = typename AVLTree<Key, bool>::Iterator;

  Map();
  Map(std::initializer_list<value_type> const &items);
  std::pair<typename Map<Key, Value>::iterator, bool> insert(
      const value_type &value);
  Map(const Map &other);
  Map(Map &&other) noexcept;
  Map &operator=(Map &&other) noexcept;
  Map &operator=(const Map &other);
  Map(std::initializer_list<std::pair<const Key, Value>> items);
  ~Map();
  Value at(const Key &key);
  Value &operator[](const Key &key);
  void insert(const Key &key, const Value &value);
  void insert_or_assign(const Key &key, const Value &value);
};
}  // namespace s21
#include "s21_map_impl.tpp"
#endif  // MAP_MAP_H_
