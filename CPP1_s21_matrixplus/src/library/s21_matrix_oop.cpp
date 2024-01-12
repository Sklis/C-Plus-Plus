#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  memoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  new (this) S21Matrix(other.rows_, other.cols_);
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != 0) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != 0) delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

double S21Matrix::calcDeterminant() {
  double det = 0;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0, sign = 1; i < rows_; i++, sign *= -1) {
      minor.calcMinor(i, 0, *this);
      det += sign * matrix_[i][0] * minor.calcDeterminant();
    }
  }

  return det;
}

void S21Matrix::calcMinor(int row, int column, S21Matrix &other) {
  for (int i = 0, minor_i = 0; i < other.rows_; i++) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < other.cols_; j++) {
      if (j == column) continue;
      matrix_[minor_i][minor_j] = other.matrix_[i][j];
      minor_j++;
    }
    minor_i++;
  }
}

void S21Matrix::memoryAllocation() {
  this->validateMatrixSize();

  if (matrix_ != 0) {
    matrix_ = new double *[rows_] {};
    for (int i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]{};
        if (matrix_[i] == 0) this->~S21Matrix();
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  this->validateMatrixSize();
  other.validateMatrixSize();

  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  this->validateMatrixSize(other);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  this->validateMatrixSize(other);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  this->validateMatrixSize();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  this->validateMatrixSize();
  other.validateMatrixSize();
  if (cols_ != other.rows_) {
    throw std::range_error("The matrices have unsuitable dimensions");
  }

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  this->validateMatrixSize();

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  this->validateMatrixSize();
  this->validateSquareMatrix();

  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        minor.calcMinor(i, j, *this);
        result.matrix_[i][j] = minor.Determinant() * pow(-1, i + j);
      }
    }
  }

  return result;
}

double S21Matrix::Determinant() {
  this->validateMatrixSize();
  this->validateSquareMatrix();
  double det;

  if (rows_ == 1) {
    det = matrix_[0][0];
  } else {
    det = calcDeterminant();
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  this->validateMatrixSize();
  this->validateSquareMatrix();
  S21Matrix result(rows_, cols_);

  if (double det = Determinant() && fabs(det) > 1e-6) {
    if (rows_ == 1) {
      result.matrix_[0][0] = 1 / det;
    } else {
      result = CalcComplements();
      result = result.Transpose();
      result.MulNumber(1.0 / det);
    }
  } else {
    throw std::range_error("The determinant is 0");
  }

  return result;
}

int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows >= 1 && rows_ != rows) {
    S21Matrix result(rows, cols_);
    result.copyMatrix(*this);
    *this = result;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols >= 1 && cols_ != cols) {
    S21Matrix result(rows_, cols);
    result.copyMatrix(*this);
    *this = result;
  }
}

void S21Matrix::validateMatrixSize() const {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Matrix size is invalid");
  }
}

void S21Matrix::validateMatrixSize(const S21Matrix &other) const {
  this->validateMatrixSize();
  other.validateMatrixSize();
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Matrices of unequal sizes");
  }
}

void S21Matrix::validateSquareMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square");
  }
}

void S21Matrix::copyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_ && i < other.rows_; i++) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::fillMatrix(double *values) {
  for (int i = 0, iv = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++, iv++) {
      matrix_[i][j] = values[iv];
    }
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;

  this->~S21Matrix();
  new (this) S21Matrix(other.rows_, other.cols_);
  copyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);

  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index is out of range");
  }

  return matrix_[row][col];
}
