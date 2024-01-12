namespace s21 {

template <typename T>
Queue<T>::Node::Node(const T& value) : data(value), next(nullptr) {}

template <typename T>
Queue<T>::Queue() : front_(nullptr), rear_(nullptr) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> const& items)
    : front_(nullptr), rear_(nullptr) {
  for (const auto& item : items) {
    push(item);
  }
}

template <typename T>
Queue<T>::Queue(const Queue& other) {
  front_ = nullptr;
  rear_ = nullptr;

  Node* currentNode = other.front_;
  while (currentNode != nullptr) {
    Node* newNode = new Node(currentNode->data);
    if (empty()) {
      front_ = newNode;
      rear_ = newNode;
    } else {
      rear_->next = newNode;
      rear_ = newNode;
    }
    currentNode = currentNode->next;
  }
}

template <typename T>
Queue<T>::Queue(Queue&& other) {
  front_ = other.front_;
  rear_ = other.rear_;
  other.front_ = nullptr;
  other.rear_ = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
  clear();
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  if (this != &other) {
    clear();
    Node* otherCurrent = other.front_;
    while (otherCurrent != nullptr) {
      push(otherCurrent->data);
      otherCurrent = otherCurrent->next;
    }
  }
  return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
  if (this != &other) {
    clear();
    front_ = other.front_;
    rear_ = other.rear_;
    other.front_ = nullptr;
    other.rear_ = nullptr;
  }

  return *this;
}

template <typename T>
void Queue<T>::clear() {
  while (!empty()) {
    pop();
  }
}

template <typename T>
void Queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  Node* temp = front_;
  front_ = front_->next;
  delete temp;
  if (front_ == nullptr) rear_ = nullptr;
}

template <typename T>
void Queue<T>::push(const T& value) {
  Node* newNode = new Node(value);
  if (empty()) {
    front_ = newNode;
    rear_ = newNode;
  } else {
    rear_->next = newNode;
    rear_ = newNode;
  }
}

template <typename T>
bool Queue<T>::empty() const {
  return front_ == nullptr;
}

template <typename T>
typename Queue<T>::size_type Queue<T>::size() const {
  typename Queue<T>::size_type count = 0;
  Node* current = front_;
  while (current != nullptr) {
    ++count;
    current = current->next;
  }
  return count;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (front_ == nullptr) throw std::out_of_range("Queue is empty");
  return front_->data;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (rear_ == nullptr) throw std::out_of_range("Queue is empty");
  return rear_->data;
}

template <typename T>
template <class... Args>
void Queue<T>::insert_many_back(Args&&... args) {
  (push(std::forward<Args>(args)), ...);
}

template <typename T>
void Queue<T>::swap(Queue& other) noexcept {
  std::swap(front_, other.front_);
  std::swap(rear_, other.rear_);
}

template <typename T>
void Queue<T>::print() const {
  Node* current = front_;
  while (current != nullptr) {
    std::cout << current->data << " ";
    current = current->next;
  }
  std::cout << std::endl;
}
}  // namespace s21