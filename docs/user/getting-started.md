# Getting Started <!-- omit in toc -->

## Table of Contents <!-- omit in toc -->

- [Basics of a Matrix](#basics-of-a-matrix)
- [Declaration/Usage](#declarationusage)
- [Next Steps](#next-steps)

## Basics of a Matrix

A matrix is simply a two-dimensional table of numbers. By convention, an "m x n" matrix is a matrix with m rows and n columns. This implementation stores doubles as its values, so as to allow for more precise solutions to given tasks.

Matrices are an immensely powerful object in the world of mathematics, and there are many ways in which they can be used and manipulated. Among the many uses, a few examples are:

- solving systems of linear equations
- calculating a linear transformation
- solving differential equations
- data fitting

and many more. The goal of this library is to provide you with an easy way to perform many of these manipulations and calculations in C++.

## Declaration/Usage

The Matrix class has two main constructors:

1. ```C++
   Matrix A(int rows, int cols);
   ```

    This is the most basic initialization of a matrix. It will create a matrix with the given number of rows and columns; upon declaration, all entries in the matrix will be 0.

    If `rows` or `cols` is less than 0, the matrix is initialized with **both** fields set to 1. This is to avoid incorrect calculations that might still be valid if one of the fields were set to its intended value.

2. ```C++
   Matrix A(int rows, int cols, double** array);
   ```

    This constructor allows you to initialize a matrix with the values that you want it to have. In addition to specifying the number of rows and columns, you can also pass in a 2-dimensional array of doubles to represent what the matrix's entries will look like. Each array of doubles acts as a row, and every entry in those array act as a column entry in that row.

    If `double** array` does not have the same number of rows and columns as `rows` and `cols`, then the subsequent behavior of your program is undefined.

In addition to these two basic constructors, the Matrix class also supports copy and assignment construction:

```C++
// copy construction according to existing Matrix A:
Matrix B = A;
Matrix C(A);

// assignment of existing Matrix D to A:
D = A;
```

## Next Steps

Now that you can declare and initialize a matrix, feel free to consult the [reference](README.md) for more on how to use it!
