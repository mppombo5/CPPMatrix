//
// Created by Matthew Pombo on 11/21/19.
//

// test cases for row and column vectors

#include "../Matrix.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    // 3x4 matrix A
    double Arow1[4] = {
            1, 2, 3, 4
    };
    double Arow2[4] = {
            2, 3, 4, 5
    };
    double Arow3[4] = {
            3, 4, 5, 6
    };
    double* arrA[] = {
            Arow1, Arow2, Arow3
    };
    Matrix A(3, 4, arrA);

    double colVec[3] = {
            2, 3, 4
    };
    double* AcolVec1 = A.colVector(2);
    for (int i = 0; i < A.rows(); i++) {
        assert(colVec[i] == AcolVec1[i]);
    }

    double rowVec[4] = {
            2, 3, 4, 5
    };
    double* ArowVec1 = A.rowVector(2);
    for (int i = 0; i < A.cols(); i++) {
        assert(rowVec[i] == ArowVec1[i]);
    }
    double* invalidRowVec = A.rowVector(4);
    double* invalidRowVec2 = A.rowVector(0);
    assert(invalidRowVec ==  nullptr && invalidRowVec2 == nullptr);

    double* invalidColVec = A.colVector(5);
    double* invalidColVec2 = A.colVector(0);
    assert(invalidColVec == nullptr && invalidColVec2 == nullptr);

    cout << "All RCVector tests passed!" << endl;
}