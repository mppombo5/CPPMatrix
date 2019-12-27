//
// Created by Matthew Pombo on 12/14/19.
//

/*
 * This test file exists solely for the purpose of testing out the different constructors and making sure
 * they all work fine. The majority of this will probably just be copying and pasting other code from
 * test files and using different constructors on them.
 */

#include "../src/Matrix.h"
#include "MainTest.h"
#include <iostream>

void ConstructTest() {
    std::cout << "Starting constructor tests..." << std::endl;

    // copy and paste from DetTest.cpp
    double Darr[5*5] = {
            9, 5, 3, 6, 7,
            5, 6, 2, 5, 5,
            2, 5, 7, 3, 4,
            5, 3, 7, 3, 1,
            2, 4, 7, 3, 1
    };
    Matrix D(5, 5, Darr);
    assert(D.det() == 420);

    // copy-paste from RCVector tests
    double Aarr[3*4] = {
            1, 2, 3, 4,
            2, 3, 4, 5,
            3, 4, 5, 6
    };

    Matrix A(3, 4, Aarr);

    double colVec[3] = { 2, 3, 4 };
    double* AcolVec1 = A.colVector(2);
    for (int i = 0; i < A.rows(); i++) {
        assert(colVec[i] == AcolVec1[i]);
    }

    std::cout << "All constructor tests passed!" << std::endl << std::endl;
}