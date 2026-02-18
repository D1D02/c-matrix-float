#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

#define EPSILON 1e-9

#define GET_ELEMENT(m, r, c) ((m)->p_matrix[ (r) * (m)->cols + (c) ])

typedef float matrix_type;

typedef struct MatrixFloatStruct{
   unsigned short int rows;
   unsigned short int cols;
   matrix_type * p_matrix;
}matrix;



typedef void ( *MatrixBasicOperation ) ( matrix *, unsigned short int , unsigned short int );
typedef void ( *MatricesBasicOperation ) ( matrix_type *, const matrix *, const matrix *, unsigned short int , unsigned short int );


/* <-------------------------------------------------------- Matrix Creation --------------------------------------------------------> */
matrix* create_empty_matrix( unsigned short int rows, unsigned short int cols );
matrix* create_example_matrix( unsigned short int );
matrix* create_identity_matrix( unsigned short ints );

/* <-------------------------------------------------------- Matrix Operations --------------------------------------------------------> */
matrix* difference_matrices( matrix *, matrix * );
matrix* product_matrices( matrix *, matrix * );
matrix* sum_matrices( matrix *, matrix * );
matrix* transpose_matrix( matrix * );
matrix* inverse_matrix( matrix * );

/* <-------------------------------------------------------- Matrix Operations Implementation --------------------------------------------------------> */
void difference_matrices_elements( matrix_type *, const matrix *, const matrix *, unsigned short int , unsigned short int );
void insert_example_matrix_elements( matrix *, unsigned short int , unsigned short int );
void insert_zero_matrix_elements( matrix *, unsigned short int, unsigned short int );
void print_matrix_elements( matrix *, unsigned short int, unsigned short int );
void product_matrices_elements( matrix_type *, const matrix *, const matrix *, unsigned short int, unsigned short int );
void sum_matrices_elements( matrix_type *, const matrix *, const matrix *, unsigned short int, unsigned short int );
matrix* sum_difference_matrices( matrix *, matrix *, MatricesBasicOperation );

/* <-------------------------------------------------------- Utility --------------------------------------------------------> */
void print_matrix( matrix * );
float* create_simple_matrix( unsigned short int, unsigned short int );
void free_simple_matrix( matrix_type * );
void free_matrix( matrix * );

/* <-------------------------------------------------------- Matrix Loop Functions --------------------------------------------------------> */
void basic_double_loop_matrices( matrix *, const matrix *, const matrix *, MatricesBasicOperation );
void basic_double_loop_matrix( matrix *, MatrixBasicOperation );

#endif
