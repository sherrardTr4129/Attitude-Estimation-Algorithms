#include "../Quaternion/Quaternion.hpp"
#include "Euler.hpp"
#include "gtest/gtest.h"
using namespace structures;

TEST(EulerClassTesting, TestEulerCreation) {
  // test default constructor
  Euler<float> default_euler;
  EXPECT_FLOAT_EQ(0, default_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(0, default_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(0, default_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, default_euler.getAngleType());

  // test parameterized constructor
  Euler<float> param_euler(10, 15, 20, DEGREES);
  EXPECT_FLOAT_EQ(10, param_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(15, param_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(20, param_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, param_euler.getAngleType());

  // test copy constructor
  Euler<float> copied_euler(param_euler);
  EXPECT_FLOAT_EQ(10, copied_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(15, copied_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(20, copied_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, copied_euler.getAngleType());

  // test copy assignment operator overload
  Euler<float> copied_assigned_euler;
  copied_assigned_euler = copied_euler;
  EXPECT_FLOAT_EQ(10, copied_assigned_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(15, copied_assigned_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(20, copied_assigned_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, copied_assigned_euler.getAngleType());
}

TEST(EulerClassTesting, TestEulerSetGet) {
  // create zeroed out Euler
  Euler<float> new_euler;
  EXPECT_FLOAT_EQ(0, new_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(0, new_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(0, new_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, new_euler.getAngleType());

  // set values
  new_euler.setX(Angle<float>(15, new_euler.getAngleType()));
  new_euler.setY(Angle<float>(20, new_euler.getAngleType()));
  new_euler.setZ(Angle<float>(25, new_euler.getAngleType()));

  // get values back and assert they are changed as expected
  EXPECT_FLOAT_EQ(15, new_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(20, new_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(25, new_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, new_euler.getAngleType());
}

TEST(EulerClassTesting, TestEulerAngleTypeConv) {
  // create a test euler angle
  Euler<float> new_euler(90, 270, 90, DEGREES);

  // convert to radians
  new_euler.toRadians();

  // make sure all conversions worked
  EXPECT_EQ(RADIANS, new_euler.getAngleType());
  EXPECT_FLOAT_EQ(M_PI / 2, new_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ((M_PI * 3) / 2, new_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI / 2, new_euler.getZ().getAngleValue());
  EXPECT_EQ(RADIANS, new_euler.getX().getAngleType());
  EXPECT_EQ(RADIANS, new_euler.getY().getAngleType());
  EXPECT_EQ(RADIANS, new_euler.getZ().getAngleType());

  // do the same thing in reverse
  new_euler.toDegrees();

  // verify we get our original values back
  EXPECT_EQ(DEGREES, new_euler.getAngleType());
  EXPECT_FLOAT_EQ(90, new_euler.getX().getAngleValue());
  EXPECT_FLOAT_EQ(270, new_euler.getY().getAngleValue());
  EXPECT_FLOAT_EQ(90, new_euler.getZ().getAngleValue());
  EXPECT_EQ(DEGREES, new_euler.getX().getAngleType());
  EXPECT_EQ(DEGREES, new_euler.getY().getAngleType());
  EXPECT_EQ(DEGREES, new_euler.getZ().getAngleType());
}

TEST(EulerClassTesting, TestEulerToQuat) {
  // create a few test euler angles
  Euler<float> new_euler_one(45, 45, 45, DEGREES);
  Euler<float> new_euler_two(M_PI / 2, M_PI / 2, M_PI / 2, RADIANS);

  // generate quaternion and verify we get expected values
  Quaternion<float> new_quat_one = new_euler_one.toQuaternion();
  Quaternion<float> new_quat_two = new_euler_two.toQuaternion();

  // make sure original Eulers were not mutated
  EXPECT_EQ(DEGREES, new_euler_one.getAngleType());
  EXPECT_EQ(RADIANS, new_euler_two.getAngleType());
  EXPECT_FLOAT_EQ(45, new_euler_one.getX().getAngleValue());
  EXPECT_FLOAT_EQ(45, new_euler_one.getY().getAngleValue());
  EXPECT_FLOAT_EQ(45, new_euler_one.getZ().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI / 2, new_euler_two.getX().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI / 2, new_euler_two.getY().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI / 2, new_euler_two.getZ().getAngleValue());

  // make sure quaternion values are correct
  EXPECT_NEAR(0.8446, new_quat_one.getW(), 0.0001);
  EXPECT_NEAR(0.1913, new_quat_one.getX(), 0.0001);
  EXPECT_NEAR(0.4619, new_quat_one.getY(), 0.0001);
  EXPECT_NEAR(0.1913, new_quat_one.getZ(), 0.0001);
  EXPECT_NEAR(0.7071, new_quat_two.getW(), 0.0001);
  EXPECT_NEAR(0.0, new_quat_two.getX(), 0.0001);
  EXPECT_NEAR(0.7071, new_quat_two.getY(), 0.0001);
  EXPECT_NEAR(0.0, new_quat_two.getZ(), 0.0001);
}

TEST(EulerClassTesting, TestEulerAddSub) {
  // create a few test euler angles of same type
  Euler<float> new_euler_one(45, 45, 45, DEGREES);
  Euler<float> new_euler_two(45, 45, 45, DEGREES);

  // perform addition and subtraction
  Euler<float> add_res_one = new_euler_one + new_euler_two;
  Euler<float> sub_res_one = new_euler_one - new_euler_two;

  // make sure values are correct
  EXPECT_EQ(DEGREES, add_res_one.getAngleType());
  EXPECT_EQ(DEGREES, sub_res_one.getAngleType());
  EXPECT_FLOAT_EQ(90, add_res_one.getX().getAngleValue());
  EXPECT_FLOAT_EQ(90, add_res_one.getY().getAngleValue());
  EXPECT_FLOAT_EQ(90, add_res_one.getZ().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_one.getX().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_one.getY().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_one.getZ().getAngleValue());

  // create a few test euler angles of different types
  Euler<float> new_euler_three(90, 90, 90, DEGREES);
  Euler<float> new_euler_four(M_PI / 2, M_PI / 2, M_PI / 2, RADIANS);

  // perform addition and subtraction
  Euler<float> add_res_two = new_euler_three + new_euler_four;
  Euler<float> sub_res_two = new_euler_three - new_euler_four;

  // make sure values are correct
  EXPECT_EQ(DEGREES, add_res_two.getAngleType());
  EXPECT_EQ(DEGREES, sub_res_two.getAngleType());
  EXPECT_FLOAT_EQ(180, add_res_two.getX().getAngleValue());
  EXPECT_FLOAT_EQ(180, add_res_two.getY().getAngleValue());
  EXPECT_FLOAT_EQ(180, add_res_two.getZ().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_two.getX().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_two.getY().getAngleValue());
  EXPECT_FLOAT_EQ(0, sub_res_two.getZ().getAngleValue());

  // make sure radian euler was not mutated
  EXPECT_EQ(RADIANS, new_euler_four.getAngleType());
}

TEST(EulerClassTesting, TestEulerScalarMult) {
  // create a few test euler angles different types
  Euler<float> deg_euler(90, 90, 90, DEGREES);
  Euler<float> rad_euler(M_PI / 2, M_PI / 2, M_PI / 2, RADIANS);

  // do scalar multiplication
  Euler<float> deg_euler_prod_1 = deg_euler * 0.5;
  Euler<float> deg_euler_prod_2 = deg_euler * 2.0;
  Euler<float> rad_euler_prod = rad_euler * 2.0;

  // check values
  EXPECT_FLOAT_EQ(45, deg_euler_prod_1.getX().getAngleValue());
  EXPECT_FLOAT_EQ(45, deg_euler_prod_1.getY().getAngleValue());
  EXPECT_FLOAT_EQ(45, deg_euler_prod_1.getZ().getAngleValue());
  EXPECT_FLOAT_EQ(180, deg_euler_prod_2.getX().getAngleValue());
  EXPECT_FLOAT_EQ(180, deg_euler_prod_2.getY().getAngleValue());
  EXPECT_FLOAT_EQ(180, deg_euler_prod_2.getZ().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI, rad_euler_prod.getX().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI, rad_euler_prod.getY().getAngleValue());
  EXPECT_FLOAT_EQ(M_PI, rad_euler_prod.getZ().getAngleValue());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}