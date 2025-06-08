# **Matrix Float C Library**

A simple C float library to create and manipulate matrices, with functions that are intended to be used on 
microcontroller (but it is not excluded to be used in other ways). 

I'm a computer science student and I'm developing this to help me in my project, but I want to maintain this 
library as long is necessary: so feel free, to issue and propose or to report errors.

> [!NOTE]
> This is a student project and is maintained only by the creator himself.

> [!WARNING]
> This library could have problems that are not resolved: in that case, open an issue if it's not already opened.


## Testing

For testing purpose, you can find an example.c file where you can test the library: you will find examples for commands. 
Make sure you have installed CMake on your platform. 
To build this project, create a build directory and move into it:
```
cd build
```
Then, prompt the following commands:
```
cmake ..
cmake --build .
```
Finally, find the example.exe in your build directory and run it (the position of the example executable depends 
on your operating system).


## Functions 

In this section you will find all the functions that are implemented on the branch main, with a small explanation.

### Creation
- **create_matrix**: creates a matrix with the specified numbers of rows, columns and elements.
- **create_identity_matrix**: creates an identity matrix of the specified order.
> [!WARNING]
> All matrices should be destroyed with **destroy_matrix**.


### Operations
- **add_matrices**: takes 2 not null matrices with same dimensions, same number of rows and cols, and returns a matrix that is the sum of the 2 matrices
- **multiply_matrices**: takes 2 not null matrices, with number of columns of the first matrix equal to the number of rows of the second one, and returns a matrix_float that is the product of the 2 matrices

### Utility
- **print_matrix**: prints the specified matrix.

## TO-DO
- Implement other operations (subtraction, product for a scalar, transpose, etc.).
- Implement operations on raw pointers rather than on matrix objects (to improve performance).

## Releases
- v0.2: (francespos's contribution) Code refactoring. Matrices elements are stored in a single rather than a double 
pointer to improve performance (memory allocated contiguously). Matrices are passed by value rather than by reference (again, to improve performance, because matrix objects are very small). Using CMake instead of Makefile (for portability).
- v0.1: Original Release  