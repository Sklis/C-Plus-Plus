namespace s21 {
template <typename T, size_t N>
s21::Array<T, N>::Array() : size_(N) {
  for (size_t i = 0; i < size_; ++i) {
    elems_[i] = T();
  }
}

template <typename T, size_t N>
s21::Array<T, N>::Array(const std::initializer_list<value_type> &items)
    : Array() {
  std::copy(items.begin(), items.end(), elems_);
}

template <typename T, size_t N>
s21::Array<T, N>::Array(const Array<T, N> &a) {
  std::copy(a.elems_, a.elems_ + N, elems_);
}

template <typename T, size_t N>
s21::Array<T, N>::Array(Array<T, N> &&a) noexcept {
  std::move(a.elems_, a.elems_ + N, elems_);
}

template <typename T, size_t N>
s21::Array<T, N>::~Array() = default;

template <typename T, size_t N>
typename Array<T, N>::Array &s21::Array<T, N>::operator=(const Array<T, N> &a) {
  std::copy(a.elems_, a.elems_ + N, elems_);
  return *this;
}

template <typename T, size_t N>
typename Array<T, N>::Array &s21::Array<T, N>::operator=(
    Array<T, N> &&a) noexcept {
  for (size_t i = 0; i < N; ++i) elems_[i] = std::move(a.elems_[i]);
  return *this;
}

template <typename T, size_t N>
typename Array<T, N>::iterator s21::Array<T, N>::begin() {
  return elems_;
}

template <typename T, size_t N>
typename Array<T, N>::iterator s21::Array<T, N>::end() {
  return elems_ + size_;
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator s21::Array<T, N>::begin() const {
  return elems_;
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator s21::Array<T, N>::end() const {
  return elems_ + size_;
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator s21::Array<T, N>::cbegin() const {
  return elems_;
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator s21::Array<T, N>::cend() const {
  return elems_ + size_;
}

template <typename T, size_t N>
typename Array<T, N>::reference s21::Array<T, N>::at(size_type pos) {
  return (*this)[pos];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference s21::Array<T, N>::at(
    size_type pos) const {
  return (*this)[pos];
}

template <typename T, size_t N>
typename Array<T, N>::reference s21::Array<T, N>::front() {
  return elems_[0];
}

template <typename T, size_t N>
typename Array<T, N>::reference s21::Array<T, N>::back() {
  return elems_[N - 1];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference s21::Array<T, N>::front() const {
  return elems_[0];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference s21::Array<T, N>::back() const {
  return elems_[N - 1];
}

template <typename T, size_t N>
bool s21::Array<T, N>::empty() {
  return size_ == 0;
}

template <typename T, size_t N>
typename Array<T, N>::size_type s21::Array<T, N>::size() const {
  return size_;
}

template <typename T, size_t N>
typename Array<T, N>::size_type s21::Array<T, N>::max_size() {
  return size();
}

template <typename T, size_t N>
void s21::Array<T, N>::swap(Array<T, N> &a) {
  std::swap_ranges(elems_, elems_ + N, a.elems_);
}

template <typename T, size_t N>
void s21::Array<T, N>::fill(const_reference value) {
  std::fill(elems_, elems_ + N, value);
}

template <typename T, size_t N>
typename Array<T, N>::reference s21::Array<T, N>::operator[](size_type pos) {
  if (pos >= N) throw std::out_of_range("Index out of bounds");
  return elems_[pos];
}

template <typename T, size_t N>
typename Array<T, N>::const_reference s21::Array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) throw std::out_of_range("Index out of bounds");
  return elems_[pos];
}

template <typename T, size_t N>
void s21::Array<T, N>::print() {
  for (auto it = begin(); it != end(); ++it) std::cout << *it << " ";
  std::cout << std::endl;
}

template <typename T, size_t N>
typename Array<T, N>::iterator s21::Array<T, N>::data() {
  return elems_;
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator s21::Array<T, N>::data() const {
  return elems_;
}
}  // namespace s21