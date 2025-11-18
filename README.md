# **Matrix Float C Library**

A simple c float library to create and manipulate matrices, with functions that are intended to be used on microcontroller ( but it is not excluded to be used in other ways ). 

I'm a computer science student and I'm developing this to help me in my project, but I want to maintain this library as long is necessary: so feel free, to issue and propose or to report errors.

> [!NOTE]
> This is a student project and is maintained only by the creator himself.

> [!WARNING]
> This library could have problems that are not resolved: in that case, open an issue if it's not already opened.


## Testing

For testing purpose, you can find an example.c file where you can test the library: you will find examples for commands. If you are on linux, you can just use this command to build the code:
```
make
```
And for running the example code, after launching the make command, you just need to send this command:
```
./example
```


## Functions 

In this section you will find all the functions that are implemented on the branch main, with a small explanation.

### Creation
- **create_empty_float_matrix**, a function that create a matrix from 2 unsigned short int, rows and columns, and return a zero matrix_float (a matrix_float initialized with all zeros).
- **create_example_matrix**, a function that create a matrix from a 1 unsigned short int, representing rank, and return a matrix_float with incremental value starting from the first cell.
- **create_identity_matrix**, a function that takes a number, rank, and create a squared matrix with 1 on diagonal.

### Operations
- **difference_matrices**, a function that takes two not null matrix_float with same dimensions, same number of rows and cols, and return a matrix_float that is the difference of the 2 matrices.
- **inverse_matrix**, a function that takes a not null matrix_float with same dimensions, same number of rows and cols, and return a matrix_float that is the inverse of the given matrix.  (Gauss-Jordan)
- **sum_matrices**, a function that takes two not null matrix_float with same dimensions, same number of rows and cols, and return a matrix_float that is the sum of the 2 matrices.
- **product_matrices**, a function that takes in input 2 not null matrix_float, with cols of the first matrix equal to the rows of the second, and return a matrix_float that is the multiplication of the 2 matrices.
- **transpose_matrix**, a function that takes a not null matrix_float and return a matrix_float that is the transpose of the given matrix.


### Utility
- **create_simple_float_matrix**, a function that takes in input 2 numbers, rows and columns, and return a simple float matrix.
- **free_matrix_float**, a function that takes in input a matrix_float and deallocate the memory.
- **free_simple_float_matrix**, a function that takes in input a simple float matrix and number of rows and deallocate the memory.
- **print_matrix**, a function that takes in input a not null matrix_float and print it on the standart output.
