//
// Created by Matthew Pombo on 11/24/19.
//

#include "../src/Matrix.h"
#include "MainTest.h"
#include <iostream>
#include <cassert>

void DetTest() {
    std::cout << "Starting determinant tests..." << std::endl;

    double Arow1[2] = { 2, 4 };
    double Arow2[2] = { 3, 1 };
    double* Arows[] = { Arow1, Arow2 };
    Matrix A(2, 2, Arows);

    assert(A.det() == -10);
    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            assert(A(i+1, j+1) == Arows[i][j]);
        }
    }

    double Brow1[3] = { 4, 6, 5 };
    double Brow2[3] = { 8, 6, 5 };
    double Brow3[3] = { 9, 0, 6 };
    double* Brows[] = { Brow1, Brow2, Brow3 };
    Matrix B(3, 3, Brows);

    assert(B.det() == -144);
    for (int i = 0; i < B.rows(); i++) {
        for (int j = 0; j < B.cols(); j++) {
            assert(B(i+1, j+1) == Brows[i][j]);
        }
    }

    double Crow1[4] = { 1, 3, 5, 9 };
    double Crow2[4] = { 1, 3, 1, 7 };
    double Crow3[4] = { 4, 3, 9, 7 };
    double Crow4[4] = { 5, 2, 0, 9 };
    double* Crows[] = { Crow1, Crow2, Crow3, Crow4 };
    Matrix C(4, 4, Crows);

    assert(C.det() == -376);
    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.cols(); j++) {
            assert(C(i+1, j+1) == Crows[i][j]);
        }
    }

    double Drow1[5] = { 9, 5, 3, 6, 7 };
    double Drow2[5] = { 5, 6, 2, 5, 5 };
    double Drow3[5] = { 2, 5, 7, 3, 4 };
    double Drow4[5] = { 5, 3, 7, 3, 1 };
    double Drow5[5] = { 2, 4, 7, 3, 1 };
    double* Drows[] = { Drow1, Drow2, Drow3, Drow4, Drow5 };
    Matrix D(5, 5, Drows);

    assert(D.det() == 420);
    for (int i = 0; i < D.rows(); i++) {
        for (int j = 0; j < D.cols(); j++) {
            assert(D(i+1, j+1) == Drows[i][j]);
        }
    }

    std::cout << "All determinant tests passed!" << std::endl << std::endl;
}