#include <iostream>
#include "../src/Matrix.h"
#include "MainTest.h"
using namespace std;

int main() {
    DetTest();
    MultTest();
    AddTest();
    EqualTest();
    RCVTest();
    TransposeTest();

    return 0;
}