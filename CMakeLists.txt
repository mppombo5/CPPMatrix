cmake_minimum_required(VERSION 3.15)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainTest src/Matrix.cpp src/Matrix.h
        tests/DetTest.cpp tests/MultTest.cpp tests/RCVectorsTest.cpp tests/MainTest.cpp tests/MainTest.h)