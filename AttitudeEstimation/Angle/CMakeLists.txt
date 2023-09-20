cmake_minimum_required(VERSION 3.14)
project(test_angle)

add_executable(testAngle Angle.hpp test_angle.cpp)
target_link_libraries(testAngle gtest)
