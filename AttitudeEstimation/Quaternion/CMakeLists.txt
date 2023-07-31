cmake_minimum_required(VERSION 3.14)
project(test_quaternion)

add_executable(testQuat Quaternion.hpp test_quaternion.cpp)
target_link_libraries(testQuat gtest)
