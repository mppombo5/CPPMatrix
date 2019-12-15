# Basic Implementation of the Matrix class

## Data Members

The basic Matrix class has only three data members:  two `int`'s for the number of rows and columns in the matrix, and a `double**` that represents the actual elements within the matrix.

## Actual Representation of the Matrix's Elements

I opted to represent the elements with a multi-level array of doubles. The main reason for this is for ease of swapping rows. There are many instances when we have to swap rows in manipulating matrices; for example, in finding the determinant we have to swap which row to ignore at the top so that we have the correct submatrix to find the minor.

Another instance is swapping rows for finding the Reduced Row-Echelon Form of a matrix (when I get around to implementing it), so we can swap rows such that there are always leading 0s.  Swapping elements in an array of pointers to doubles is infinitely cheaper than swapping around all the elements in-place, so it seemed like the natural decision to make.

## Reference

For more documentation, feel free to consult the [reference](README.md#reference).
