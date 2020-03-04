//
// Created by Matthew Pombo on 12/27/19.
//

#ifndef CPPMATRIX_CPPMATRIX_H
#define CPPMATRIX_CPPMATRIX_H

namespace CPPMat {
    class Matrix;
}

// must forward-declare friend functions
CPPMat::Matrix  operator* (const CPPMat::Matrix& A, const CPPMat::Matrix& B);
CPPMat::Matrix  operator* (double d, const CPPMat::Matrix& A);
CPPMat::Matrix  operator* (const CPPMat::Matrix& A, double d);

namespace CPPMat {

    class Matrix {
    public:
        // initialize a rows x cols matrix with all 0's
        Matrix(int rows, int cols);

        // initialize a rows x cols matrix according to a given 2D array or vector
        Matrix(int rows, int cols, double** matrixArray);

        // easier constructor using a single array of doubles
        Matrix(int rows, int cols, const double* matrixArray);

        Matrix(const Matrix& src);
        ~Matrix();


        // Operators
        Matrix& operator=(const Matrix& src);
        double operator()(int row, int col) const;
        Matrix& operator+(const Matrix& m) const;
        bool operator==(const Matrix& m) const;
        bool operator!=(const Matrix& m) const;

        // wack syntax for friend functions
        friend Matrix (::operator*(const Matrix& A, const Matrix& B));
        //Matrix& operator*=(const Matrix& B);
        friend Matrix (::operator*(double d, const Matrix& A));
        friend Matrix (::operator*(const Matrix& A, double d));


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
        void insert(int row, int col, double value);
        void swapRows(int row1, int row2);

    private:
        int m_rows;
        int m_cols;
        double** m_array;

        double detHelper(int size, int offset, double** array);
    };

}

#endif //CPPMATRIX_CPPMATRIX_H
