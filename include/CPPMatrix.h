//
// Created by Matthew Pombo on 12/27/19.
//

#ifndef CPPMATRIX_CPPMATRIX_H
#define CPPMATRIX_CPPMATRIX_H

// needed to forward-declare ostream for << operator
#include <iosfwd>

/// The main namespace for the CPPMatrix library.
namespace cppmat {

// Forward-declare for overload declarations.
class Matrix;

// Non-member operator overloads.
Matrix operator*(double d, const Matrix& A);
std::ostream& operator<<(std::ostream& lhs, const Matrix& rhs);

/// The main Matrix class.
/**
 * The Matrix class represents a 2-dimensional, numerical matrix. It supplies
 * several functions to perform calculations and manipulations on the matrix,
 * as well as overloaded operators that perform the logical, mathematical
 * equivalent of using those operators on a real matrix.
 *
 * @author Matthew Pombo
 */
class Matrix {
public:
    //////////////////
    // Constructors //
    //////////////////

    /// The most basic constructor for the Matrix class.
    /**
     * This constructor takes in integer values for the number of rows and
     * columns in the matrix to be constructed, and initializes every value to 0.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     */
    Matrix(int rows, int cols);

    /// Initializes matrix with values according to 2D array of doubles.
    /**
     * This constructor takes in the number of rows and columns in the matrix
     * to be constructed, and initializes the values in the matrix according to
     * the 2D array of doubles passed in as 'matrixArray'.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @param matrixArray A pointer to a 2D array of doubles with which to initialize the matrix.
     */
    Matrix(int rows, int cols, double** matrixArray);

    /// Initializes matrix with values according to a 1D array of doubles.
    /**
     * This constructor takes in the number of rows and columns in the matrix
     * to be constructed, and initializes values according to the 1D array of
     * doubles 'matrixArray'. The constructor automatically separates the values
     * in 'matrixArray' and populates the rows and columns appropriately. This
     * method of initialization should be preferred over the 2D array of doubles
     * when possible: (1) for the sake of convenience, and (2) this constructor
     * treats the array as const.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @param matrixArray A pointer to a 1D array of doubles with which to initialize the matrix.
     */
    Matrix(int rows, int cols, const double* matrixArray);

    /// Matrix copy constructor.
    /**
     * A standard copy constructor for the Matrix class; creates a deep copy
     * of 'src' by manually copying over all values from its internal array
     * of doubles.
     *
     * @param src The lvalue Matrix instance to be copied.
     */
    Matrix(const Matrix& src);

    /// Matrix move constructor.
    /**
     * A standard move constructor for the Matrix class, adhering to the
     * conventions set by the C++11 standard. Claims ownership of the data
     * members in 'src', and sets all dynamically allocated memory in
     * 'src' to nullptr.
     *
     * @param src The rvalue Matrix instance from which to construct the lvalue.
     */
    Matrix(Matrix&& src) noexcept;

    /// Matrix copy-assignment operator.
    /**
     * Frees all allocated memory held by the Matrix instance and performs a
     * deep copy of data members in 'src'.
     *
     * @param src Matrix instance to be copied.
     * @return A deep copy of 'src'.
     */
    Matrix& operator=(const Matrix& src);

    /// Matrix move-assignment operator.
    /**
     * Frees all dynamically allocated memory in the current Matrix instance,
     * claims ownership of all data members owned by the rvalue 'src', and
     * sets all memory previously owned by 'src' to nullptr.
     *
     * @param src The rvalue Matrix instance from which to assign this Matrix instance.
     * @return A Matrix instance with the data members previously owned by 'src'.
     */
    Matrix& operator=(Matrix&& src) noexcept;

    /// Basic destructor which frees all allocated memory.
    ~Matrix();


    ///////////////
    // Operators //
    ///////////////

    /// The result of multiplying two matrices together.
    /**
     * This overloaded multiplication operator returns a new matrix. This new
     * matrix is mathematical result of multiplying the two matrix operands
     * together.
     *
     * @param rhs The matrix by which to multiply the left hand side.
     * @return The result of multiplying the two operands.
     */
    Matrix operator*(const Matrix& rhs) const;
    
