#include <iostream>
#include "../src/Matrix.h"
#include "MainTest.h"

int main() {
    DetTest();
    MultTest();
    AddTest();
    EqualTest();
    RCVTest();
    TransposeTest();
    ConstructTest();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}