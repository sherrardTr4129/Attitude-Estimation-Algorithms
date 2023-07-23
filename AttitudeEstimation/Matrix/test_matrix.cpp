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
  ASSERT_EQ(50, matrix_one(1,1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
