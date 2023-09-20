#include "Angle.hpp"
#include "gtest/gtest.h"
using namespace structures;

TEST(AngleClassTesting, TestAngleCreation) {
  // create a few angle objects
  Angle<float> deg_angle(50, DEGREES);
  Angle<float> rad_angle(3.14159, RADIANS);

  // make sure they were created correctly
  ASSERT_FLOAT_EQ(50, deg_angle.getAngleValue());
  ASSERT_FLOAT_EQ(3.14159, rad_angle.getAngleValue());
  ASSERT_EQ(DEGREES, deg_angle.getAngleType());
  ASSERT_EQ(RADIANS, rad_angle.getAngleType());

  // test copy constructor
  Angle<float> deg_angle_copy(deg_angle);
  Angle<float> rad_angle_copy(rad_angle);
  ASSERT_FLOAT_EQ(50, deg_angle_copy.getAngleValue());
  ASSERT_FLOAT_EQ(3.14159, rad_angle_copy.getAngleValue());
  ASSERT_EQ(DEGREES, deg_angle_copy.getAngleType());
  ASSERT_EQ(RADIANS, rad_angle_copy.getAngleType());

  // test copy assignment operator
  Angle<float> deg_angle_copy_assign;
  Angle<float> rad_angle_copy_assign;
  deg_angle_copy_assign = deg_angle;
  rad_angle_copy_assign = rad_angle;
  ASSERT_FLOAT_EQ(50, deg_angle_copy_assign.getAngleValue());
  ASSERT_FLOAT_EQ(3.14159, rad_angle_copy_assign.getAngleValue());
  ASSERT_EQ(DEGREES, deg_angle_copy_assign.getAngleType());
  ASSERT_EQ(RADIANS, rad_angle_copy_assign.getAngleType());
}

TEST(AngleClassTesting, TestAngleNormalization) {
  // TODO: Implement me
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}