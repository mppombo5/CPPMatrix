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
    Matrix(int rows, int cols, int** matrixArray);
    Matrix& operator=(const Matrix& src);
    Matrix(const Matrix& src);
    ~Matrix();

    // Accessors
    int rows() const;
    int cols() const;
    bool isSquare() const;
    void print() const;
    int valueAt(int row, int col) const;
    int operator()(int row, int col) const;
    Matrix& transpose() const;

    // Mutators
    bool insert(int row, int col, int value);

private:
    int m_rows;
    int m_cols;
    int** m_array;
};


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

inline
int Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
}


#endif //MATRIX_MATRIX_H
