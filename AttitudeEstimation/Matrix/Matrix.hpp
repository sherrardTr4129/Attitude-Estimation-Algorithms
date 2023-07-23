#pragma once
#include <vector>

template <typename T> class Matrix {
    public:
      Matrix(size_t num_rows, size_t num_cols, T initial_value);
      Matrix(Matrix<T> const& other);
      Matrix(std::vector<std::vector<T>> new_vec);
      size_t getNumRows();
      size_t getNumCols();
      bool setValue(size_t row, size_t col, T value);
      T operator()(size_t row, size_t col);
      Matrix operator+(Matrix const& other);
      Matrix operator-(Matrix const& other);
      Matrix operator*(Matrix const& other);

    private:
      std::vector<std::vector<T>> _matrix;
};

/**
 * @brief Creates a new matrix object with size (num_rows x num_cols) initialized to 0.
 * @param num_rows the number of rows to create the matrix with.
 * @param num_cols the number of columns to create the matrix with
*/
template <typename T> Matrix<T>::Matrix(size_t num_rows, size_t num_cols, T initial_value) {
    // create empty matrix of (row, col) dimensions
    this->_matrix = std::vector<std::vector<T>>(num_rows, std::vector<T> (num_cols, initial_value));
}

/**
 * @brief creates a new matrix object from an existing matrix object.
 * @param other the other matrix to copy into 'this' matrix.
*/
template <typename T> Matrix<T>::Matrix(Matrix<T> const& other) {
    this->_matrix = other._matrix;
}

/**
 * @brief creates a new matrix object from an existing 2D vector.
 * @param new_vec the 2D vector to copy into 'this' matrix.
*/
template <typename T> Matrix<T>::Matrix(std::vector<std::vector<T>> new_vec) {
    this->_matrix = new_vec;
}

/**
 * @brief returns the number of rows for a given matrix.
 * @return the number of rows for the given matrix.
*/
template <typename T> size_t Matrix<T>::getNumRows() {
    return this->_matrix.size();
}

/**
 * @brief returns the number of columns for a given matrix.
 * @return the number of columns for a given matrix.
*/
template <typename T> size_t Matrix<T>::getNumCols() {
    return this->_matrix[0].size();
}

/**
 * @brief method to set a particular value at a given row 
 * and column to a particular value.
 * @param row the row to set the value in
 * @param col the column to set the value in
 * @param value the value to set at the (row, col) intersection
 * @return false if an out of bounds operation was detected, true otherwise
*/
template <typename T> bool Matrix<T>::setValue(size_t row, size_t col, T value) {
    
    // exit early if we try to step out of bounds
    if(!(row < this->getNumRows() || col < this->getNumCols())) {
        return false;
    }

    this->_matrix[row][col] = value;
    return true;
}

/**
 * @brief the operator overload for the item accessor operator.
*/
template <typename T> T Matrix<T>::operator()(size_t row, size_t col) {
    return this->_matrix[row][col];
}

/**
 * @brief the operator overload for addition for a 
 * given set of matricies. NOTE: this implementation assumes
 * matrices of the same dimensions have been provided. If that is
 * not the case, matrix of size 1x1 will be returned, initialized to -1.
*/
template <typename T> Matrix<T> Matrix<T>::operator+(Matrix<T> const& other) {

    // if dimensions are not the same, return the "error matrix"
    if(this->_matrix.size() != other._matrix.size() || 
        this->_matrix[0].size() != other._matrix[0].size()) {
            return Matrix<T>(1, 1, -1);
    }
    
    // create empty 2D vector the same size as 'this' matrix.
    std::vector<std::vector<T>> res_vec(this->_matrix.size(), 
        std::vector<T> (this->_matrix[0].size(), 0));

    // add this matrix to other matrix
    for(size_t row = 0; row < res_vec.size(); row++) {
        for(size_t col = 0; col < res_vec[0].size(); col++) {
            res_vec[row][col] = this->_matrix[row][col] + other._matrix[row][col];
        }
    }

    Matrix<T> res_matrix(res_vec);
    return res_matrix;
}