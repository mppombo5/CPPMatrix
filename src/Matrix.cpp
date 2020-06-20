//
// Created by Matthew Pombo on 11/9/19.
//

#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "../include/CPPMatrix.h"

////////////////////////////////
/// Constructors/Destructors ///
////////////////////////////////

// This is a general function to speed up the process of checking the
// validity of a Matrix when it's trying to be constructed.
// Returns false if the supplied arguments are invalid,
// returns true and initializes data members otherwise.
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

// Closest thing to a default constructor. Takes in number of rows and number
// of columns, and initializes all entries to 0.
cppmat::Matrix::Matrix(int rows, int cols) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor:\n"
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

// Takes in a 2D array of doubles and initializes values according to said array.
cppmat::Matrix::Matrix(int rows, int cols, double** matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor:\n"
            << "'rows' and 'cols' must be greater than 0; received [rows = " << rows << ", cols = " << cols << "].";
        throw std::invalid_argument(err.str());
    }

    // Initialize matrix values based on the 2D array.
    m_array = new double*[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_array[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j++)
            m_array[i][j] = matrixArray[i][j];
    }
}

// Slightly more user-friendly constructor, which only
// uses a single array of doubles to initialize.
cppmat::Matrix::Matrix(int rows, int cols, const double* matrixArray) {
    if (!initialize(rows, cols, &m_rows, &m_cols)) {
        std::stringstream err;
        err << "Invalid dimensions passed to Matrix constructor:\n"
            << "'rows' and 'cols' must be greater than 0; received [rows = " << rows << ", cols = " << cols << "].";
        throw std::invalid_argument(err.str());
    }

    m_array = new double*[m_rows];

    // The logic here divides the single array into however many rows and columns the matrix has.
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

// Copy constructor.
cppmat::Matrix::Matrix(const Matrix& src) {
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

// Copy assignment operator.
cppmat::Matrix& cppmat::Matrix::operator=(const Matrix& src) {
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

// Move constructor.
cppmat::Matrix::Matrix(Matrix &&src) noexcept {
    m_rows = src.m_rows;
    m_cols = src.m_cols;
    m_array = src.m_array;

    // Have to free data from src to avoid multiple/duplicate memory freeing.
    src.m_rows = 0;
    src.m_cols = 0;
    src.m_array = nullptr;
}

// Move assignment operator.
cppmat::Matrix& cppmat::Matrix::operator=(Matrix&& src) noexcept {
    if (this != &src) {
        // Delete each array pointed to by each element in m_array. (2D array being freed.)
        for (int i = 0; i < m_rows; i++) {
            delete[] m_array[i];
        }
        delete[] m_array;

        m_rows = src.m_rows;
        m_cols = src.m_cols;
        m_array = src.m_array;

        // Free data from src to avoid duplicate memory freeing.
        src.m_rows = 0;
        src.m_cols = 0;
        src.m_array = nullptr;
    }

    return *this;
}

// Basic destructor, just deletes dynamically allocated memory used by the matrix.
cppmat::Matrix::~Matrix() {
    for (int i = 0; i < m_rows; i++)
        delete [] m_array[i];

    delete [] m_array;
}


/////////////////
/// Operators ///
/////////////////

// Parentheses operator for quick access to a matrix value.
// e.g. to get the value in the 2nd row, 3rd column,
// you can use double x = A(2, 3).
// IMPORTANT: row/column values are *1-INDEXED*.
double cppmat::Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
}

// Returns whether two matrices are the same size and have the same elements.
bool cppmat::Matrix::operator==(const Matrix & m) const {
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

// Inverts the equality operator.
bool cppmat::Matrix::operator!=(const Matrix& m) const {
    return !operator==(m);
}

// Overloaded multiplication operator. Returns the result of multiplying
// the two matrix operands together.
cppmat::Matrix cppmat::Matrix::operator*(const cppmat::Matrix& rhs) const {
    if (m_cols != rhs.m_rows) {
        std::stringstream err;
        err << "Matrix multiplication error: columns in first operand must equal rows in the second.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") * ("
            << rhs.m_rows << " x " << rhs.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    // Construct the new matrix to return.
    int newRows = m_rows;
    int newCols = rhs.m_cols;
    int commonVal = m_cols;
    auto* newArr = new double[newRows * newCols];

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            double entry = 0;
            for (int k = 0; k < commonVal; k++) {
                entry += (m_array[i][k] * rhs.m_array[k][j]);
            }
            newArr[(i*newCols) + j] = entry;
        }
    }

    cppmat::Matrix result(newRows, newCols, newArr);
    delete [] newArr;
    return result;
}

// Similar to the friend multiplication operator, but with assignment at the end.
cppmat::Matrix& cppmat::Matrix::operator*=(const Matrix &B) {
    if (m_cols != B.m_rows) {
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
            double entry = 0;
            for (int k = 0; k < commonVal; k++) {
                entry += (m_array[i][k] * B.m_array[k][j]);
            }
            newArr[i][j] = entry;
        }
    }

    // Free previously used memory to prevent memory leaks.
    for (int i = 0; i < m_rows; i++) {
        delete [] m_array[i];
    }
    delete [] m_array;

    // m_rows doesn't need to be updated.
    m_cols = newCols;
    m_array = newArr;

    return *this;
}

// Multiplies each element in 'A' by 'd'.
cppmat::Matrix cppmat::Matrix::operator*(double d) const {
    int rows = m_rows;
    int cols = m_cols;
    auto* newArr = new double[rows * cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newArr[(i*cols) + j] = m_array[i][j] * d;
        }
    }

    cppmat::Matrix result(rows, cols, newArr);
    delete [] newArr;
    return result;
}

