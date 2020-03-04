//
// Created by Matthew Pombo on 11/9/19.
//

#include <iostream>
#include <string>
#include <exception>
#include <sstream>
#include "../include/CPPMatrix.h"
using CPPMat::Matrix;

////////////////////////////////
/// Constructors/Destructors ///
////////////////////////////////

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

CPPMat::Matrix::Matrix(int rows, int cols) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor.\n"
            << "'rows' and 'cols' must be greater than 0; received [rows = " << rows << ", cols = " << cols << "].";
        throw std::invalid_argument(err.str());
    }

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = 0;
    }
}

CPPMat::Matrix::Matrix(int rows, int cols, double** matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor.\n"
            << "'rows' and 'cols' must be greater than 0; received [rows = " << rows << ", cols = " << cols << "].";
        throw std::invalid_argument(err.str());
    }

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = matrixArray[i][j];
    }
}

CPPMat::Matrix::Matrix(int rows, int cols, const double* matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor.\n"
            << "'rows' and 'cols' must be greater than 0; received [rows = " << rows << ", cols = " << cols << "].";
        throw std::invalid_argument(err.str());
    }

    m_array = new double*[m_rows];

    int i = 0;
    while (i < m_rows) {
        m_array[i] = new double[m_cols];
        int j = 0;
        while (j < m_cols) {
            m_array[i][j] = matrixArray[i*m_cols + j];
            j++;
        }
        i++;
    }
}

CPPMat::Matrix::Matrix(const Matrix& src) {
    auto** newArr = new double*[src.m_rows];
    for (int i = 0; i < src.m_rows; i++) {
        newArr[i] = new double[src.m_cols];
        for (int j = 0; j < src.m_cols; j++) {
            newArr[i][j] = src.m_array[i][j];
        }
    }

    m_array = newArr;
    m_rows = src.m_rows;
    m_cols = src.m_cols;
}

CPPMat::Matrix::~Matrix() {
    for (int i = 0; i < m_rows; i++)
        delete [] m_array[i];

    delete [] m_array;
}


/////////////////
/// Operators ///
/////////////////

CPPMat::Matrix& CPPMat::Matrix::operator=(const Matrix& src) {
    if (&src == this)
        return *this;

    for (int i = 0; i < src.m_rows; i++)
        delete [] m_array[i];

    delete [] m_array;

    auto** newArr = new double*[src.m_rows];
    for (int i = 0; i < src.m_rows; i++) {
        newArr[i] = new double[src.m_cols];
        for (int j = 0; j < src.m_cols; j++) {
            newArr[i][j] = src.m_array[i][j];
        }
    }

    m_array = newArr;
    m_rows = src.m_rows;
    m_cols = src.m_cols;
    return *this;
}

double CPPMat::Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
}

CPPMat::Matrix& CPPMat::Matrix::operator+(const Matrix& m) const {
    if (m_rows != m.m_rows || m_cols != m.m_cols) {
        std::stringstream err;
        err << "Matrix addition error: operands must have the same dimensions.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") + ("
            << m.m_rows << " x " << m.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    auto** newArr = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        newArr[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++) {
            newArr[i][j] = m_array[i][j] + m.m_array[i][j];
        }
    }
    auto* A = new Matrix(m_rows, m_cols, newArr);
    return *A;
}

