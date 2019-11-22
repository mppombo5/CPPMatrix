//
// Created by Matthew Pombo on 11/9/19.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
public:
    // initialize a rows x cols matrix with all 0's
    Matrix(int rows, int cols);
    // initialize a rows x cols matrix according to a given 2D array or vector
    Matrix(int rows, int cols, double** matrixArray);
    Matrix& operator=(const Matrix& src);
    Matrix(const Matrix& src);
    ~Matrix();

    // Operators
    double operator()(int row, int col) const;
    Matrix& operator*(const Matrix& m) const;

    // Accessors
    int rows() const;
    int cols() const;
<<<<<<< HEAD
    double valueAt(int row, int col) const;
    double determinant(const Matrix& A) const;
    double det(const Matrix& A) const;
    double* rowVector(int row) const;
    double* colVector(int col) const;
=======
    double valueAt(int row, int col) const;
    double* rowVector(int row) const;
    double* colVector(int col) const;
>>>>>>> master
    bool isSquare() const;
    void print() const;
    Matrix& transpose() const;

    // Mutators
    bool insert(int row, int col, double value);

private:
    int m_rows;
    int m_cols;
    double** m_array;
};


inline
double Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
}

inline
int Matrix::rows() const {
    return m_rows;
}

inline
int Matrix::cols() const {
    return m_cols;
}

inline
bool Matrix::isSquare() const {
    return m_rows == m_cols;
}

// det(A) is just an alias for determinant(A)
inline
<<<<<<< HEAD
double Matrix::det(const Matrix& A) const {
    return determinant(A);
=======
double Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
>>>>>>> master
}


#endif //MATRIX_MATRIX_H
