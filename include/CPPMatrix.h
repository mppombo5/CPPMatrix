//
// Created by Matthew Pombo on 12/27/19.
//

#ifndef CPPMATRIX_CPPMATRIX_H
#define CPPMATRIX_CPPMATRIX_H

// needed to forward-declare ostream for << operator
#include <iosfwd>

namespace cppmat {
    class Matrix;
}

// must forward-declare friend functions
cppmat::Matrix operator* (const cppmat::Matrix& A, const cppmat::Matrix& B);
cppmat::Matrix operator* (double d, const cppmat::Matrix& A);
cppmat::Matrix operator* (const cppmat::Matrix& A, double d);
cppmat::Matrix operator+ (const cppmat::Matrix& A, const cppmat::Matrix& B);
cppmat::Matrix operator- (const cppmat::Matrix& A, const cppmat::Matrix& B);

std::ostream&  operator<<(std::ostream& os, const cppmat::Matrix& A);

namespace cppmat {

class Matrix {
public:
    // initialize a rows x cols matrix with all 0's
    Matrix(int rows, int cols);

    // initialize a rows x cols matrix according to a given 2D array or vector
    Matrix(int rows, int cols, double** matrixArray);

    // easier constructor using a single array of doubles
    Matrix(int rows, int cols, const double* matrixArray);

    // Copy constructor.
    Matrix(const Matrix& src);

    // Copy assignment operator.
    Matrix& operator=(const Matrix& src);

    // Move constructor.
    Matrix(Matrix&& src) noexcept;

    // Move assignment operator.
    Matrix& operator=(Matrix&& src) noexcept;

    // Destructor.
    ~Matrix();


    // Operators
    Matrix& operator*=(const Matrix& B);
    Matrix& operator*=(double d);
    Matrix& operator+=(const Matrix& B);
    Matrix& operator-=(const Matrix& B);
    bool    operator==(const Matrix& m) const;
    bool    operator!=(const Matrix& m) const;
    double  operator()(int row, int col) const;

    // wack syntax for friend functions
    friend Matrix (::operator*(const Matrix& A, const Matrix& B));
    friend Matrix (::operator*(double d,        const Matrix& A));
    friend Matrix (::operator*(const Matrix& A, double d));
    friend Matrix (::operator+(const Matrix& A, const Matrix& B));
    friend Matrix (::operator-(const Matrix& A, const Matrix& B));

    friend std::ostream& (::operator<<(std::ostream& os, const Matrix& A));


    // Accessors
    int rows() const;
    int cols() const;
    double valueAt(int row, int col) const;
    std::vector<double> rowVector(int row) const;
    std::vector<double> colVector(int col) const;
    bool isSquare() const;
    void print() const;
    Matrix transpose() const;

    double determinant();
    double det();


    // Mutators
    void insert(int row, int col, double value);
    void swapRows(int row1, int row2);

private:
    int m_rows;
    int m_cols;
    double** m_array;

    double detHelper(int size, int offset, double** array);
}; // class Matrix

} // namespace cppmat

#endif //CPPMATRIX_CPPMATRIX_H
