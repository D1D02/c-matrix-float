#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

typedef struct MatrixFloatStruct{
   unsigned short int rows;
   unsigned short int cols;
   float** p_matrix;
}matrix_float;


matrix_float* create_empty_float_matrix( unsigned short int rows, unsigned short int cols );
matrix_float* create_example_matrix( unsigned short int );

void print_matrix( matrix_float * );


#endif
