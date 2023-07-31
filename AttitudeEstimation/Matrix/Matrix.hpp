#pragma once
#include <vector>

template <typename T> class Matrix {
    public:
      Matrix(size_t num_rows, size_t num_cols, T initial_value);
      Matrix(Matrix<T> const& other);
      Matrix(std::vector<std::vector<T>> new_vec);
      size_t getNumRows() const;
      size_t getNumCols() const;
      bool setValue(size_t row, size_t col, T value);
      T getValue(size_t row, size_t col) const;
      bool isErrorMatrix();
      Matrix operator+(Matrix const& other);
      Matrix operator-(Matrix const& other);
      Matrix operator*(Matrix const& other);
      Matrix operator*(T const& other);
      bool operator==(Matrix const& other);
      bool operator!=(Matrix const& other);
      void transpose();

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
template <typename T> size_t Matrix<T>::getNumRows() const{
    return this->_matrix.size();
}

/**
 * @brief returns the number of columns for a given matrix.
 * @return the number of columns for a given matrix.
*/
template <typename T> size_t Matrix<T>::getNumCols() const{
    return this->_matrix[0].size();
}

/**
 * @brief determines if 'this' matrix is an error matrix or not
 * i.e. matrix of dimensions (1,1) with a value of -1 at index (0,0).
 * @return true if an error matrix, false otherwise.
*/
template <typename T> bool Matrix<T>::isErrorMatrix() {
    if(this->getNumRows() == 1 && this->getNumCols() == 1) {
        if(this->getValue(0,0) == -1) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
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
 * @brief method to get a particular value at a given row and column.
 * @param row the row to get the value from
 * @param col the column to get the value from
 * @return the value at (row, col).
*/
template <typename T> T Matrix<T>::getValue(size_t row, size_t col) const {
    return this->_matrix[row][col];
}

/**
 * @brief the operator overload for addition for a 
 * given set of matricies. NOTE: this implementation assumes
 * matrices of the same dimensions have been provided. If that is
 * not the case, matrix of size 1x1 will be returned, initialized to -1.
 * @param other the addend matrix.
 * @return the resultant matrix after the addition operation.
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

/**
 * @brief the operator overload for subtraction for a 
 * given set of matricies. NOTE: this implementation assumes
 * matrices of the same dimensions have been provided. If that is
 * not the case, matrix of size 1x1 will be returned, initialized to -1.
 * @param other the subtrahend matrix.
 * @return the resultant matrix after the subtraction.
*/
template <typename T> Matrix<T> Matrix<T>::operator-(Matrix<T> const& other) {

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
            res_vec[row][col] = this->_matrix[row][col] - other._matrix[row][col];
        }
    }

    Matrix<T> res_matrix(res_vec);
    return res_matrix;
}

/**
 * @brief the overload for the multiplication operator 
 * for a given set of matricies. NOTE: if matrix dimensions are not
 * suitable for multiplication, the error matrix will be returned.
 * @param other the mutiplicant matrix.
 * @return the resultant matrix.
*/
template <typename T> Matrix<T> Matrix<T>::operator*(Matrix<T> const& other) {
    // make sure number of columns of first matrix has the same number
    // of rows as the second matrix. If not, return the 'error matrix'.
    if(this->getNumCols() != other.getNumRows()) {
        return Matrix<T>(1, 1, -1);
    }

    // create empty matrix of correct size
    Matrix<T> res_mat(this->getNumRows(), other.getNumCols(), 0);

    // perform multiplication
    for(size_t i = 0; i < this->getNumRows(); i++) {
        for(size_t j = 0; j < other.getNumCols(); j++) {
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
template <typename T> Matrix<T> Matrix<T>::operator*(T const& other) {
    // create empty matrix of correct size
    Matrix<T> res_mat(this->getNumRows(), this->getNumCols(), 0);

    // perform multiplication
    for(size_t i = 0; i < this->getNumRows(); i++) {
        for(size_t j = 0; j < this->getNumCols(); j++) {
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
template <typename T> bool Matrix<T>::operator==(Matrix<T> const& other) {
    // see if dimensions are equal.
    if(this->getNumRows() == other.getNumRows() && this->getNumCols() == other.getNumCols()) {
        // if they are, see if all internal values are equal
        for(size_t i = 0; i < this->getNumRows(); i++) {
            for(size_t j = 0; j < this->getNumCols(); j++) {

                // exit early if not equal
                if(this->getValue(i, j) != other.getValue(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief the overload for the inequality operator.
 * @param other the other matrix used in the inequality test.
 * @return true if not equal, false otherwise.
*/
template <typename T> bool Matrix<T>::operator!=(Matrix<T> const& other) {
    // see if dimensions are not equal.
    if(this->getNumRows() != other.getNumRows() || this->getNumCols() != other.getNumCols()) {
        return true;
    }
    else {
        for(size_t i = 0; i < this->getNumRows(); i++) {
            for(size_t j = 0; j < this->getNumCols(); j++) {

                // exit early if not equal
                if(this->getValue(i, j) != other.getValue(i, j)) {
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
template <typename T> void Matrix<T>::transpose() {
    // make new vector with swapped dimensions of 'this' Matrix
    std::vector<std::vector<T>> transpose_vec(this->getNumCols(), std::vector<T> (this->getNumRows(), 0));

    for(size_t i = 0; i < this->getNumRows(); i++) {
        for(size_t j = 0; j < this->getNumCols(); j++) {
            transpose_vec[j][i] = this->getValue(i, j);
        }
    }

    this->_matrix = transpose_vec;
}
