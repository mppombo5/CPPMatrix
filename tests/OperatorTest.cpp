//
// Created by Matthew Pombo on 11/21/19.
//

#include <iostream>
#include <cassert>
#include "MainTest.h"
#include "../src/Matrix.h"
using namespace std;

void MultTest() {
    cout << "Starting multiplication tests..." << endl;

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

    // 4x5 matrix B
    double Brow1[5] = {
            1, 2, 3, 4, 5
    };
    double Brow2[5] = {
            2, 3, 4, 5, 6
    };
    double Brow3[5] = {
            3, 4, 5, 6, 7
    };
    double Brow4[5] = {
            4, 5, 6, 7, 8
    };
    double* arrB[] = {
            Brow1, Brow2, Brow3, Brow4
    };
    Matrix B(4, 5, arrB);

    Matrix AB = A * B;
    assert(AB.rows() == A.rows());
    assert(AB.cols() == B.cols());
    assert(AB(1, 1) == 1*1 + 2*2 + 3*3 + 4*4);
    assert(AB(1, 2) == 1*2 + 2*3 + 3*4 + 4*5);
    assert(AB(2, 2) == 2*2 + 3 * 3 + 4 * 4 + 5 * 5);
    assert(AB(1, 5) == 1*5 + 2 * 6 + 3 * 7 + 4 * 8);

    Matrix D(7, 9);
    Matrix E(7, 9);
    Matrix DE = D * E;
    assert(DE.rows() == 1);
    assert(DE.cols() == 1);

    cout << "All multiplication tests passed!" << endl;
}

void AddTest() {
    cout << "Starting addition tests..." << endl;

    double Arow1[2] = {
            1, 0
    };
    double Arow2[2] = {
            0, 1
    };
    double* Arows[] = {
            Arow1, Arow2
    };
    Matrix A(2, 2, Arows);

    double Brow1[2] = {
            3, 0
    };
    double Brow2[2] = {
            0, 3
    };
    double* Brows[] = {
            Brow1, Brow2
    };
    Matrix B(2, 2, Brows);

    Matrix C = A + B;
    double Crow1[2] = {
            4, 0
    };
    double Crow2[2] = {
            0, 4
    };
    double* Crows[] = {
            Crow1, Crow2
    };

    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            assert(C(i+1, j+1) == Crows[i][j]);
        }
    }

    double Drow1[2] = {
            0, 1
    };
    double Drow2[2] = {
            1, 0
    };
    double* Drows[] = {
            Drow1, Drow2
    };
    Matrix D(2, 2, Drows);
    C = A + D;
    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            assert(C(i+1, j+1) == 1);
        }
    }

    double Erow1[3] = {
            1, 1, 1
    };
    double Erow2[3] = {
            1, 1, 1
    };
    double* Erows[] = {
            Erow1, Erow2
    };
    Matrix E(2, 3, Erows);
    C = A + E;
    assert(C.rows() == 1 && C.cols() == 1 && C(1, 1) == 0);

    cout << "All addition tests passed!" << endl;
}
