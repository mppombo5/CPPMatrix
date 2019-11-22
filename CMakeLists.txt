cmake_minimum_required(VERSION 3.15)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainTest tests/test.cpp Matrix.cpp Matrix.h)
add_executable(MultiplyTest Matrix.cpp Matrix.h tests/MultTest.cpp)
add_executable(RCVectorsTest Matrix.cpp Matrix.h tests/RCVectors.cpp)