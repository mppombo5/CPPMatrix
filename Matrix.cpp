//
// Created by Matthew Pombo on 11/9/19.
//

#include <iostream>
#include <iomanip>
#include "Matrix.h"
using namespace std;

////////////////////////////////
/// Constructors/Destructors ///
////////////////////////////////

const char* invalidInit = "HEY! Those are invalid dimensions. Must have more than 1 rows and columns. Defaulting to 1x1 matrix.";

bool initialize(int rows, int cols, int* targetRows, int* targetCols) {
    if (rows < 1 || cols < 1) {
        *targetRows = 1;
        *targetCols = 1;
        return false;
    }
    *targetRows = rows;
    *targetCols = cols;
    return true;
}

Matrix::Matrix(int rows, int cols) {
    if (!initialize(rows, cols, &m_rows, &m_cols))
        cerr << invalidInit << endl;

    m_array = new int*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new int[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = 0;
    }
}

Matrix::Matrix(int rows, int cols, int** matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols))
        cout << invalidInit << endl;

    m_array = new int*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new int[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = matrixArray[i][j];
    }
}

Matrix::Matrix(const Matrix& src) {
    int** newArr = new int*[src.rows()];
    for (int i = 0; i < src.rows(); i++) {
        newArr[i] = new int[src.cols()];
        for (int j = 0; j < src.cols(); j++) {
            newArr[i][j] = src.m_array[i][j];
        }
    }

    m_array = newArr;
    m_rows = src.rows();
    m_cols = src.cols();
}

Matrix::~Matrix() {
    for (int i = 0; i < m_rows; i++)
        delete [] m_array[i];

    delete [] m_array;
}


/////////////////
/// Operators ///
/////////////////

Matrix& Matrix::operator=(const Matrix& src) {
    for (int i = 0; i < src.rows(); i++)
        delete [] m_array[i];

    delete [] m_array;

    int** newArr = new int*[src.rows()];
    for (int i = 0; i < src.rows(); i++) {
        newArr[i] = new int[src.cols()];
        for (int j = 0; j < src.cols(); j++) {
            newArr[i][j] = src.m_array[i][j];
        }
    }

    m_array = newArr;
    m_rows = src.rows();
    m_cols = src.cols();
    return *this;
}

Matrix& Matrix::operator*(const Matrix& m) const {
    if (this->cols() != m.rows()) {
        cerr << "ERROR! The columns in the first operand must equal the rows in the second operand." << endl
             << "Returning 1x1 matrix." << endl << "Eventually I'll handle exceptions correctly." << endl;
        int** arr = new int*[1];
        arr[0] = new int[1];
        arr[0][0] = 0;
        Matrix* D = new Matrix(1, 1, arr);
        return *D;
    }

    int newRows = this->rows();
    int newCols = m.cols();
    int commonVal = this->cols();

    int** newArr = new int*[newRows];
    for (int i = 0; i < newRows; i++) {
        newArr[i] = new int[newCols];
        for (int j = 0; j < newCols; j++) {
            int entry = 0;
            for (int k = 0; k < commonVal; k++) {
                entry += (this->m_array[i][k] + m.m_array[k][j]);
            }
            newArr[i][j] = entry;
        }
    }
    Matrix* C = new Matrix(newRows, newCols, newArr);
    return *C;
}


/////////////////
/// Accessors ///
/////////////////

void Matrix::print() const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << m_array[i][j] << "\t";
        }
        cout << endl;
    }
}

int Matrix::valueAt(int row, int col) const {
    if (row < 1 || row > m_rows || col < 1 || col > m_cols) {
        cerr << "HEY! You tried to access a matrix with invalid parameters. Returning 0." << endl;
        return 0;
    }

    return m_array[row-1][col-1];
}

int* Matrix::rowVector(int row) const {
    int* rowVec = new int[this->cols()];
    for (int i = 0; i < this->cols(); i++) {
        rowVec[i] = m_array[row-1][i];
    }
    return rowVec;
}

int* Matrix::colVector(int col) const {
    int* colVec = new int[this->rows()];
    for (int i = 0; i < this->rows(); i++) {
        colVec[i] = m_array[i][col-1];
    }
    return colVec;
}

Matrix& Matrix::transpose() const {
    int** tArr = new int*[this->cols()];
    for (int i = 0; i < this->cols(); i++) {
        tArr[i] = new int[this->rows()];
        for (int j = 0; j < this->rows(); j++) {
            tArr[i][j] = this->m_array[j][i];
        }
    }

    Matrix* T = new Matrix(this->cols(), this->rows(), tArr);
    return *T;
}


////////////////
/// Mutators ///
////////////////

bool Matrix::insert(int row, int col, int value) {
    if (row > m_rows || row < 1 || col > m_cols || col < 1)
        return false;

    m_array[row - 1][col - 1] = value;
    return true;
}