cppmat::Matrix cppmat::operator*(double d, const cppmat::Matrix& A) {
    return A * d;
}

cppmat::Matrix& cppmat::Matrix::operator*=(double d) {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_array[i][j] *= d;
        }
    }

    return *this;
}

// Friend function that returns the result of adding
// all corresponding elements of this matrix and 'rhs' together.
cppmat::Matrix cppmat::Matrix::operator+(const cppmat::Matrix& rhs) const {
    if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
        std::stringstream err;
        err << "Matrix addition error: operands must have the same dimensions.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") + ("
            << rhs.m_rows << " x " << rhs.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    int newRows = m_rows;
    int newCols = m_cols;
    auto* newArr = new double[newRows * newCols];

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            newArr[(i*newCols) + j] = m_array[i][j] + rhs.m_array[i][j];
        }
    }

    cppmat::Matrix result(newRows, newCols, newArr);
    delete [] newArr;
    return result;
}

cppmat::Matrix& cppmat::Matrix::operator+=(const Matrix& B) {
    if (m_rows != B.m_rows || m_cols != B.m_cols) {
        std::stringstream err;
        err << "Matrix addition error: operands must have the same dimensions.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") + ("
            << B.m_rows << " x " << B.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_array[i][j] += B.m_array[i][j];
        }
    }

    return *this;
}

// Same idea as the addition operator, but with subtraction instead.
cppmat::Matrix cppmat::Matrix::operator-(const cppmat::Matrix& rhs) const {
    if (m_rows != rhs.m_rows || m_cols != rhs.m_cols) {
        std::stringstream err;
        err << "Matrix subtraction error: operands must have the same dimensions.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") - ("
            << rhs.m_rows << " x " << rhs.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    int newRows = m_rows;
    int newCols = m_cols;
    auto* newArr = new double[newRows * newCols];

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            newArr[(i*newCols) + j] = m_array[i][j] - rhs.m_array[i][j];
        }
    }

    cppmat::Matrix result(newRows, newCols, newArr);
    delete [] newArr;
    return result;
}

cppmat::Matrix& cppmat::Matrix::operator-=(const Matrix& B) {
    if (m_rows != B.m_rows || m_cols != B.m_cols) {
        std::stringstream err;
        err << "Matrix subtraction error: operands must have the same dimensions.\n"
            << "Received bad matrix dimensions [(" << m_rows << " x " << m_cols << ") - ("
            << B.m_rows << " x " << B.m_cols << ")].";
        throw std::invalid_argument(err.str());
    }

    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_array[i][j] -= B.m_array[i][j];
        }
    }

    return *this;
}

// Gives an easier syntax for formatting all elments in the array.
// With this function, you can do things like { std::cout << A; }.
std::ostream& cppmat::operator<<(std::ostream& lhs, const cppmat::Matrix& rhs) {
    for (int i = 0; i < rhs.m_rows; i++) {
        for (int j = 0; j < rhs.m_cols; j++) {
            lhs << rhs.m_array[i][j];
            if (j != rhs.m_cols - 1) {
                lhs << '\t';
            }
        }
        lhs << std::endl;
    }

    return lhs;
}


/////////////////
/// Accessors ///
/////////////////

int cppmat::Matrix::rows() const {
    return m_rows;
}

int cppmat::Matrix::cols() const {
    return m_cols;
}

