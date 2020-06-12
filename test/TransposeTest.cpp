//
// Created by Matthew Pombo on 12/4/19.
//

#include "../include/CPPMatrix.h"
#include "MainTest.h"
#include <iostream>
#include <cassert>
using cppmat::Matrix;

void TransposeTest() {
    std::cout << "Starting transpose tests..." << std::endl;

    double Arow1[3] = { 1, 2, 3 };
    double Arow2[3] = { 4, 5, 6 };
    double Arow3[3] = { 7, 8, 9 };
    double Arow4[3] = { 10, 11, 12 };
    double Arow5[3] = { 13, 14, 15 };
    double* Arows[] = { Arow1, Arow2, Arow3, Arow4, Arow5 };
    cppmat::Matrix A(5, 3, Arows);
   /*
    * 1  2  3
    * 4  5  6
    * 7  8  9
    * 10 11 12
    * 13 14 15
    */

   /*
    * transpose should be
    * 1   4   7   10  13
    * 2   5   8   11  14
    * 3   6   9   12  15
    */
    double ATrow1[5] = { 1, 4, 7, 10, 13 };
    double ATrow2[5] = { 2, 5, 8, 11, 14 };
    double ATrow3[5] = { 3, 6, 9, 12, 15 };
    double* ATrows[] = { ATrow1, ATrow2, ATrow3 };
    cppmat::Matrix AT = A.transpose();

    for (int i = 0; i < AT.rows(); i++) {
        for (int j = 0; j < AT.cols(); j++) {
            assert(AT(i+1, j+1) == ATrows[i][j]);
        }
    }

    double Barr[4 * 4] = {
            1,  2,  3,  4,
            5,  6,  7,  8,
            9,  10, 11, 12,
            13, 14, 15, 16
    };
    Matrix B(4, 4, Barr);

    double BTarr[4 * 4] = {
            1, 5, 9, 13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16
    };
    Matrix BT = B.transpose();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(BT(i+1, j+1) == BTarr[i*4 + j]);
        }
    }

    std::cout << "All transpose tests passed." << std::endl << std::endl;
}
