#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

#define EPSILON 0.000000001

typedef struct MatrixFloatStruct{
   unsigned short int rows;
   unsigned short int cols;
   float** p_matrix;
}matrix_float;


typedef void ( *MatrixBasicOperation ) ( matrix_float *, unsigned short int , unsigned short int );
typedef void ( *MatricesBasicOperation ) ( float *, const matrix_float *, const matrix_float *, unsigned short int , unsigned short int );


/* <-------------------------------------------------------- Matrix Creation --------------------------------------------------------> */
matrix_float* create_empty_float_matrix( unsigned short int rows, unsigned short int cols );
matrix_float* create_example_matrix( unsigned short int );
matrix_float* create_identity_matrix( unsigned short ints );

/* <-------------------------------------------------------- Matrix Operations --------------------------------------------------------> */
matrix_float* product_matrices( matrix_float *, matrix_float * );
matrix_float* sum_matrices( matrix_float *, matrix_float * );
matrix_float* transpose_matrix( matrix_float * );
matrix_float* inverse_matrix( matrix_float * );

/* <-------------------------------------------------------- Matrix Operations Implementation --------------------------------------------------------> */
void insert_example_matrix_elements( matrix_float *, unsigned short int , unsigned short int );
void insert_zero_matrix_elements( matrix_float *, unsigned short int, unsigned short int );
void print_matrix_elements( matrix_float *, unsigned short int, unsigned short int );
void product_matrices_elements( float *, const matrix_float *, const matrix_float *, unsigned short int, unsigned short int );
void sum_matrices_elements( float *, const matrix_float *, const matrix_float *, unsigned short int, unsigned short int );

/* <-------------------------------------------------------- Utility --------------------------------------------------------> */
void print_matrix( matrix_float * );
float** create_simple_float_matrix( unsigned short int, unsigned short int );
void free_simple_float_matrix( float ** matrix, unsigned short int rows);
void free_matrix_float( matrix_float * );

/* <-------------------------------------------------------- Matrix Loop Functions --------------------------------------------------------> */
void basic_double_loop_matrices( matrix_float *, const matrix_float *, const matrix_float *, MatricesBasicOperation );
void basic_double_loop_matrix( matrix_float *, MatrixBasicOperation );

#endif
