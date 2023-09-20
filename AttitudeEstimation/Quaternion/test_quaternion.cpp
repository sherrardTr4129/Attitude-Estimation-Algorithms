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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}