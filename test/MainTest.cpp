#include <iostream>
#include "../include/CPPMatrix.h"
#include "MainTest.h"

int main() {
    DetTest();
    MultTest();
    AddTest();
    EqualTest();
    ParenTest();
    RCVTest();
    TransposeTest();
    ConstructTest();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}