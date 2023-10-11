#include "Quaternion.hpp"
#include "gtest/gtest.h"
using namespace structures;

TEST(QuaternionClassTesting, TestQuatCreation) {
  // test identity case
  Quaternion<float> identityQuat;
  ASSERT_EQ(identityQuat.getX(), 0);
  ASSERT_EQ(identityQuat.getY(), 0);
  ASSERT_EQ(identityQuat.getZ(), 0);
  ASSERT_EQ(identityQuat.getW(), 1);

  // test non-indentity case.
  Quaternion<float> nonIdentQuat(0.2, 0.4, 0.3, 0.5);
  EXPECT_FLOAT_EQ(nonIdentQuat.getX(), 0.2);
  EXPECT_FLOAT_EQ(nonIdentQuat.getY(), 0.4);
  EXPECT_FLOAT_EQ(nonIdentQuat.getZ(), 0.3);
  EXPECT_FLOAT_EQ(nonIdentQuat.getW(), 0.5);

  // test copy constructor case
  Quaternion<float> testQuat(0.2, 0.4, 0.3, 0.5);
  Quaternion<float> copyQuat(nonIdentQuat);
  EXPECT_FLOAT_EQ(copyQuat.getX(), 0.2);
  EXPECT_FLOAT_EQ(copyQuat.getY(), 0.4);
  EXPECT_FLOAT_EQ(copyQuat.getZ(), 0.3);
  EXPECT_FLOAT_EQ(copyQuat.getW(), 0.5);

  // test copy assignment operator
  Quaternion<float> copy_assigned_quat;
  copy_assigned_quat = testQuat;
  EXPECT_FLOAT_EQ(copy_assigned_quat.getX(), 0.2);
  EXPECT_FLOAT_EQ(copy_assigned_quat.getY(), 0.4);
  EXPECT_FLOAT_EQ(copy_assigned_quat.getZ(), 0.3);
  EXPECT_FLOAT_EQ(copy_assigned_quat.getW(), 0.5);
}

TEST(QuaternionClassTesting, TestQuatMultiplication) {
  // test identity case
  Quaternion<float> identityQuatOne;
  Quaternion<float> identityQuatTwo;

  // multiply two identity quats and make sure we get one back
  Quaternion<float> res_quat = identityQuatOne * identityQuatTwo;
  EXPECT_FLOAT_EQ(res_quat.getX(), 0.0);
  EXPECT_FLOAT_EQ(res_quat.getY(), 0.0);
  EXPECT_FLOAT_EQ(res_quat.getZ(), 0.0);
  EXPECT_FLOAT_EQ(res_quat.getW(), 1.0);

  // test non-identity case
  Quaternion<float> nonIdentityQuatOne(0.5, 0.2, 0.2, 0.6);
  Quaternion<float> nonIdentityQuatTwo(0.6, 0.3, 0.1, 0.3);

  // multiply two non-identity quats and make sure we
  // get correct value back
  Quaternion<float> non_ident_res_quat =
      nonIdentityQuatOne * nonIdentityQuatTwo;
  EXPECT_FLOAT_EQ(non_ident_res_quat.getX(), 0.47);
  EXPECT_FLOAT_EQ(non_ident_res_quat.getY(), 0.31);
  EXPECT_FLOAT_EQ(non_ident_res_quat.getZ(), 0.15);
  EXPECT_FLOAT_EQ(non_ident_res_quat.getW(), -0.2);
}

TEST(QuaternionClassTesting, TestQuatScalarMultiplication) {
  // test non-identity case
  Quaternion<double> nonIdentityQuatOne(0.5, 0.2, 0.2, 0.6);
  Quaternion<double> resQuat = nonIdentityQuatOne * 0.5;

  EXPECT_NEAR(resQuat.getX(), 0.25, 0.0001);
  EXPECT_NEAR(resQuat.getY(), 0.1, 0.0001);
  EXPECT_NEAR(resQuat.getZ(), 0.1, 0.0001);
  EXPECT_NEAR(resQuat.getW(), 0.3, 0.0001);
}

TEST(QuaternionClassTesting, TestQuaternionNorm) {
  // take norm and make sure component values are correct
  Quaternion<double> QuatToNorm(0.94064704, 0.12645116, 0.80194097, 0.62633894);
  Quaternion<double> resQuat = QuatToNorm.norm();

  EXPECT_NEAR(resQuat.getX(), 0.67600473, 0.0001);
  EXPECT_NEAR(resQuat.getY(), 0.0908753, 0.0001);
  EXPECT_NEAR(resQuat.getZ(), 0.57632232, 0.0001);
  EXPECT_NEAR(resQuat.getW(), 0.45012429, 0.0001);

  // test zero magnitude case
  Quaternion<double> zeroQuat(0, 0, 0, 0);
  Quaternion<double> zeroQuatNorm = zeroQuat.norm();

  EXPECT_NEAR(zeroQuatNorm.getX(), 0, 0.0001);
  EXPECT_NEAR(zeroQuatNorm.getY(), 0, 0.0001);
  EXPECT_NEAR(zeroQuatNorm.getZ(), 0, 0.0001);
  EXPECT_NEAR(zeroQuatNorm.getW(), 1, 0.0001);
}

TEST(QuaternionClassTesting, TestQuaternionConj) {
  // take conjugate of quaternion, check component values
  Quaternion<double> QuatToNorm(0.94064704, 0.12645116, 0.80194097, 0.62633894);
  Quaternion<double> resQuat = QuatToNorm.conj();

  EXPECT_NEAR(resQuat.getX(), -0.94064704, 0.0001);
  EXPECT_NEAR(resQuat.getY(), -0.12645116, 0.0001);
  EXPECT_NEAR(resQuat.getZ(), -0.80194097, 0.0001);
  EXPECT_NEAR(resQuat.getW(), 0.62633894, 0.0001);
}

TEST(QuaternionClassTesting, TestQuaternionAccesor) {
  // create quaternion, make sure accessor returns the correct value
  Quaternion<double> testAccessQuat(0.94064704, 0.12645116, 0.80194097, 0.62633894);

  EXPECT_FLOAT_EQ(testAccessQuat.getX(), testAccessQuat[1]);
  EXPECT_FLOAT_EQ(testAccessQuat.getY(), testAccessQuat[2]);
  EXPECT_FLOAT_EQ(testAccessQuat.getZ(), testAccessQuat[3]);
  EXPECT_FLOAT_EQ(testAccessQuat.getW(), testAccessQuat[0]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}