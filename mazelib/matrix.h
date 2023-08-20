#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <cassert>
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace mcg {

template<typename Tp>
class Matrix {
 public:
  using value_type = Tp;
  using reference = Tp&;
  using const_reference = const Tp&;
  using pointer = Tp*;
  using const_pointer = const Tp*;
  using size_type = typename std::vector<Tp>::size_type;

  using iterator = typename std::vector<Tp>::iterator;
  using const_iterator = typename std::vector<Tp>::const_iterator;

  Matrix() = default;

  Matrix(std::initializer_list<std::initializer_list<Tp>> const& list)
  : rows_(list.size()), cols_(list.begin()->size()) {
    for (auto& i : list) {
      assert(i.size() == cols_);
      for (auto& j : i) {
        data_.push_back(j);
      }
    }
  }

  Matrix(size_type rows, size_type cols)
    : rows_(rows), cols_(cols), data_(rows * cols) {}

  Matrix(const Matrix& other)
      : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

  Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    other.rows_ = other.cols_ = 0;
  }

  virtual ~Matrix() = default;

  Matrix& operator=(const Matrix& other) {
    if (this != &other) {
      Matrix tmp(other);
      swap(tmp);
    }
    return *this;
  }

  Matrix& operator=(Matrix&& other) noexcept {
    Matrix tmp(std::move(other));
    if (this != &other) {
      swap(tmp);
    }
    return *this;
  }

  pointer operator[](size_type row) noexcept {
    return &data_[row * cols_];
  }

  const_pointer operator[](size_type row) const noexcept {
    return &data_[row * cols_];
  }

  bool operator==(const Matrix& other) const noexcept {
    return IsEqual(other);
  }

  bool operator!=(const Matrix& other) const noexcept {
    return !IsEqual(other);
  }

  void Swap(Matrix& other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
  }

  iterator begin() noexcept {
    return data_.begin();
  }

  const_iterator begin() const noexcept {
    return data_.begin();
  }

  iterator end() noexcept {
    return data_.end();
  }

  const_iterator end() const noexcept {
    return data_.end();
  }

  void Clear() noexcept {
    data_.clear();
    cols_ = rows_ = 0;
  }

  reference At(size_type row, size_type col) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("operator[]. Row or col is out of range");
    }
    return data_[row * cols_ + col];
  }

  const_reference At(size_type row, size_type col) const {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("operator[]. Row or col is out of range");
    }
    return data_[row * cols_ + col];
  }

  size_type GetRows() const noexcept {
    return rows_;
  }

  size_type GetCols() const noexcept {
    return cols_;
  }

  void SetCols(size_type cols) {
    Matrix tmp(rows_, cols);
    size_type cols_to_copy = std::min(cols_, cols);
    for (size_type i = 0; i < rows_; ++i) {
      memcpy(&tmp.data_[i * cols], &data_[i * cols_], cols_to_copy * sizeof(Tp));
    }
    Swap(tmp);
  }

  void SetRows(size_type rows) {
    data_.resize(rows * cols_);
    rows_ = rows;
  }

  bool IsEqual(const Matrix& other) const noexcept {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      return false;
    }
    for (size_type i = 0; i < data_.size(); ++i) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  size_type rows_{}, cols_{};
  std::vector<Tp> data_;
};

template<typename Tp>
std::ostream& operator<<(std::ostream& os, Matrix<Tp>& mat) noexcept {
  for(size_t i = 0; i < mat.GetRows(); ++i) {
    for (size_t j = 0; j < mat.GetCols(); ++j) {
      os << mat[i][j];
      if (j != mat.GetCols() - 1) {
        os << ' ';
      }
    }
    if (i != mat.GetRows() - 1) {
      os << '\n';
    }
  }
  return os;
}

} // namespace mcg


#endif // MATRIX_H_
