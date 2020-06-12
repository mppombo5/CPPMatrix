//
// Created by Matthew Pombo on 11/21/19.
//

// test cases for row and column vectors

#include "../include/CPPMatrix.h"
#include "MainTest.h"
#include <iostream>
#include <vector>
#include <cassert>

void RCVTest() {
    std::cout << "Starting row/column vector tests..." << std::endl;

    // 3x4 matrix A
    double Arow1[4] = { 1, 2, 3, 4 };
    double Arow2[4] = { 2, 3, 4, 5 };
    double Arow3[4] = { 3, 4, 5, 6 };
    double* arrA[] = { Arow1, Arow2, Arow3 };
    cppmat::Matrix A(3, 4, arrA);

    double colVec[3] = { 2, 3, 4 };
    std::vector<double> AcolVec1 = A.colVector(2);
    for (int i = 0; i < A.rows(); i++) {
        assert(colVec[i] == AcolVec1[i]);
    }

    double rowVec[4] = { 2, 3, 4, 5 };
    std::vector<double> ArowVec1 = A.rowVector(2);
    for (int i = 0; i < A.cols(); i++) {
        assert(rowVec[i] == ArowVec1[i]);
    }

    std::vector<double> invalidRowVec;
    bool caughtRV1 = false;
    try {
        invalidRowVec = A.rowVector(4);
    }
    catch (std::out_of_range&) {
        caughtRV1 = true;
    }
    assert(caughtRV1);

    bool caughtRV2 = false;
    try {
        invalidRowVec = A.rowVector(0);
    }
    catch (std::out_of_range&) {
        caughtRV2 = true;
    }
    assert(caughtRV2);

    std::vector<double> invalidColVec;
    bool caughtCV1 = false;
    try {
        invalidColVec = A.colVector(5);
    }
    catch (std::out_of_range&) {
        caughtCV1 = true;
    }
    assert(caughtCV1);

    bool caughtCV2 = false;
    try {
        invalidColVec = A.colVector(0);
    }
    catch (std::out_of_range&) {
        caughtCV2 = true;
    }
    assert(caughtCV2);

    std::cout << "All RCVector tests passed." << std::endl << std::endl;
}