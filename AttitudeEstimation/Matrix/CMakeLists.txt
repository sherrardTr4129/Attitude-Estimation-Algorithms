cmake_minimum_required(VERSION 3.14)
project(test_matrix)

add_executable(testMatrix Matrix.hpp test_matrix.cpp)
target_link_libraries(testMatrix gtest)
