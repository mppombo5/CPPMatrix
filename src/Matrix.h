//
// Created by Matthew Pombo on 11/9/19.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

namespace CPPMat {
    class Matrix {
    public:
        // initialize a rows x cols matrix with all 0's
        Matrix(int rows, int cols);

        // initialize a rows x cols matrix according to a given 2D array or vector
        Matrix(int rows, int cols, double** matrixArray);

        // easier constructor using a single array of doubles
        Matrix(int rows, int cols, double* matrixarray);

        Matrix(const Matrix& src);
        ~Matrix();

        // Operators
        Matrix& operator=(const Matrix& src);
        double operator()(int row, int col) const;
        Matrix& operator*(const Matrix& m) const;
        Matrix& operator+(const Matrix& m) const;
        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const;

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
}




inline
double CPPMat::Matrix::operator()(int row, int col) const {
    return this->valueAt(row, col);
}

inline
int CPPMat::Matrix::rows() const {
    return m_rows;
}

inline
int CPPMat::Matrix::cols() const {
    return m_cols;
}

inline
bool CPPMat::Matrix::isSquare() const {
    return m_rows == m_cols;
}

// det(A) is just an alias for determinant(A)
inline
double CPPMat::Matrix::det() {
    return this->determinant();

}

inline
bool CPPMat::Matrix::operator!=(const Matrix& m) const {
    return !operator==(m);
}


#endif //MATRIX_MATRIX_H
