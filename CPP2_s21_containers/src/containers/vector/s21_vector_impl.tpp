#include <limits>
namespace s21 {
template <typename T>
void Vector<T>::allocate() {
  data_ = new T[capacity_];
}

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(size_t initialSize)
    : size_(initialSize), capacity_(initialSize) {
  allocate();
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = T();
  }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    reserve(newCapacity);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity) {
  if (newCapacity > max_size())
    throw std::out_of_range("ReserveError: Too large size for a new capacity");

  if (newCapacity > capacity_) {
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data_;
}

template <typename T>
void Vector<T>::print() const {
  for (size_t i = 0; i < size_; ++i) {
    std::cout << data_[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v) : size_(v.size_), capacity_(v.size_) {
  allocate();
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> const& items)
    : size_(items.size()), capacity_(items.size()) {
  allocate();
  size_t i = 0;
  for (const T& item : items) {
    data_[i++] = item;
  }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v) noexcept
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
  if (this != &v) {
    this->swap(v);
    delete[] v.data_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.data_ = nullptr;
  }

  return *this;
}

template <typename T>
bool Vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t Vector<T>::size() const {
  return size_;
}

template <typename T>
size_t Vector<T>::max_size() const {
  return std::numeric_limits<size_t>::max();
}

template <typename T>
size_t Vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void Vector<T>::pop_back() {
  if (size_ > 0) --size_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T* newData = new T[size_];
    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = size_;
  }
}

template <typename T>
void Vector<T>::clear() noexcept {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const {
  return const_iterator(data_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const {
  return const_iterator(data_ + size_);
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  // return at(pos);
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  // return at(pos);
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  size_type idx = pos - begin();

  if (idx > size_) {
    throw std::out_of_range(
        "InsertError: The insertion position is out of range of the vector "
        "memory");
  }

  if (size_ == capacity_) {
    reserve(capacity_ ? capacity_ * 2 : 1);
  }

  iterator new_pos = begin() + idx;

  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++size_;

  return new_pos;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(const_iterator pos) {
  size_type position = pos - data_;

  if (position > size_) {
    throw std::out_of_range("EraseError: Index out of range");
  }

  iterator start(data_ + position);

  for (iterator it = start; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --size_;
  return start;
}

template <typename T>
void Vector<T>::erase(const_iterator first, const_iterator last) {
  size_t startIndex = first - begin();
  size_t endIndex = last - begin();

  if (startIndex >= size_ || endIndex > size_ || startIndex >= endIndex) {
    throw std::out_of_range("EraseError: Index out of range");
  }

  size_t elementsToRemove = endIndex - startIndex;

  for (size_t i = startIndex; i < size_ - elementsToRemove; ++i) {
    data_[i] = data_[i + elementsToRemove];
  }

  size_ -= elementsToRemove;
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  Vector<T> tmp{args...};
  iterator cur_pos = begin() + (pos - cbegin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    cur_pos = insert(cur_pos, tmp[i]);
    ++cur_pos;
  }

  return cur_pos;
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args) {
  insert_many(cend(), args...);
}

template <typename T>
bool s21::Vector<T>::operator==(const s21::Vector<T>& other) const noexcept {
  if (size_ != other.size()) return false;
  auto my_it = cbegin();
  auto other_it = other.cbegin();
  bool res = true;
  while (my_it != cend() && res) {
    if (*my_it != *other_it) res = false;
    ++my_it;
    ++other_it;
  }
  return res;
}

template <typename T>
bool s21::Vector<T>::operator!=(const s21::Vector<T>& other) const noexcept {
  return !(*this == other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  if (this != &v) {
    Vector tmp(v);
    *this = std::move(tmp);
  }
  return *this;
}

template <typename T>
T* Vector<T>::data() {
  return data_;
}

template <typename T>
const T* Vector<T>::data() const {
  return data_;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return const_iterator(data_);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return const_iterator(data_ + size_);
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::operator++() {
  ++data_;
  return *this;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::operator--() {
  --data_;
  return *this;
}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::operator++() const {
  ++data_;
  return *this;
}

template <typename T>
typename Vector<T>::const_iterator& Vector<T>::operator--() const {
  --data_;
  return *this;
}
template <typename T>
bool Vector<T>::operator==(const iterator& other) const {
  return data_ == other.data_;
}

template <typename T>
bool Vector<T>::operator!=(const iterator& other) const {
  return data_ != other.data_;
}
}  // namespace s21
