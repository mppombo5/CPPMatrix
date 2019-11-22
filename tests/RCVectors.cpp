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
    int Arow1[4] = {
            1, 2, 3, 4
    };
    int Arow2[4] = {
            2, 3, 4, 5
    };
    int Arow3[4] = {
            3, 4, 5, 6
    };
    int* arrA[] = {
            Arow1, Arow2, Arow3
    };
    Matrix A(3, 4, arrA);

    int colVec[3] = {
            2, 3, 4
    };
    int* AcolVec1 = A.colVector(2);
    for (int i = 0; i < A.rows(); i++) {
        assert(colVec[i] == AcolVec1[i]);
    }

    int rowVec[4] = {
            2, 3, 4, 5
    };
    int* ArowVec1 = A.rowVector(2);
    for (int i = 0; i < A.cols(); i++) {
        assert(rowVec[i] == ArowVec1[i]);
    }
    int* invalidRowVec = A.rowVector(4);
    int* invalidRowVec2 = A.rowVector(0);
    assert(invalidRowVec ==  nullptr && invalidRowVec2 == nullptr);

    int* invalidColVec = A.colVector(5);
    int* invalidColVec2 = A.colVector(0);
    assert(invalidColVec == nullptr && invalidColVec2 == nullptr);

    cout << "All RCVector tests passed!" << endl;
}