    Matrix& operator*=(const Matrix& B);
    Matrix operator*(double d) const;
    Matrix& operator*=(double d);
    Matrix operator+(const Matrix& rhs) const;
    Matrix& operator+=(const Matrix& B);
    Matrix operator-(const Matrix& rhs) const;
    Matrix& operator-=(const Matrix& B);
    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
    double operator()(int row, int col) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& rhs);


    ///////////////
    // Accessors //
    ///////////////

    /// Returns the number of rows in the matrix.
    /**
     * @return The number of rows in this matrix instance.
     */
    int rows() const;

    /// Returns the number of columns in the matrix.
    /**
     * @return The number of columns in this matrix instance.
     */
    int cols() const;

    /// Returns the value of an element in the matrix.
    /**
     * Returns the element in the matrix at row 'row', column 'col'.
     * NOTE: the row and column arguments are *1-INDEXED*. This means that if
     * you want the value in the 2nd row and 3rd column, you would call
     * valueAt(2, 3); NOT valueAt(1, 2).
     *
     * @param row The 1-indexed row in which the value is located.
     * @param col The 1-indexed column in which the value is located.
     * @return The value in this matrix instance at row 'row', column 'col'.
     */
    double valueAt(int row, int col) const;

    /// Returns a copy of a row in the matrix.
    /**
     * Constructs a vector of doubles with the same elements as in the row
     * 'row' in the matrix.
     * NOTE: the row argument is *1-INDEXED*.
     *
     * @param row The 1-indexed row from which to copy values.
     * @return A copy of the 'row'th row in the matrix, as a std::vector of doubles.
     */
    std::vector<double> rowVector(int row) const;

    /// Returns a copy of a column in the matrix.
    /**
     * Constructs a vector of doubles with the same elements as in the column
     * 'col' in the matrix.
     * NOTE: the column argument is *1-INDEXED*.
     *
     * @param col The 1-indexed column from which to copy values.
     * @return A copy of the 'col'th column in the matrix, as a std::vector of doubles.
     */
    std::vector<double> colVector(int col) const;

    /// Determine whether the matrix is square.
    /**
     * @return Whether or not the matrix has as many rows as it has columns.
     */
    bool isSquare() const;

    /// Print a text representation of the matrix.
    /**
     * Prints each element of the matrix to standard output. Each element is
     * separated by a tab literal; therefore, the visual representation is
     * not guaranteed to align perfectly in the case of long numbers.
     */
    void print() const;

    /// Get the transpose of the matrix.
    /**
     * @return The transpose of this matrix. That is, the matrix formed by
     * turning each of its constituent rows into its constituent columns.
     */
    Matrix transpose() const;

    /// Get the determinant of the matrix.
    /**
     * @return The determinant of the matrix. NOTE: the current implementation
     * uses recursion instead of the faster row-reducing method. It is not
     * recommended to use this function for actual, time-sensitive
     * calculations.
     */
    double determinant();

    /// An alias for determinant().
    /**
     * @sa Matrix::determinant()
     */
    double det();


    //////////////
    // Mutators //
    //////////////

    /// Change an element in the matrix.
    /**
     * This function takes in the row and column of the element to change,
     * and sets it to the value of the third argument.
     * NOTE: the row and column arguments are *1-INDEXED*.
     *
     * @param row The 1-indexed row of the element you wish to change.
     * @param col The 1-indexed column of the element you wish to change.
     * @param value The value to set the element to.
     */
    void insert(int row, int col, double value);

    /// Swap two rows in the matrix.
    /**
     * This function takes in two, *1-indexed* row indices, and swaps the
     * elements within the two rows.
     *
     * @param row1 The first row to swap.
     * @param row2 The second row to swap.
     */
    void swapRows(int row1, int row2);

private:
    int m_rows;
    int m_cols;
    double** m_array;

    double detHelper(int size, int offset, double** array);
}; // class Matrix

} // namespace cppmat

#endif //CPPMATRIX_CPPMATRIX_H
