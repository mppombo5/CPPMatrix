//
// Created by Matthew Pombo on 12/27/19.
//

#ifndef CPPMATRIX_CPPMATRIX_H
#define CPPMATRIX_CPPMATRIX_H

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

#endif //CPPMATRIX_CPPMATRIX_H
