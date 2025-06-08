#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdio.h>

#define MATRIX_ASSERT(expr, msg) \
    if (!(expr)) { \
        fprintf(stderr, "Assertion failed: %s\nFile: %s, Line: %d\nMessage: %s\n", \
            #expr, __FILE__, __LINE__, msg); \
        abort(); \
    }

#define MATRIX_AT(matrix, row, col) ((matrix).elems[(row) * (matrix).num_cols + (col)])

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
    size_t num_rows;
    size_t num_cols;
    float *elems;
} matrix_t;

matrix_t create_matrix(size_t num_rows, size_t num_cols, float *elems);
matrix_t create_identity_matrix(size_t size);

matrix_t add_matrices(matrix_t lhs, matrix_t rhs);
matrix_t multiply_matrices(matrix_t lhs, matrix_t rhs);

void print_matrix(matrix_t matrix);
void destroy_matrix(matrix_t *matrix);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MATRIX_H