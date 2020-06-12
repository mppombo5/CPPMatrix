# Accessing a Matrix <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Characteristics of a Matrix](#characteristics-of-a-matrix)
- [Getting Values from a Matrix](#getting-values-from-a-matrix)
- [Taking the Transpose of a Matrix](#taking-the-transpose-of-a-matrix)
- [Printing out a Matrix](#printing-out-a-matrix)
- [Further Reading](#further-reading)

## Characteristics of a Matrix

1. ```C++
   int rows() const;
   int cols() const;
   ```

   Return the number of rows and columns in a matrix, respectively.

2. ```C++
   bool isSquare() const;
   ```

   Returns true only if the number of rows in a matrix equals the number of columns.

3. ```C++
   double determinant();
   double det();
   ```

   Return the determinant of a square matrix. If the matrix is not square, then the function returns 0 and a diagnostic message is written to standard error.  
   NOTE: the determinant function is NOT thread-safe. The matrix is ultimately returned unchanged, but the implementation swaps things around as it goes.

## Getting Values from a Matrix

1. ```C++
   double valueAt(int row, int col) const;
   // or, equivalently for an existing matrix A:
   A(int row, int col)
   ```

   These two member functions will return the value of the element at row `row`, column `col`. The access is **1-indexed**, so `A(1,1)` or `A.valueAt(1,1)` will return the value in the first row and first column.

   If `row` or `col` is less than 1 or greater than the dimensions of the matrix, the function returns 0 and a diagnostic message is written to standard error.

2. ```C++
   double* rowVector(int row) const;
   double* colVector(int col) const;
   ```

   These two member functions return a pointer to an array of doubles that is equivalent to the row or column vector at row `row` or column `col`. If either argument is less than 1 or greater than the number of rows or columns in the matrix, the function returns `nullptr` and a diagnostic message is written to standard error.

   Again, this access is 1-indexed, so `A.rowVector(1)` will give a row vector corresponding to the first row.  
   The array is a copy of the matrix's vectors; this does not return a direct pointer to the matrix itself.

## Taking the Transpose of a Matrix

You can also take the transpose of a matrix:

```C++
cppmat::Matrix& transpose() const;
```

This will return a new matrix whose column vectors are equal to the original matrix's row vectors.

## Printing out a Matrix

If you ever need to print out a rough visual representation of your matrix, you can do so with the member function

```C++
void print() const;
```

This will print out each row of the matrix to standard output, with each value separated by a single `\t` tab character.

## Further Reading

Feel free to consult the [reference](README.md) for more on how to use your matrix.
