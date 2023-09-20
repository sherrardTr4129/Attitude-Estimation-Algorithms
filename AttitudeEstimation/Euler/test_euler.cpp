#include "Euler.hpp"
#include "gtest/gtest.h"
using namespace structures;

TEST(EulerClassTesting, TestEulerCreation) {
  // test default constructor
  Euler<float> default_euler;
  EXPECT_FLOAT_EQ(0, default_euler.getX());
  EXPECT_FLOAT_EQ(0, default_euler.getY());
  EXPECT_FLOAT_EQ(0, default_euler.getZ());

  // test parameterized constructor
  Euler<float> param_euler(10, 15, 20);
  EXPECT_FLOAT_EQ(10, param_euler.getX());
  EXPECT_FLOAT_EQ(15, param_euler.getY());
  EXPECT_FLOAT_EQ(20, param_euler.getZ());

  // test copy constructor
  Euler<float> copied_euler(param_euler);
  EXPECT_FLOAT_EQ(10, copied_euler.getX());
  EXPECT_FLOAT_EQ(15, copied_euler.getY());
  EXPECT_FLOAT_EQ(20, copied_euler.getZ());

  // test copy assignment operator overload
  Euler<float> copied_assigned_euler;
  copied_assigned_euler = copied_euler;
  EXPECT_FLOAT_EQ(10, copied_assigned_euler.getX());
  EXPECT_FLOAT_EQ(15, copied_assigned_euler.getY());
  EXPECT_FLOAT_EQ(20, copied_assigned_euler.getZ());
}

TEST(EulerClassTesting, TestEulerSetGet) {
  // create zeroed out Euler
  Euler<float> new_euler;
  EXPECT_FLOAT_EQ(0, new_euler.getX());
  EXPECT_FLOAT_EQ(0, new_euler.getY());
  EXPECT_FLOAT_EQ(0, new_euler.getZ());

  // set values
  new_euler.setX(15);
  new_euler.setY(20);
  new_euler.setZ(25);

  // get values back and assert they are changed as expected
  EXPECT_FLOAT_EQ(15, new_euler.getX());
  EXPECT_FLOAT_EQ(20, new_euler.getY());
  EXPECT_FLOAT_EQ(25, new_euler.getZ());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}