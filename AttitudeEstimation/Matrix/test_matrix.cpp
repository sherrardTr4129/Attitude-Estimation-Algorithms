#include "gtest/gtest.h"
#include "Matrix.hpp"

TEST(MatrixClassTesting, TestMatrixCreation) {
  Matrix<int> int_matrix(5, 2, 0);
  ASSERT_EQ(5, int_matrix.getNumRows());
  ASSERT_EQ(2, int_matrix.getNumCols());

  Matrix<double> double_matrix(1, 2, 0);
  ASSERT_EQ(1, double_matrix.getNumRows());
  ASSERT_EQ(2, double_matrix.getNumCols());
}

TEST(MatrixClassTesting, TestMatrixAccessor) {
  Matrix<int> matrix_one(2, 2, 1);

  // try to set a value out of bounds
  ASSERT_FALSE(matrix_one.setValue(2, 2, 1));

  // try to set a value in bounds
  ASSERT_TRUE(matrix_one.setValue(1, 1, 50));

  // access the changed value
  ASSERT_EQ(50, matrix_one.getValue(1,1));
}

TEST(MatrixClassTesting, TestMatrixAddition) {
  // create 10x10 matricies of 1 and -1
  Matrix<int> one_matrix(10, 10, 1);
  Matrix<int> neg_one_matrix(10, 10, -1);

  Matrix<int> addition_res = one_matrix + neg_one_matrix;

  for(size_t i = 0; i < addition_res.getNumRows(); i++) {
    for(size_t j = 0; j < addition_res.getNumCols(); j++) {
      int value = addition_res.getValue(i, j);
      
      // make sure value is 0
      ASSERT_EQ(0, value);
    }
  }

  // try to add two matricies with non-equal dims.
  Matrix<int> test_mat_one(10, 10, 1);
  Matrix<int> test_mat_two(10, 11, 1);
  Matrix<int> res_mat = test_mat_one + test_mat_two;

  // make sure we get the 'error matrix' back
  ASSERT_TRUE(res_mat.isErrorMatrix());
}

TEST(MatrixClassTesting, TestMatrixSubtraction) {
  // create 10x10 matricies of 1 and -1
  Matrix<int> one_matrix(10, 10, 1);
  Matrix<int> neg_one_matrix(10, 10, -1);

  Matrix<int> addition_res = one_matrix - neg_one_matrix;

  for(size_t i = 0; i < addition_res.getNumRows(); i++) {
    for(size_t j = 0; j < addition_res.getNumCols(); j++) {
      int value = addition_res.getValue(i, j);
      
      // make sure value is 2
      ASSERT_EQ(2, value);
    }
  }

  // try to subtract two matricies with non-equal dims.
  Matrix<int> test_mat_one(10, 10, 1);
  Matrix<int> test_mat_two(10, 11, 1);
  Matrix<int> res_mat = test_mat_one - test_mat_two;

  // make sure we get the 'error matrix' back
  ASSERT_TRUE(res_mat.isErrorMatrix());
}

TEST(MatrixClassTesting, TestScalarAndMatrixMult) {
  // create an identity matrix
  std::vector<std::vector<int>> I_vec {{1, 0, 0},
                                     {0, 1, 0},
                                     {0, 0, 1}};
  
  Matrix<int> I_mat(I_vec);

  // create a (3x3) square matrix of 5's
  Matrix<int> square_fives(3, 3, 5);

  // multiply them
  Matrix<int> identity_res = I_mat * square_fives;

  // make sure result is the same after multiplying by
  // identity matrix
  for(size_t i = 0; i < identity_res.getNumRows(); i++) {
    for(size_t j = 0; j < identity_res.getNumCols(); j++) {
      ASSERT_EQ(square_fives.getValue(i, j), identity_res.getValue(i, j));
    }
  }

  // multiply 3x3 matrix of 5's by 5 scalar
  Matrix<int> five_squared = square_fives * 5;

  // make sure all values are correct
  for(size_t i = 0; i < identity_res.getNumRows(); i++) {
    for(size_t j = 0; j < identity_res.getNumCols(); j++) {
      ASSERT_EQ(25, five_squared.getValue(i, j));
    }
  }

  // make sure we get an error matrix when trying to 
  // multiply invalid sized matricies
  Matrix<int> mat_one(3, 2, 5);
  Matrix<int> mat_two(3, 3, 5);
  Matrix<int> res_matrix = mat_one * mat_two;

  ASSERT_TRUE(res_matrix.isErrorMatrix());
}

TEST(MatrixClassTesting, TestMatrixEqualityOperators) {
  // make two identical matricies
  Matrix<int> mat_one(3, 3, 5);
  Matrix<int> mat_two(3, 3, 5);

  ASSERT_TRUE(mat_one == mat_two);
  ASSERT_FALSE(mat_one != mat_two);

  // modify one, make sure they are no longer equal
  mat_one.setValue(1, 1, 2);

  ASSERT_FALSE(mat_one == mat_two);
  ASSERT_TRUE(mat_one != mat_two);
}

TEST(MatrixClassTesting, TestMatrixTranspose) {
  std::vector<std::vector<int>> vec_to_transpose {{1},
                                                  {1}, 
                                                  {1}};
  Matrix<int> mat_to_transpose(vec_to_transpose);

  // perform transpose
  mat_to_transpose.transpose();

  // make sure new dimensions are good
  ASSERT_EQ(1, mat_to_transpose.getNumRows());
  ASSERT_EQ(3, mat_to_transpose.getNumCols());

  // more complicated case
  std::vector<std::vector<int>> test_vec {{1, 0, 0},
                                       {1, 0, 0},
                                       {1, 0, 1}};
  
  std::vector<std::vector<int>> test_vec_T {{1, 1, 1},
                                         {0, 0, 0},
                                         {0, 0, 1}};
  
  Matrix<int> test_mat(test_vec);
  Matrix<int> test_mat_T(test_vec_T);

  test_mat.transpose();

  // make sure matrix transposed correctly
  ASSERT_TRUE(test_mat == test_mat_T);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
