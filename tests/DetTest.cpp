//
// Created by Matthew Pombo on 11/24/19.
//

#include "../Matrix.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    double Arow1[2] = {
            2, 4
    };
    double Arow2[2] = {
            3, 1
    };
    double* Arows[] = {
            Arow1, Arow2
    };
    Matrix A(2, 2, Arows);
    assert(A.det() == -10);

    double Brow1[3] = {
            4, 6, 5
    };
    double Brow2[3] = {
            8, 6, 5
    };
    double Brow3[3] = {
            9, 0, 6
    };
    double* Brows[] = {
            Brow1, Brow2, Brow3
    };
    Matrix B(3, 3, Brows);
    assert(B.det() == -144);

    cout << "All determinant tests passed!" << endl;
}