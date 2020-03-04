//
// Created by Matthew Pombo on 11/21/19.
//

#include <iostream>
#include <cassert>
#include "../include/CPPMatrix.h"
#include "MainTest.h"
using CPPMat::Matrix;

void MultTest() {
    std::cout << "Starting multiplication tests..." << std::endl;

    // 3x4 matrix A
    double Arow1[4] = { 1, 2, 3, 4 };
    double Arow2[4] = { 2, 3, 4, 5 };
    double Arow3[4] = { 3, 4, 5, 6 };
    double* arrA[] = { Arow1, Arow2, Arow3 };
    CPPMat::Matrix A(3, 4, arrA);

    // 4x5 matrix B
    double Brow1[5] = { 1, 2, 3, 4, 5 };
    double Brow2[5] = { 2, 3, 4, 5, 6 };
    double Brow3[5] = { 3, 4, 5, 6, 7 };
    double Brow4[5] = { 4, 5, 6, 7, 8 };
    double* arrB[] = { Brow1, Brow2, Brow3, Brow4 };
    CPPMat::Matrix B(4, 5, arrB);

    CPPMat::Matrix AB = A * B;
    assert(AB.rows() == A.rows());
    assert(AB.cols() == B.cols());
    assert(AB(1, 1) == 1*1 + 2*2 + 3*3 + 4*4);
    assert(AB(1, 2) == 1*2 + 2*3 + 3*4 + 4*5);
    assert(AB(2, 2) == 2*2 + 3 * 3 + 4 * 4 + 5 * 5);
    assert(AB(1, 5) == 1*5 + 2 * 6 + 3 * 7 + 4 * 8);

    A *= B;
    assert(A == AB);

    CPPMat::Matrix D(7, 9);
    CPPMat::Matrix E(7, 9);
    bool caughtMult1 = false;
    try {
        CPPMat::Matrix DE = D * E;
    }
    catch (std::invalid_argument&) {
        caughtMult1 = true;
    }
    assert(caughtMult1);

    bool caughtMult2 = false;
    try {
        CPPMat::Matrix F = CPPMat::Matrix(4, 5) * CPPMat::Matrix(6, 4);
    }
    catch (std::invalid_argument&) {
        caughtMult2 = true;
    }
    assert(caughtMult2);


    // test Matrix-double multiplication
    double Farr[3 * 3] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };
    Matrix F(3, 3,Farr);
    double d1 = 3.6;
    Matrix d1F = d1 * F;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(d1F(i + 1, j + 1) == (d1 * F(i + 1, j + 1)));
        }
    }

    F *= d1;
    assert(F == d1F);

    std::cout << "All multiplication tests passed." << "\n\n";
}

void AddTest() {
    std::cout << "Starting addition tests..." << std::endl;

    double Arow1[2] = { 1, 0 };
    double Arow2[2] = { 0, 1 };
    double* Arows[] = { Arow1, Arow2 };
    CPPMat::Matrix A(2, 2, Arows);

    double Brow1[2] = { 3, 0 };
    double Brow2[2] = { 0, 3 };
    double* Brows[] = { Brow1, Brow2 };
    CPPMat::Matrix B(2, 2, Brows);

    CPPMat::Matrix C = A + B;
    double Crow1[2] = { 4, 0 };
    double Crow2[2] = { 0, 4 };
    double* Crows[] = { Crow1, Crow2 };

    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            assert(C(i+1, j+1) == Crows[i][j]);
        }
    }

    double Drow1[2] = { 0, 1 };
    double Drow2[2] = { 1, 0 };
    double* Drows[] = { Drow1, Drow2 };
    CPPMat::Matrix D(2, 2, Drows);

    C = A + D;
    for (int i = 0; i < A.rows(); i++) {
        for (int j = 0; j < A.cols(); j++) {
            assert(C(i+1, j+1) == 1);
        }
    }

    double Erow1[3] = { 1, 1, 1 };
    double Erow2[3] = { 1, 1, 1 };
    double* Erows[] = { Erow1, Erow2 };
    CPPMat::Matrix E(2, 3, Erows);
    bool caughtIA1 = false;
    try {
        C = A + E;
    }
    catch (std::invalid_argument&) {
        caughtIA1 = true;
    }
    assert(caughtIA1);

    bool caughtIA2 = false;
    try {
        Matrix F = Matrix(4, 4) + Matrix(4, 5);
    }
    catch (std::invalid_argument&) {
        caughtIA2 = true;
    }
    assert(caughtIA2);

    std::cout << "All addition tests passed." << "\n\n";
}

void EqualTest() {
    std::cout << "Starting equivalence tests..." << std::endl;

    double Arow1[2] = { 1, 1 };
    double Arow2[2] = { 2, 2 };
    double* Arows[] = { Arow1, Arow2 };
    CPPMat::Matrix A(2, 2, Arows);

    double Brow1[2] = { 1, 1 };
    double Brow2[2] = { 2, 2 };
    double* Brows[] = { Brow1, Brow2 };
    CPPMat::Matrix B(2, 2, Brows);

    assert(A == B && !(A != B));

    double Crow1[2] = { 1, 1 };
    double Crow2[2] = { 2, 1 };
    double* Crows[] = { Crow1, Crow2 };
    CPPMat::Matrix C(2, 2, Crows);

    assert(A != C && !(A == C));

    double Drow1[3] = { 1, 1, 1 };
    double Drow2[3] = { 2, 2, 2 };
    double* Drows[] = { Drow1, Drow2 };
    CPPMat::Matrix D(2, 3, Drows);

    assert(A != D && !(A == D));

    std::cout << "Equivalence tests passed." << "\n\n";
}

void ParenTest() {
    std::cout << "Starting matrix access tests..." << std::endl;

    double Aarr[12] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6
    };
    Matrix A(3, 4, Aarr);
    double bad;
    // BA = bad access
    bool caughtBA1 = false;
    try {
        bad = A(2, 5);
    }
    catch (std::out_of_range&) {
        caughtBA1 = true;
    }
    assert(caughtBA1);

    bool caughtBA2 = false;
    try {
        bad = A(0, -1);
    }
    catch (std::out_of_range&) {
        caughtBA2 = true;
    }
    assert(caughtBA2);

    std::cout << "Access tests passed." << "\n\n";
}
