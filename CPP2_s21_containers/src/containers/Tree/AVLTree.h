#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

namespace s21 {
template <typename Key, typename Value>
class AVLTree {
 private:
  struct AVLNode {
    Key key;
    Value value;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;
    AVLNode(const Key& k, const Value& v, AVLNode* p)
        : key(k),
          value(v),
          left(nullptr),
          right(nullptr),
          parent(p),
          height(1) {}
  };
  AVLNode* copyTree(AVLNode* node);
  AVLNode* insert(AVLNode* node, const Key& key, const Value& value,
                  AVLNode* parent);
  AVLNode* remove(AVLNode* node, const Key& key);
  int height(AVLNode* node);
  int balanceFactor(AVLNode* node);
  void updateHeight(AVLNode* node);
  AVLNode* rotateRight(AVLNode* y);
  AVLNode* rotateLeft(AVLNode* x);
  AVLNode* balance(AVLNode* node);
  AVLNode* find(AVLNode* node, const Key& key);
  AVLNode* findMin(AVLNode* node) const;
  AVLNode* findMax(AVLNode* node) const;
  void clear(AVLNode* node);
  AVLNode* findSuccessor(AVLNode* node) const;
  AVLNode* findPredecessor(AVLNode* node) const;
  size_t getSize(AVLNode* node) const;
  void mergeRecursive(AVLNode* node);

 public:
  AVLNode* root;
  class Iterator;
  using size_type = size_t;
  using iterator = Iterator;
  using reference = Value&;

  class Iterator {
   private:
    AVLNode* current;
    const AVLTree<Key, Value>* tree;

   public:
    Iterator(AVLNode* node) : current(node) {}
    Iterator(AVLNode* node, const AVLTree<Key, Value>* t)
        : current(node), tree(t) {}
    const Value& operator*();
    bool operator==(const iterator& it) const;
    bool operator!=(const iterator& it) const;
    Iterator& operator++();
    Iterator& operator++(int);
    Iterator& operator--();
    Iterator& operator--(int);
    AVLNode* getCurrent() const;
    friend class AVLTree<Key, Value>;
  };

  AVLTree() : root(nullptr) {}
  AVLTree(const AVLTree& other);
  AVLTree(AVLTree&& other) noexcept;
  AVLTree& operator=(const AVLTree& other);
  AVLTree& operator=(AVLTree&& other) noexcept;
  ~AVLTree();
  // methods
  void insert(const Key& key, const Value& value = Value());
  void remove(const Key& key);
  void swap(AVLTree& other);
  void merge(AVLTree& other);
  void clear();
  void erase(iterator pos);
  // size
  size_type size() const;
  size_type max_size();
  bool empty();
  // find & contains
  iterator find(const Key& key);
  bool contains(const Key& key);
  // iterators
  iterator begin() const;
  iterator end() const;
  // debug
  void printLevelOrder() const;
  void printInOrder(AVLNode* node);
  void print();
};

}  // namespace s21

#include "AVLTree_impl.tpp"
#endif  // AVL_TREE_H_
