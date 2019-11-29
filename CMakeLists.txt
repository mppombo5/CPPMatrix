cmake_minimum_required(VERSION 3.15)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainTest src/Matrix.cpp src/Matrix.h tests/MainTest.cpp)
add_executable(MultiplyTest src/Matrix.cpp src/Matrix.h tests/MultTest.cpp)
add_executable(RCVectorsTest src/Matrix.cpp src/Matrix.h tests/RCVectorsTest.cpp)
add_executable(DetTest src/Matrix.cpp src/Matrix.h tests/DetTest.cpp)
