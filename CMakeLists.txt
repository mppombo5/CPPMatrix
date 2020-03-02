cmake_minimum_required(VERSION 3.3.0)
project(CPPMatrix)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SRCFILES include/CPPMatrix.h src/Matrix.cpp)
set (TESTFILES test/DetTest.cpp test/OperatorTest.cpp test/RCVectorsTest.cpp test/MainTest.cpp
        test/MainTest.h test/TransposeTest.cpp test/ConstructorTest.cpp)

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