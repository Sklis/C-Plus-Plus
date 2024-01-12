namespace s21 {

template <typename T>
Stack<T>::Node::Node(const T& value) : data(value), next(nullptr) {}

template <typename T>
Stack<T>::Stack() : top_(nullptr) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> const& items) : top_(nullptr) {
  for (const T& item : items) {
    push(item);
  }
}

template <typename T>
Stack<T>::Stack(const Stack& other) : top_(nullptr) {
  if (this != &other) {
    clear();
    Node* otherCurrent = other.top_;
    s21::Stack<T> tempStack;
    while (otherCurrent != nullptr) {
      tempStack.push(otherCurrent->data);
      otherCurrent = otherCurrent->next;
    }
    while (!tempStack.empty()) {
      push(tempStack.top());
      tempStack.pop();
    }
  }
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : top_(other.top_) {
  other.top_ = nullptr;
}

template <typename T>
Stack<T>::~Stack() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  if (this != &other) {
    clear();
    Node* otherCurrent = other.top_;
    s21::Stack<T> tempStack;
    while (otherCurrent != nullptr) {
      tempStack.push(otherCurrent->data);
      otherCurrent = otherCurrent->next;
    }
    while (!tempStack.empty()) {
      push(tempStack.top());
      tempStack.pop();
    }
  }
  return *this;
}

template <typename T>
void Stack<T>::clear() {
  while (!empty()) pop();
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
  if (this != &other) {
    clear();
    top_ = other.top_;
    other.top_ = nullptr;
  }
  return *this;
}

template <typename T>
void Stack<T>::push(const T& value) {
  Node* newNode = new Node(value);
  newNode->next = top_;
  top_ = newNode;
}

template <typename T>
void Stack<T>::pop() {
  if (!empty()) {
    Node* temp = top_;
    top_ = top_->next;
    delete temp;
  }
}

template <typename T>
const T& Stack<T>::top() const {
  if (!empty()) {
    return top_->data;
  } else {
    throw std::out_of_range("Stack is empty");
  }
}

template <typename T>
bool Stack<T>::empty() const {
  return top_ == nullptr;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
  typename Stack<T>::size_type count = 0;
  Node* current = top_;
  while (current != nullptr) {
    ++count;
    current = current->next;
  }
  return count;
}

template <typename T>
template <typename... Args>
void Stack<T>::insert_many_front(Args&&... args) {
  Stack<T> tempStack;
  (tempStack.push(std::forward<Args>(args)), ...);

  Stack<T> tempStack2;
  while (!tempStack.empty()) {
    tempStack2.push(tempStack.top());
    tempStack.pop();
  }

  while (!tempStack2.empty()) {
    push(tempStack2.top());
    tempStack2.pop();
  }
}

template <typename T>
void Stack<T>::swap(Stack& other) noexcept {
  std::swap(top_, other.top_);
}

template <typename T>
void Stack<T>::print() const {
  Node* current = top_;
  while (current != nullptr) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

}  // namespace s21