# The Determinant Function

The determinant function was an enough of an undertaking that I figured it warrants its own documentation page.

## Recursive Hell

The first thing you might notice upon looking at the code for the `determinant()` function is that it uses a recursive helper function. I am well aware of the method of finding determinants by row-reducing to an upper-triangular matrix and multiplying the diagonal entries, but more than anything I wanted to challenge myself to see if I could implement it the way us humans find it, by finding the determinants of successively smaller submatrices. If this library somehow gains popularity and people actually start caring about the efficiency of its member functions, I will certainly change it to use the row-reducing method.

Figuring out how to ignore the rows as necessary as we take successively smaller submatrices was the biggest challenge to overcome. I went through several other ideas that were either far less efficient or simply didn't work; two such ideas were maintaining a hash table of rows to ignore and organizing all the rows and reorganizing them at the beginning and end of each iteration of the for loop.

My breakthrough came when I realized that only one swap was needed in each iteration; if I were to swap the currently ignored row with the row at the top, then the rows would all fall into place such that the top row was ignored and the other rows were still in increasing order, so the minor of that submatrix could be performed all within those rows, without needing to keep track of any rows to ignore.

With this system in place, all I needed was one call to swap the rows at the beginning of each for loop and one while loop afterwards to bring the top row all the way back down to the bottom.

## Reference

For more documentation, feel free to consult the [reference](README.md#reference).
