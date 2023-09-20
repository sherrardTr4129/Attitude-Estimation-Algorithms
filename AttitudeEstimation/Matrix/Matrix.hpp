#pragma once
#include <cstddef>

template <typename T, size_t rows, size_t cols> class Matrix {
public:
  /**
   * @brief Matrix class constructor
   * @param initial_value the value to initialize the matrix members to
   */
  Matrix(T initial_value = 0.0) {
    for (size_t cur_row = 0; cur_row < this->getNumRows(); cur_row++) {
      for (size_t cur_col = 0; cur_col < this->getNumCols(); cur_col++) {
        _matrix[cur_row][cur_col] = initial_value;
      }
    }
    _rows = rows;
    _cols = cols;
  }

  /**
   * @brief Matrix class constructor
   * @param new_mat[rows][cols] the 2D array to copy into the new matrix
   */
  Matrix(T new_mat[rows][cols]) {
    for (size_t cur_row = 0; cur_row < this->getNumRows(); cur_row++) {
      for (size_t cur_col = 0; cur_col < this->getNumCols(); cur_col++) {
        _matrix[cur_row][cur_col] = new_mat[cur_row][cur_col];
      }
    }
    _rows = rows;
    _cols = cols;
  }

  /**
   * @brief returns the number of rows for a given matrix.
   * @return the number of rows for the given matrix.
   */
  size_t getNumRows() const { return this->_rows; }

  /**
   * @brief returns the number of columns for a given matrix.
   * @return the number of columns for a given matrix.
   */
  size_t getNumCols() const { return this->_cols; }

  /**
   * @brief method to set a particular value at a given row
   * and column to a particular value.
   * @param row the row to set the value in
   * @param col the column to set the value in
   * @param value the value to set at the (row, col) intersection
   * @return false if an out of bounds operation was detected, true otherwise
   */
  bool setValue(size_t row, size_t col, T value) {
    // exit early if we try to step out of bounds
    if (!(row < this->getNumRows() || col < this->getNumCols())) {
      return false;
    }

    this->_matrix[row][col] = value;
    return true;
  }

  /**
   * @brief method to get a particular value at a given row and column.
   * @param row the row to get the value from
   * @param col the column to get the value from
   * @return the value at (row, col).
   */
  T getValue(size_t row, size_t col) const { return this->_matrix[row][col]; }

  /**
   * @brief the operator overload for addition for a
   * given set of matricies.
   * @param other the addend matrix.
   * @return the resultant matrix after the addition operation.
   */
  Matrix<T, rows, cols> operator+(Matrix const &other) {
    // create empty 2D vector the same size as 'this' matrix.
    T res_vec[rows][cols];

    // add this matrix to other matrix
    for (size_t row = 0; row < this->getNumRows(); row++) {
      for (size_t col = 0; col < this->getNumCols(); col++) {
        res_vec[row][col] = this->_matrix[row][col] + other._matrix[row][col];
      }
    }

    Matrix<T, rows, cols> res_matrix(res_vec);
    return res_matrix;
  }

  /**
   * @brief the operator overload for subtraction for a
   * given set of matricies.
   * @param other the subtrahend matrix.
   * @return the resultant matrix after the subtraction.
   */
  Matrix<T, rows, cols> operator-(Matrix const &other) {
    // create empty 2D vector the same size as 'this' matrix.
    T res_vec[rows][cols];

    // subtract this matrix to other matrix
    for (size_t row = 0; row < this->getNumRows(); row++) {
      for (size_t col = 0; col < this->getNumCols(); col++) {
        res_vec[row][col] = this->_matrix[row][col] - other._matrix[row][col];
      }
    }

    Matrix<T, rows, cols> res_matrix(res_vec);
    return res_matrix;
  }

  /**
   * @brief the overload for the multiplication operator
   * for a given set of matricies.
   * @param other the mutiplicant matrix.
   * @return the resultant matrix.
   */
  template <size_t n>
  Matrix<T, rows, n> operator*(Matrix<T, cols, n> const &other) {
    // create empty matrix of correct size
    Matrix<T, rows, n> res_mat(0.0);

    // perform multiplication
    for (size_t i = 0; i < this->getNumRows(); i++) {
      for (size_t j = 0; j < other.getNumCols(); j++) {
        T sum = 0;
        for (size_t k = 0; k < this->getNumCols(); k++) {
          sum += this->getValue(i, k) * other.getValue(k, j);
        }

        res_mat.setValue(i, j, sum);
      }
    }
    return res_mat;
  }

  /**
   * @brief the overload for the multiplication operator
   * for a given scalar.
   * @param other the scalar to multiply 'this' matrix by.
   * @return the resultant matrix.
   */
  Matrix<T, rows, cols> operator*(T const &other) {
    // create empty matrix of correct size
    Matrix<T, rows, cols> res_mat(0.0);

    // perform multiplication
    for (size_t i = 0; i < this->getNumRows(); i++) {
      for (size_t j = 0; j < this->getNumCols(); j++) {
        T new_val = this->getValue(i, j) * other;
        res_mat.setValue(i, j, new_val);
      }
    }

    return res_mat;
  }

  /**
   * @brief the overload for the equality operator.
   * @param other the other matrix used in the equality test.
   * @return true if equal, false otherwise.
   */
  bool operator==(Matrix const &other) {
    // see if dimensions are equal.
    if (this->getNumRows() == other.getNumRows() &&
        this->getNumCols() == other.getNumCols()) {
      // if they are, see if all internal values are equal
      for (size_t i = 0; i < this->getNumRows(); i++) {
        for (size_t j = 0; j < this->getNumCols(); j++) {

          // exit early if not equal
          if (this->getValue(i, j) != other.getValue(i, j)) {
            return false;
          }
        }
      }
      return true;
    } else {
      return false;
    }
  }

  /**
   * @brief the overload for the inequality operator.
   * @param other the other matrix used in the inequality test.
   * @return true if not equal, false otherwise.
   */
  bool operator!=(Matrix const &other) {
    // see if dimensions are not equal.
    if (this->getNumRows() != other.getNumRows() ||
        this->getNumCols() != other.getNumCols()) {
      return true;
    } else {
      for (size_t i = 0; i < this->getNumRows(); i++) {
        for (size_t j = 0; j < this->getNumCols(); j++) {

          // exit early if not equal
          if (this->getValue(i, j) != other.getValue(i, j)) {
            return true;
          }
        }
      }
      return false;
    }
  }

  /**
   * @brief transposes 'this' given matrix.
   * @return a new copy of 'this' matrix, transposed.
   */
  Matrix<T, cols, rows> transpose() {
    // make new vector with swapped dimensions of 'this' Matrix
    Matrix<T, cols, rows> transpose_mat;

    for (size_t i = 0; i < this->getNumRows(); i++) {
      for (size_t j = 0; j < this->getNumCols(); j++) {
        transpose_mat.setValue(j, i, this->getValue(i, j));
      }
    }

    return transpose_mat;
  }

private:
  T _matrix[rows][cols];
  size_t _rows = rows;
  size_t _cols = cols;
};