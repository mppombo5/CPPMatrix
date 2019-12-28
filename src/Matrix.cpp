//
// Created by Matthew Pombo on 11/9/19.
//

#include <iostream>
#include "../include/CPPMatrix.h"

////////////////////////////////
/// Constructors/Destructors ///
////////////////////////////////

const char* invalidInit = "Invalid dimensions passed to constructor; defaulting to 1x1 matrix.";

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
    if (!initialize(rows, cols, &m_rows, &m_cols))
        std::cerr << invalidInit << std::endl;

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = 0;
    }
}

CPPMat::Matrix::Matrix(int rows, int cols, double** matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols))
        std::cerr << invalidInit << std::endl;

    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = matrixArray[i][j];
    }
}

CPPMat::Matrix::Matrix(int rows, int cols, double* matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols))
        std::cerr << invalidInit << std::endl;

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

CPPMat::Matrix& CPPMat::Matrix::operator*(const Matrix& m) const {
    if (m_cols != m.m_rows) {
        std::cerr << "Matrix multiplication error: The columns in the first operand must equal the rows in the second operand." << std::endl
             << "Returning 1x1 matrix." << std::endl;
        auto* D = new Matrix(1, 1);
        return *D;
    }

    int newRows = m_rows;
    int newCols = m.m_cols;
    int commonVal = m_cols;
    auto** newArr = new double*[newRows];

    // preemptively make an array of column vectors to save on space and accesses
    auto** columnVectors = new double*[m.m_cols];
    for (int i = 0; i < m.m_cols; i++) {
        columnVectors[i] = m.colVector(i+1);
    }

    for (int i = 0; i < newRows; i++) {
        double* rowVec = rowVector(i+1);
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

CPPMat::Matrix& CPPMat::Matrix::operator+(const Matrix& m) const {
    if (m_rows != m.m_rows || m_cols != m.m_cols) {
        std::cerr << "Matrix addition error: the two operands must have the same dimensions." << std::endl
             << "Returning 1x1 matrix." << std::endl;
        auto* D = new Matrix(1, 1);
        return *D;
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
        std::cerr << "Attempted element access to matrix with invalid dimensions. Returning 0." << std::endl;
        return 0;
    }

    return m_array[row-1][col-1];
}

// Functions to return an array containing a row or column vector with the elements in the argument's row or column

double* CPPMat::Matrix::rowVector(int row) const {
    if (row < 1 || row > m_rows) {
        std::cerr << "Invalid dimensions in calling rowVector, returning nullptr." << std::endl;
        return nullptr;
    }
    auto* rowVec = new double[m_cols];
    for (int i = 0; i < m_cols; i++) {
        rowVec[i] = m_array[row-1][i];
    }
    return rowVec;
}

double* CPPMat::Matrix::colVector(int col) const {
    if (col < 1 || col > m_cols) {
        std::cerr << "Invalid dimensions in calling colVector, returning nullptr." << std::endl;
        return nullptr;
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
    while (j < (size + 1)) {
        swapRows((offset + j) + 1, offset + j);
        j++;
    }
    return determinant;
}

double CPPMat::Matrix::determinant() {
    if (!isSquare()) {
        std::cerr << "Matrix is not square, cannot take valid determinant; returning 0." << std::endl;
        return 0;
    }
    if (m_rows == 1)
        return valueAt(1, 1);

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
bool CPPMat::Matrix::insert(int row, int col, double value) {
    if (row > m_rows || row < 1 || col > m_cols || col < 1)
        return false;

    m_array[row - 1][col - 1] = value;
    return true;
}

// simply swaps two rows in a matrix, using the "temp and switch" method
bool CPPMat::Matrix::swapRows(int row1, int row2) {
    if (row1 < 1 || row1 > m_rows || row2 < 1 || row2 > m_rows)
        return false;

    if (row1 == row2)
        return true;

    double* tmp = m_array[row1 - 1];
    m_array[row1 - 1] = m_array[row2 - 1];
    m_array[row2 - 1] = tmp;
    return true;
}
