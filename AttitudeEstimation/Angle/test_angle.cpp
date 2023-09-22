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

TEST(AngleClassTesting, TestAngleTypeConversion) {
  // make degree angle
  Angle<float> deg_angle(150, DEGREES);

  // try to convert to degrees
  deg_angle.toDegrees();

  // make sure nothing changed
  ASSERT_FLOAT_EQ(150, deg_angle.getAngleValue());
  EXPECT_EQ(DEGREES, deg_angle.getAngleType());

  // convert to radians, assert correct value and type
  deg_angle.toRadians();
  EXPECT_NEAR(2.61799, deg_angle.getAngleValue(), 0.001);
  EXPECT_EQ(RADIANS, deg_angle.getAngleType());

  // do the same process with rad->degrees
  Angle<float> rad_angle(M_PI / 2, RADIANS);

  rad_angle.toRadians();
  ASSERT_FLOAT_EQ(M_PI / 2, rad_angle.getAngleValue());
  EXPECT_EQ(RADIANS, rad_angle.getAngleType());

  rad_angle.toDegrees();
  EXPECT_NEAR(90, rad_angle.getAngleValue(), 0.001);
  EXPECT_EQ(DEGREES, rad_angle.getAngleType());
}

TEST(AngleClassTesting, TestAngleNormalization) {
  // make degree angle outside of 0->360 degree bounds
  Angle<float> deg_angle(720, DEGREES);

  // make sure it's normalized correctly
  ASSERT_FLOAT_EQ(0, deg_angle.getAngleValue());

  // make radian angle outside of 0->2*PI bounds
  Angle<float> rad_angle(3 * M_PI, RADIANS);
  ASSERT_FLOAT_EQ(M_PI, rad_angle.getAngleValue());
}

TEST(AngleClassTesting, TestAngleAddSub) {
  // make two angles of the same type
  Angle<float> deg_angle_one(100, DEGREES);
  Angle<float> deg_angle_two(100, DEGREES);

  // perform addition and subtraction
  Angle<float> add_res_angle_one = deg_angle_one + deg_angle_two;
  Angle<float> sub_res_angle_one = deg_angle_one - deg_angle_two;

  // verify results
  ASSERT_FLOAT_EQ(200, add_res_angle_one.getAngleValue());
  ASSERT_FLOAT_EQ(0, sub_res_angle_one.getAngleValue());

  // make two angles for different types
  Angle<float> deg_angle_three(90, DEGREES);
  Angle<float> rad_angle_one(M_PI / 2, RADIANS);

  // perform addition and subtraction
  Angle<float> add_res_angle_two = deg_angle_three + rad_angle_one;
  Angle<float> sub_res_angle_two = deg_angle_three - rad_angle_one;

  // verify results
  ASSERT_FLOAT_EQ(180, add_res_angle_two.getAngleValue());
  ASSERT_FLOAT_EQ(0, sub_res_angle_two.getAngleValue());
  ASSERT_EQ(DEGREES, add_res_angle_two.getAngleType());
  ASSERT_EQ(DEGREES, sub_res_angle_two.getAngleType());

  // make sure original operators are not mutated
  ASSERT_EQ(DEGREES, deg_angle_three.getAngleType());
  ASSERT_EQ(RADIANS, rad_angle_one.getAngleType());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}