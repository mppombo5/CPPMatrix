cmake_minimum_required(VERSION 3.15)
project(CPPMatrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainTest src/Matrix.cpp src/Matrix.h
        tests/DetTest.cpp tests/OperatorTest.cpp tests/RCVectorsTest.cpp tests/MainTest.cpp tests/MainTest.h tests/TransposeTest.cpp tests/ConstructorTest.cpp)

add_library(CPPMTXstatic STATIC src/Matrix.cpp src/Matrix.h)
add_library(CPPMTXshared SHARED src/Matrix.cpp src/Matrix.h)