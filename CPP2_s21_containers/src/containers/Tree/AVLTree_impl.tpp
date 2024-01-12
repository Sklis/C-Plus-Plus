namespace s21 {
template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(const AVLTree& other) {
  root = copyTree(other.root);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::copyTree(
    AVLNode* node) {
  if (node == nullptr) {
    return nullptr;
  }
  AVLNode* newNode = new AVLNode(node->key, node->value, nullptr);
  newNode->left = copyTree(node->left);
  if (newNode->left != nullptr) {
    newNode->left->parent = newNode;
  }
  newNode->right = copyTree(node->right);
  if (newNode->right != nullptr) {
    newNode->right->parent = newNode;
  }
  newNode->height = node->height;
  return newNode;
}

template <typename Key, typename Value>
AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(const AVLTree& other) {
  if (this != &other) {
    clear();
    root = copyTree(other.root);
  }
  return *this;
}

template <typename Key, typename Value>
AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(AVLTree&& other) noexcept {
  if (this != &other) {
    clear();
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename Key, typename Value>
AVLTree<Key, Value>::AVLTree(AVLTree&& other) noexcept {
  root = other.root;
  other.root = nullptr;
}

template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
  clear(root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear(AVLNode* node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
  root = insert(root, key, value, nullptr);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::insert(
    AVLNode* node, const Key& key, const Value& value, AVLNode* parent) {
  if (node == nullptr) {
    return new AVLNode(key, value, parent);
  }
  if (key < node->key) {
    node->left = insert(node->left, key, value, node);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value, node);
  } else {
    node->value = value;
    return node;
  }
  updateHeight(node);
  return balance(node);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key) {
  root = remove(root, key);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::erase(iterator pos) {
  if (pos.current == nullptr) {
    return;
  }
  root = remove(root, pos.current->key);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::remove(
    AVLNode* node, const Key& key) {
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      AVLNode* temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        delete node;
        return temp;
      } else {
        *node = *temp;
        delete temp;
        updateHeight(node);
        return balance(node);
      }
    } else {
      AVLNode* temp = findMin(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = remove(node->right, temp->key);
    }
  }
  updateHeight(node);
  return balance(node);
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::height(AVLNode* node) {
  if (node == nullptr) return 0;
  return node->height;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::balance(
    AVLNode* node) {
  if (node == nullptr) {
    return nullptr;
  }

  updateHeight(node);

  int balance = balanceFactor(node);

  if (balance > 1 && balanceFactor(node->left) >= 0) {
    return rotateRight(node);
  }

  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  if (balance < -1 && balanceFactor(node->right) <= 0) {
    return rotateLeft(node);
  }

  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::rotateLeft(
    AVLNode* x) {
  AVLNode* y = x->right;
  x->right = y->left;
  if (y->left != nullptr) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == nullptr)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;

  updateHeight(x);
  updateHeight(y);

  return y;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::rotateRight(
    AVLNode* y) {
  AVLNode* x = y->left;
  y->left = x->right;
  if (x->right != nullptr) x->right->parent = y;
  x->parent = y->parent;
  if (y->parent == nullptr)
    root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  x->right = y;
  y->parent = x;

  updateHeight(y);
  updateHeight(x);

  return x;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode* node) {
  if (node != nullptr) {
    node->height =
        std::max((node->left != nullptr) ? node->left->height : 0,
                 (node->right != nullptr) ? node->right->height : 0) +
        1;
  }
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::balanceFactor(AVLNode* node) {
  return (node != nullptr) ? height(node->left) - height(node->right) : 0;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::size_type AVLTree<Key, Value>::size() const {
  return getSize(root);
}

template <typename Key, typename Value>
size_t AVLTree<Key, Value>::getSize(AVLNode* node) const {
  if (node == nullptr) {
    return 0;
  }
  return 1 + getSize(node->left) + getSize(node->right);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::size_type AVLTree<Key, Value>::max_size() {
  return (std::numeric_limits<size_type>::max() /
          sizeof(typename AVLTree<Key, Value>::AVLNode)) /
         2;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::empty() {
  return root == nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::swap(AVLTree& other) {
  std::swap(root, other.root);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::merge(AVLTree& other) {
  if (this == &other) {
    return;
  }
  mergeRecursive(other.root);
  other.clear();
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
  clear(root);
  root = nullptr;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::mergeRecursive(AVLNode* node) {
  if (node != nullptr) {
    insert(node->key, node->value);
    mergeRecursive(node->left);
    mergeRecursive(node->right);
  }
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::iterator AVLTree<Key, Value>::find(
    const Key& key) {
  AVLNode* result = find(root, key);
  return Iterator(result);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::find(
    AVLNode* node, const Key& key) {
  if (node == nullptr || key == node->key) {
    return node;
  }

  if (key < node->key) {
    return find(node->left, key);
  } else {
    return find(node->right, key);
  }
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::contains(const Key& key) {
  return find(root, key) != nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
const Value& AVLTree<Key, Value>::Iterator::operator*() {
  if (current == nullptr) {
    throw std::range_error("Out");
  }
  return current->value;
}

template <typename Key, typename Value>
typename s21::AVLTree<Key, Value>::AVLNode*
AVLTree<Key, Value>::Iterator::getCurrent() const {
  return current;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator==(const Iterator& it) const {
  return current == it.current;
}

template <typename Key, typename Value>
bool AVLTree<Key, Value>::Iterator::operator!=(const Iterator& it) const {
  return current != it.current;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator AVLTree<Key, Value>::begin() const {
  return Iterator(findMin(root), this);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::findMin(
    AVLNode* node) const {
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::iterator AVLTree<Key, Value>::end() const {
  AVLNode* maxNode = findMax(root);
  return Iterator(maxNode);
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::findMax(
    AVLNode* node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator&
AVLTree<Key, Value>::Iterator::operator++() {
  if (current == nullptr) return *this;
  current = tree->findSuccessor(current);
  return *this;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator&
AVLTree<Key, Value>::Iterator::operator--() {
  if (current == nullptr) return *this;
  current = tree->findPredecessor(current);
  return *this;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator&
AVLTree<Key, Value>::Iterator::operator++(int) {
  current = tree->findSuccessor(current);
  return *this;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::Iterator&
AVLTree<Key, Value>::Iterator::operator--(int) {
  current = tree->findPredecessor(current);
  return *this;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::findSuccessor(
    AVLNode* node) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right != nullptr) {
    return findMin(node->right);
  }

  AVLNode* parent = node->parent;
  while (parent != nullptr && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }

  return parent;
}

template <typename Key, typename Value>
typename AVLTree<Key, Value>::AVLNode* AVLTree<Key, Value>::findPredecessor(
    AVLNode* node) const {
  if (node->left != nullptr) {
    return findMax(node->left);
  }
  AVLNode* parent = node->parent;
  while (parent != nullptr && node == parent->left) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
void AVLTree<Key, Value>::printLevelOrder() const {
  if (root == nullptr) {
    std::cout << "Tree is empty." << std::endl;
    return;
  }

  std::queue<AVLNode*> nodeQueue;
  nodeQueue.push(root);
  nodeQueue.push(nullptr);  // Using nullptr as a marker for level change

  while (!nodeQueue.empty()) {
    AVLNode* current = nodeQueue.front();
    nodeQueue.pop();

    if (current == nullptr) {
      std::cout << std::endl;
      if (!nodeQueue.empty()) {
        nodeQueue.push(nullptr);  // Marker for the next level
      }
    } else {
      std::cout << "(" << current->key << ", " << current->value << ") ";

      if (current->left != nullptr) nodeQueue.push(current->left);

      if (current->right != nullptr) nodeQueue.push(current->right);
    }
  }
}
template <typename Key, typename Value>
void AVLTree<Key, Value>::printInOrder(AVLNode* node) {
  if (node != nullptr) {
    printInOrder(node->left);
    std::cout << "(" << node->key << ", " << node->value << ") ";
    printInOrder(node->right);
  }
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::print() {
  printInOrder(root);
  std::cout << std::endl;
}
}  // namespace s21