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

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = 0;
    }
}

Matrix::Matrix(int rows, int cols, double** matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols))
        cout << invalidInit << endl;

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = matrixArray[i][j];
    }
}

Matrix::Matrix(const Matrix& src) {
    auto** newArr = new double*[src.rows()];
    for (int i = 0; i < src.rows(); i++) {
        newArr[i] = new double[src.cols()];
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

    auto** newArr = new double*[src.rows()];
    for (int i = 0; i < src.rows(); i++) {
        newArr[i] = new double[src.cols()];
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
        auto** arr = new double*[1];
        arr[0] = new double[1];
        arr[0][0] = 0;
        auto* D = new Matrix(1, 1, arr);
        return *D;
    }

    int newRows = this->rows();
    int newCols = m.cols();
    int commonVal = this->cols();
    auto** newArr = new double*[newRows];

    // preemptively make an array of column vectors to save on space and accesses
    auto** columnVectors = new double*[m.cols()];
    for (int i = 0; i < m.cols(); i++) {
        columnVectors[i] = m.colVector(i+1);
    }

    for (int i = 0; i < newRows; i++) {
        double* rowVec = this->rowVector(i+1);
        newArr[i] = new double[newCols];
        for (int j = 0; j < newCols; j++) {
            double entry = 0;
            for (int k = 0; k < commonVal; k++) {
                entry += (rowVec[k] * columnVectors[j][k]);
            }
            newArr[i][j] = entry;
        }
    }

    auto* C = new Matrix(newRows, newCols, newArr);
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

double Matrix::valueAt(int row, int col) const {
    if (row < 1 || row > m_rows || col < 1 || col > m_cols) {
        cerr << "HEY! You tried to access a matrix with invalid parameters. Returning 0." << endl;
        return 0;
    }

    return m_array[row-1][col-1];
}

// Functions to return an array containing a row or column vector with the elements in the argument's row or column

double* Matrix::rowVector(int row) const {
    if (row < 1 || row > this->rows()) {
        cerr << "Invalid dimensions in calling rowVector, returning nullptr." << endl;
        return nullptr;
    }
    auto* rowVec = new double[this->cols()];
    for (int i = 0; i < this->cols(); i++) {
        rowVec[i] = m_array[row-1][i];
    }
    return rowVec;
}

double* Matrix::colVector(int col) const {
    if (col < 1 || col > this->cols()) {
        cerr << "Invalid dimensions in calling colVector, returning nullptr." << endl;
        return nullptr;
    }
    auto* colVec = new double[this->rows()];
    for (int i = 0; i < this->rows(); i++) {
        colVec[i] = m_array[i][col-1];
    }
    return colVec;
}

Matrix& Matrix::transpose() const {
    auto** tArr = new double*[this->cols()];
    for (int i = 0; i < this->cols(); i++) {
        tArr[i] = new double[this->rows()];
        for (int j = 0; j < this->rows(); j++) {
            tArr[i][j] = this->m_array[j][i];
        }
    }

    auto* T = new Matrix(this->cols(), this->rows(), tArr);
    return *T;
}

double Matrix::detHelper(int size, int offset, double** array) {
    if (size == 2) {
        /*
         * Matrix of the form:
         * a b
         * c d ;
         * returns ad - bc
         */
        return ((array[offset][offset]*array[offset+1][offset+1]) - (array[offset][offset+1]*array[offset+1][offset]));
    }

    double determinant = 0;
    for(int i = 0; i < size; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;

        // swapRows treats rows and columns with their actual position, so add 1
        this->swapRows((offset + 1), (offset + 1) + i);

        determinant += sign * m_array[offset][offset] * detHelper(size - 1, offset + 1, array);
    }

    // the lowest row will be on the top, so just swap them all back
    int j = 1;
    while (j < (size + 1)) {
        this->swapRows((offset + j) + 1, offset + j);
        j++;
    }
}

double Matrix::determinant() {
    if (!this->isSquare()) {
        cerr << "Matrix is not square, cannot take valid determinant; returning 0." << endl;
        return 0;
    }
    if (this->rows() == 1)
        return this->valueAt(1, 1);

    return detHelper(m_rows, 0, this->m_array);
}


////////////////
/// Mutators ///
////////////////

// inserts a value 'value' into into the matrix at row 'row,' column 'col'
bool Matrix::insert(int row, int col, double value) {
    if (row > m_rows || row < 1 || col > m_cols || col < 1)
        return false;

    m_array[row - 1][col - 1] = value;
    return true;
}

// simply swaps two rows in a matrix, using the "temp and switch" method
bool Matrix::swapRows(int row1, int row2) {
    if (row1 < 1 || row1 > m_rows || row2 < 1 || row2 > m_rows)
        return false;

    if (row1 == row2)
        return true;

    double* tmp = this->m_array[row1 - 1];
    this->m_array[row1 - 1] = this->m_array[row2 - 1];
    this->m_array[row2 - 1] = tmp;
    return true;
}