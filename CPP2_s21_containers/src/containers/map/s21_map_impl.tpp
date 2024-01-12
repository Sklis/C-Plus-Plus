#include <initializer_list>

namespace s21 {

template <typename Key, typename Value>
Map<Key, Value>::Map(Map &&other) noexcept
    : AVLTree<Key, Value>(std::move(other)){};

template <typename Key, typename Value>
Map<Key, Value>::Map(const Map &other) : AVLTree<Key, Value>(other){};

template <typename Key, typename Value>
Map<Key, Value>::~Map() = default;

template <typename Key, typename Value>
Map<Key, Value>::Map() : AVLTree<Key, Value>() {}
template <typename Key, typename Value>
Map<Key, Value>::Map(std::initializer_list<std::pair<const Key, Value>> items) {
  for (const auto &item : items) {
    insert(item.first, item.second);
  }
}

template <typename Key, typename Value>
Map<Key, Value>::Map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}
template <typename Key, typename Value>
void Map<Key, Value>::insert(const Key &key, const Value &value) {
  if (!AVLTree<Key, Value>::contains(key))
    AVLTree<Key, Value>::insert(key, value);
}

template <typename Key, typename Value>
void Map<Key, Value>::insert_or_assign(const Key &key, const Value &value) {
  auto forSwapit = AVLTree<Key, Value>::find(key);
  if (forSwapit != nullptr)
    forSwapit.getCurrent()->value = value;
  else
    AVLTree<Key, Value>::insert(key, value);
}

template <typename Key, typename Value>
Value Map<Key, Value>::at(const Key &key) {
  auto forSwapit = AVLTree<Key, Value>::find(key);
  return forSwapit.getCurrent()->value;
}

template <typename Key, typename Value>
Value &Map<Key, Value>::operator[](const Key &key) {
  auto it = AVLTree<Key, Value>::find(key);
  if (it == nullptr) insert(key, Value());
  return it.getCurrent()->value;
}
}  // namespace s21