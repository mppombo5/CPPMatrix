cmake_minimum_required(VERSION 3.3.0)
project(CPPMatrix)

set(CMAKE_CXX_STANDARD 14)

set(SRCFILES src/Matrix.cpp src/Matrix.h)
set (TESTFILES tests/DetTest.cpp tests/OperatorTest.cpp tests/RCVectorsTest.cpp tests/MainTest.cpp
        tests/MainTest.h tests/TransposeTest.cpp tests/ConstructorTest.cpp)

add_executable(test ${SRCFILES} ${TESTFILES})
set_target_properties(test
        PROPERTIES
        OUTPUT_NAME "MainTest"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

add_library(static STATIC ${SRCFILES})
add_library(shared SHARED ${SRCFILES})
set_target_properties(static shared
        PROPERTIES
        OUTPUT_NAME "CPPMat"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")