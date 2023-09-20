cmake_minimum_required(VERSION 3.14)
project(test_euler)

add_executable(testEuler Euler.hpp test_euler.cpp)
target_link_libraries(testEuler gtest)
