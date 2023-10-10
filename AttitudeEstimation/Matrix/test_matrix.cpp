#include "Matrix.hpp"
#include "gtest/gtest.h"

using namespace structures;

TEST(MatrixClassTesting, TestMatrixCreation) {
  // test basic creation
  Matrix<int, 5, 2> int_matrix(0.0);
  ASSERT_EQ(5, int_matrix.getNumRows());
  ASSERT_EQ(2, int_matrix.getNumCols());

  Matrix<double, 1, 2> double_matrix(0.0);
  ASSERT_EQ(1, double_matrix.getNumRows());
  ASSERT_EQ(2, double_matrix.getNumCols());

  // test copy constructor
  Matrix<int, 5, 2> int_matrix_copied(int_matrix);
  ASSERT_EQ(5, int_matrix_copied.getNumRows());
  ASSERT_EQ(2, int_matrix_copied.getNumCols());

  // test copy assignment
  Matrix<int, 5, 2> int_matrix_copied_assigned;
  int_matrix_copied_assigned = int_matrix_copied;
  ASSERT_EQ(5, int_matrix_copied_assigned.getNumRows());
  ASSERT_EQ(2, int_matrix_copied_assigned.getNumCols());
}

TEST(MatrixClassTesting, TestMatrixAccessor) {
  Matrix<int, 2, 2> matrix_one(1);

  // try to set a value out of bounds
  ASSERT_FALSE(matrix_one.setValue(2, 2, 1));

  // try to set a value in bounds
  ASSERT_TRUE(matrix_one.setValue(1, 1, 50));

  // access the changed value
  ASSERT_EQ(50, matrix_one.getValue(1, 1));
}

TEST(MatrixClassTesting, TestMatrixAddition) {
  // create 10x10 matricies of 1 and -1
  Matrix<int, 10, 10> one_matrix(1);
  Matrix<int, 10, 10> neg_one_matrix(-1);

  Matrix<int, 10, 10> addition_res = one_matrix + neg_one_matrix;

  for (size_t i = 0; i < addition_res.getNumRows(); i++) {
    for (size_t j = 0; j < addition_res.getNumCols(); j++) {
      int value = addition_res.getValue(i, j);

      // make sure value is 0
      ASSERT_EQ(0, value);
    }
  }
}

TEST(MatrixClassTesting, TestMatrixSubtraction) {
  // create 10x10 matricies of 1 and -1
  Matrix<int, 10, 10> one_matrix(1);
  Matrix<int, 10, 10> neg_one_matrix(-1);

  Matrix<int, 10, 10> addition_res = one_matrix - neg_one_matrix;

  for (size_t i = 0; i < addition_res.getNumRows(); i++) {
    for (size_t j = 0; j < addition_res.getNumCols(); j++) {
      int value = addition_res.getValue(i, j);

      // make sure value is 2
      ASSERT_EQ(2, value);
    }
  }
}

TEST(MatrixClassTesting, TestScalarAndMatrixMult) {
  // create an identity matrix
  float I_vec[3][3] = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};

  Matrix<float, 3, 3> I_mat(I_vec);

  // create a (3x3) square matrix of 5's
  Matrix<float, 3, 3> square_fives(5);

  // multiply them
  Matrix<float, 3, 3> identity_res = I_mat * square_fives;

  // make sure result is the same after multiplying by
  // identity matrix
  for (size_t i = 0; i < identity_res.getNumRows(); i++) {
    for (size_t j = 0; j < identity_res.getNumCols(); j++) {
      ASSERT_EQ(square_fives.getValue(i, j), identity_res.getValue(i, j));
    }
  }

  // multiply two non-square matricies
  Matrix<float, 3, 1> test_mat_one(5);
  Matrix<float, 1, 3> test_mat_two(10);
  Matrix test_mat_final = test_mat_one * test_mat_two;

  // make sure result is appropriate in dims.
  ASSERT_EQ(3, test_mat_final.getNumRows());
  ASSERT_EQ(3, test_mat_final.getNumCols());

  // multiply 3x3 matrix of 5's by 5 scalar
  Matrix<float, 3, 3> five_squared = square_fives * 5;

  // make sure all values are correct
  for (size_t i = 0; i < identity_res.getNumRows(); i++) {
    for (size_t j = 0; j < identity_res.getNumCols(); j++) {
      ASSERT_EQ(25, five_squared.getValue(i, j));
    }
  }
}

TEST(MatrixClassTesting, TestMatrixEqualityOperators) {
  // make two identical matricies
  Matrix<int, 3, 3> mat_one(5);
  Matrix<int, 3, 3> mat_two(5);

  ASSERT_TRUE(mat_one == mat_two);
  ASSERT_FALSE(mat_one != mat_two);

  // modify one, make sure they are no longer equal
  mat_one.setValue(1, 1, 2);

  ASSERT_FALSE(mat_one == mat_two);
  ASSERT_TRUE(mat_one != mat_two);
}

TEST(MatrixClassTesting, TestMatrixTranspose) {
  float vec_to_transpose[3][1] = {{1}, {1}, {1}};
  Matrix<float, 3, 1> mat_to_transpose(vec_to_transpose);

  // perform transpose
  Matrix<float, 1, 3> transposed_mat = mat_to_transpose.transpose();

  // make sure new dimensions are good
  ASSERT_EQ(1, transposed_mat.getNumRows());
  ASSERT_EQ(3, transposed_mat.getNumCols());

  // more complicated case
  float test_vec[3][3] = {{1, 0, 0}, {1, 0, 0}, {1, 0, 1}};

  float test_vec_T[3][3] = {{1, 1, 1}, {0, 0, 0}, {0, 0, 1}};

  Matrix<float, 3, 3> test_mat(test_vec);
  Matrix<float, 3, 3> test_mat_T(test_vec_T);

  Matrix<float, 3, 3> new_mat_transposed = test_mat.transpose();

  // make sure matrix transposed correctly
  ASSERT_TRUE(new_mat_transposed == test_mat_T);
}

TEST(MatrixClassTesting, TestMatrixNorm) {
  // test row vector
  float row_vec[3][1] = {{1}, {1}, {1}};
  Matrix<float, 3, 1> row_matrix(row_vec);
  float row_vec_norm = row_matrix.norm();
  EXPECT_NEAR(1.732, row_vec_norm, 0.001);

  // test column vector
  float col_vec[1][3] = {{1, 1, 1}};
  Matrix<float, 1, 3> col_matrix(col_vec);
  float col_vec_norm = col_matrix.norm();
  EXPECT_NEAR(1.732, col_vec_norm, 0.001);

  // test square vector. Make sure we get
  // a negative one as response.
  float square_vec[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  Matrix<float, 3, 3> square_matrix(square_vec);
  float square_matrix_norm = square_matrix.norm();
  ASSERT_EQ(-1, square_matrix_norm);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
