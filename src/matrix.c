#include "matrix.h"
#include <assert.h>
#include <stdlib.h>

matrix_t create_matrix(size_t num_rows, size_t num_cols, float *elems) {
    matrix_t matrix;

    matrix.num_rows = num_rows;
    matrix.num_cols = num_cols;
    matrix.elems = (float *)malloc(num_rows * num_cols * sizeof(float));

    MATRIX_ASSERT(matrix.elems != NULL, "Matrix allocation failed");
    
    for (size_t i = 0; i < num_rows * num_cols; i++) {
        matrix.elems[i] = elems[i];
    }
    
    return matrix;
}

matrix_t create_identity_matrix(size_t size) {
    matrix_t matrix;

    matrix.num_rows = size;
    matrix.num_cols = size; 
    matrix.elems = (float *)malloc(size * size * sizeof(float));
    
    MATRIX_ASSERT(matrix.elems != NULL, "Matrix allocation failed");

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            MATRIX_AT(matrix, i, j) = (i == j) ? 1.0f : 0.0f;
        }
    }

    return matrix;
}

matrix_t add_matrices(matrix_t lhs, matrix_t rhs) {
    MATRIX_ASSERT(lhs.num_rows == rhs.num_rows && lhs.num_cols == rhs.num_cols, 
        "Matrix dimensions do not match for addition");

    matrix_t ret;

    ret.num_rows = lhs.num_rows;
    ret.num_cols = lhs.num_cols;
    ret.elems = (float *)malloc(ret.num_rows * ret.num_cols * sizeof(float));

    MATRIX_ASSERT(ret.elems != NULL, "Matrix allocation failed");
    
    for (size_t i = 0; i < ret.num_rows * ret.num_cols; i++) {
        ret.elems[i] = lhs.elems[i] + rhs.elems[i];
    }

    return ret;
}

matrix_t multiply_matrices(matrix_t lhs, matrix_t rhs) {
    MATRIX_ASSERT(lhs.num_cols == rhs.num_rows, "Matrix dimensions do not match for multiplication");

    matrix_t ret;

    ret.num_rows = lhs.num_rows;
    ret.num_cols = rhs.num_cols;
    ret.elems = (float *)malloc(ret.num_rows * ret.num_cols * sizeof(float));

    MATRIX_ASSERT(ret.elems != NULL, "Matrix allocation failed");
    
    for (size_t i = 0; i < ret.num_rows; i++) {
        for (size_t j = 0; j < ret.num_cols; j++) {
            MATRIX_AT(ret, i, j) = 0.0f;
            for (size_t k = 0; k < lhs.num_cols; k++) {
                MATRIX_AT(ret, i, j) += MATRIX_AT(lhs, i, k) * MATRIX_AT(rhs, k, j);
            }
        }
    }

    return ret;
}

void print_matrix(matrix_t matrix) {
    MATRIX_ASSERT(matrix.elems != NULL, "Cannot print an uninitialized matrix");

    for (size_t i = 0; i < matrix.num_rows; i++) {
        for (size_t j = 0; j < matrix.num_cols; j++) {
            printf("%f ", MATRIX_AT(matrix, i, j));
        }
        printf("\n");
    }
}

void destroy_matrix(matrix_t *matrix) {
    if (matrix != NULL && matrix->elems != NULL) {
        free(matrix->elems);
        matrix->elems = NULL;

        matrix->num_rows = 0;
        matrix->num_cols = 0;
    }
}