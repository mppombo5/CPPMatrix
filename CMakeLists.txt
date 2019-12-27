cmake_minimum_required(VERSION 3.15)
project(CPPMatrix)

set(CMAKE_CXX_STANDARD 17)

set(SRCFILES src/Matrix.cpp src/Matrix.h)
set (TESTFILES tests/DetTest.cpp tests/OperatorTest.cpp tests/RCVectorsTest.cpp tests/MainTest.cpp
        tests/MainTest.h tests/TransposeTest.cpp tests/ConstructorTest.cpp)

add_executable(test ${SRCFILES} ${TESTFILES})
set_target_properties(test PROPERTIES OUTPUT_NAME "MainTest")

add_library(static STATIC ${SRCFILES})
set_target_properties(static PROPERTIES OUTPUT_NAME "CPPMat")

add_library(shared SHARED ${SRCFILES})
set_target_properties(shared PROPERTIES OUTPUT_NAME "CPPMat")