// Predecessor to ostream& operator<<.
void cppmat::Matrix::print() const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            std::cout << m_array[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// Returns *1-INDEXED* value in the matrix at row 'row' and column 'col'.
double cppmat::Matrix::valueAt(int row, int col) const {
    if (row < 1 || row > m_rows || col < 1 || col > m_cols) {
        std::stringstream err;
        err << "Bad matrix access:\n"
            << "attempted access to element (" << row << ", " << col <<") in (" << m_rows << " x " << m_cols <<") matrix.";
        throw std::out_of_range(err.str());
    }

    return m_array[row-1][col-1];
}

// Functions to return an array containing a row or column vector with the elements in the argument's row or column.

std::vector<double> cppmat::Matrix::rowVector(int row) const {
    if (row < 1 || row > m_rows) {
        std::stringstream err;
        err << "Bad matrix row vector access:\n"
            << "attempted access to row " << row << " in matrix with " << m_rows << " rows.";
        throw std::out_of_range(err.str());
    }

    // Construct a vector, treating pointers to the start and end
    // of the array as input iterators.
    std::vector<double> rowVec(m_array[row-1], m_array[row-1] + m_cols);
    return rowVec;
}

std::vector<double> cppmat::Matrix::colVector(int col) const {
    if (col < 1 || col > m_cols) {
        std::stringstream err;
        err << "Bad matrix column vector access:\n"
            << "attempted access to column " << col << " in matrix with " << m_cols << " columns.";
        throw std::out_of_range(err.str());
    }

    std::vector<double> colVec(m_rows);

    // We can't use the easy pointer-as-iterator method for this,
    // since they're at different places in memory.
    for (int i = 0; i < m_rows; i++) {
        colVec[i] = m_array[i][col-1];
    }
    return colVec;
}

bool cppmat::Matrix::isSquare() const {
    return m_rows == m_cols;
}

// Returns the transpose of the matrix.
cppmat::Matrix cppmat::Matrix::transpose() const {
    auto* newArr = new double[m_rows * m_cols];
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            newArr[(j*m_rows) + i] = m_array[i][j];
        }
    }

    Matrix result(m_cols, m_rows, newArr);
    delete [] newArr;
    return result;
}

// Helper function for the recursive determinant function.
double cppmat::Matrix::detHelper(int size, int offset, double** array) {
    if (size == 2) {
        /*
         * Matrix of the form:
         * a b
         * c d ;
         * returns ad - bc
         */
        return ((array[offset][offset] * array[offset+1][offset+1])
              - (array[offset][offset+1] * array[offset+1][offset]));
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

// Returns the determinant of the matrix.
// NOTE: this function was basically an exercise in my recursive abilities;
// it is NOT efficient in any sense of the word,
// and should not be used for actual intensive calculation.
double cppmat::Matrix::determinant() {
    if (!isSquare()) {
        std::stringstream err;
        err << "Attempted determinant calculation of non-square matrix:\n"
            << "expected (n x n) matrix, received (" << m_rows << " x " << m_cols << ").";

        throw std::invalid_argument(err.str());
    }

    if (m_rows == 1) {
        return valueAt(1, 1);
    }

    return detHelper(m_rows, 0, m_array);
}

// Just an alias for determinant().
// Eventually I want to make it a separate function, i.e. cppmat::det(A).
double cppmat::Matrix::det() {
    return this->determinant();
}


////////////////
/// Mutators ///
////////////////

// Sets the value of the matrix at row 'row' and column 'col' to 'value'.
void cppmat::Matrix::insert(int row, int col, double value) {
    if (row > m_rows || row < 1 || col > m_cols || col < 1) {
        std::stringstream err;
        err << "Bad insertion to matrix:\n"
            << "invalid argument(s) in [row = " << row << ", col = " << col << "] to (" << m_rows << " x "
            << m_cols << ") matrix.";

        throw std::invalid_argument(err.str());
    }

    m_array[row - 1][col - 1] = value;
}

// Swaps two rows in a matrix. 'row1' and 'row2' are 1-INDEXED.
void cppmat::Matrix::swapRows(int row1, int row2) {
    if (row1 < 1 || row1 > m_rows || row2 < 1 || row2 > m_rows) {
        std::stringstream err;
        err << "Bad matrix row swap:\n"
            << "invalid argument(s) in  [row1 = " << row1 << ", row2 = " << row2 << "] to matrix with " << m_rows << " rows.";

        throw std::invalid_argument(err.str());
    }

    if (row1 == row2) {
        return;
    }

    double* tmp = m_array[row1 - 1];
    m_array[row1 - 1] = m_array[row2 - 1];
    m_array[row2 - 1] = tmp;
}
