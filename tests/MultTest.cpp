//
// Created by Matthew Pombo on 11/21/19.
//

#include <iostream>
#include <cassert>
#include "../Matrix.h"
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
    cout << "A:" << endl;
    A.print();
    cout << endl;

    // 4x5 matrix B
    int Brow1[5] = {
            1, 2, 3, 4, 5
    };
    int Brow2[5] = {
            2, 3, 4, 5, 6
    };
    int Brow3[5] = {
            3, 4, 5, 6, 7
    };
    int Brow4[5] = {
            4, 5, 6, 7, 8
    };
    int* arrB[] = {
            Brow1, Brow2, Brow3, Brow4
    };
    Matrix B(4, 5, arrB);
    cout << "B:" << endl;
    B.print();
    cout << endl;

    Matrix AB = A * B;
    cout << "AB:" << endl;
    AB.print();
    cout << endl;
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

    cout << "All tests passed!" << endl;
}