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

    cout << "All determinant tests passed!" << endl;
}