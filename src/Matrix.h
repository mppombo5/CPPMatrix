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
    double valueAt(int row, int col) const;
    double* rowVector(int row) const;
    double* colVector(int col) const;
    bool isSquare() const;
    void print() const;
    Matrix& transpose() const;

    double determinant();
    double det();

    // Mutators
    bool insert(int row, int col, double value);
    bool swapRows(int row1, int row2);

private:
    int m_rows;
    int m_cols;
    double** m_array;

    double detHelper(int size, int offset, double** array);
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
double Matrix::det() {
    return this->determinant();

}


#endif //MATRIX_MATRIX_H