bool CPPMat::Matrix::operator==(const Matrix & m) const {
    if (m_rows != m.m_rows || m_cols != m.m_cols) {
        return false;
    }

    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (m_array[i][j] != m.m_array[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool CPPMat::Matrix::operator!=(const Matrix& m) const {
    return !operator==(m);
}


// friend functions
CPPMat::Matrix operator*(const Matrix& A, const Matrix& B) {
    if (A.m_cols != B.m_rows) {
        std::stringstream err;
        err << "Matrix multiplication error: columns in first operand must equal rows in the second.\n"
            << "Received bad matrix dimensions [(" << A.m_rows << " x " << A.m_cols << ") * ("
            << B.m_rows << " x " << B.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    int newRows = A.m_rows;
    int newCols = B.m_cols;
    int commonVal = A.m_cols;
    double newArr[newRows * newCols];

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            double entry = 0;
            for (int k = 0; k < commonVal; k++) {
                entry += (A.m_array[i][k] * B.m_array[k][j]);
            }
            newArr[(i*newCols) + j] = entry;
        }
    }

    return CPPMat::Matrix(newRows, newCols, newArr);
}

// WIP
/*Matrix& Matrix::operator*=(const Matrix &B) {
    if (m_cols != B.m_cols) {
        std::stringstream err;
        err << "Matrix multiplication error: columns in first operand must equal rows in the second.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") * ("
            << B.m_rows << " x " << B.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    int newRows = m_rows;
    int newCols = B.m_cols;
    int commonVal = m_cols;
    auto** newArr = new double*[newRows];

    for (int i = 0; i < newRows; i++) {
        newArr[i] = new double[newCols];
        for (int j = 0; j < newCols; j++) {

        }
    }

    return *this;
}*/

CPPMat::Matrix operator*(double d, const CPPMat::Matrix& A) {
    int rows = A.m_rows;
    int cols = A.m_cols;

    double newArr[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newArr[(i*cols) + j] = A.m_array[i][j] * d;
        }
    }

    return CPPMat::Matrix(rows, cols, newArr);
}

CPPMat::Matrix operator*(const CPPMat::Matrix& A, double d) {
    return d * A;
}


/////////////////
/// Accessors ///
/////////////////

int CPPMat::Matrix::rows() const {
    return m_rows;
}

int CPPMat::Matrix::cols() const {
    return m_cols;
}

void CPPMat::Matrix::print() const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            std::cout << m_array[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

double CPPMat::Matrix::valueAt(int row, int col) const {
    if (row < 1 || row > m_rows || col < 1 || col > m_cols) {
        throw std::out_of_range("Invalid parameters to matrix element access.");
    }

    return m_array[row-1][col-1];
}

// Functions to return an array containing a row or column vector with the elements in the argument's row or column

double* CPPMat::Matrix::rowVector(int row) const {
    if (row < 1 || row > m_rows) {
        throw std::out_of_range("Invalid parameters to matrix row vector");
    }
    auto* rowVec = new double[m_cols];
    for (int i = 0; i < m_cols; i++) {
        rowVec[i] = m_array[row-1][i];
    }
    return rowVec;
}

double* CPPMat::Matrix::colVector(int col) const {
    if (col < 1 || col > m_cols) {
        throw std::out_of_range("Invalid parameters to matrix column vector");
    }
    auto* colVec = new double[m_rows];
    for (int i = 0; i < m_rows; i++) {
        colVec[i] = m_array[i][col-1];
    }
    return colVec;
}

bool CPPMat::Matrix::isSquare() const {
    return m_rows == m_cols;
}

CPPMat::Matrix& CPPMat::Matrix::transpose() const {
    auto** tArr = new double*[m_cols];
    for (int i = 0; i < m_cols; i++) {
        tArr[i] = colVector(i+1);
    }

    auto* T = new Matrix(m_cols, m_rows, tArr);
    return *T;
}

double CPPMat::Matrix::detHelper(int size, int offset, double** array) {
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
        swapRows((offset + 1), (offset + 1) + i);

        determinant += sign * m_array[offset][offset] * detHelper(size - 1, offset + 1, array);
    }

    // the lowest row will be on the top, so just swap them all back


    int j = 1;
    while (j < size) {
        swapRows((offset + j) + 1, offset + j);
        j++;
    }
    return determinant;
}

double CPPMat::Matrix::determinant() {
    if (!isSquare()) {
        std::stringstream err;
        err << "Matrix is not square, cannot take valid determinant.\n"
            << "Expected n x n matrix, received [" << m_rows << " x " << m_cols << "].";

        throw std::invalid_argument(err.str());
    }

    if (m_rows == 1) {
        return valueAt(1, 1);
    }

    return detHelper(m_rows, 0, m_array);
}

// just an alias for determinant()
double CPPMat::Matrix::det() {
    return this->determinant();
}


////////////////
/// Mutators ///
////////////////

// inserts a value 'value' into into the matrix at row 'row,' column 'col'
void CPPMat::Matrix::insert(int row, int col, double value) {
    if (row > m_rows || row < 1 || col > m_cols || col < 1) {
        std::stringstream err;
        err << "Invalid parameters to insert(); arguments must be within matrix dimensions.\n"
            << "Bad arguments [row = " << row << ", col = " << col << "] to (" << m_rows << " x "
            << m_cols << ") matrix.";

        throw std::invalid_argument(err.str());
    }

    m_array[row - 1][col - 1] = value;
}

// simply swaps two rows in a matrix
void CPPMat::Matrix::swapRows(int row1, int row2) {
    if (row1 < 1 || row1 > m_rows || row2 < 1 || row2 > m_rows) {
        std::stringstream err;
        err << "Invalid parameters to swapRows(); arguments must be within matrix dimensions.\n"
            << "Bad arguments [row1 = " << row1 << ", row2 = " << row2 << "] to matrix with " << m_rows << " rows.";

        throw std::invalid_argument(err.str());
    }

    if (row1 == row2) {
        return;
    }

    double* tmp = m_array[row1 - 1];
    m_array[row1 - 1] = m_array[row2 - 1];
    m_array[row2 - 1] = tmp;
}
