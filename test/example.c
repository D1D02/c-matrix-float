#include <matrix.h>

int main(){ 
    printf("Matrix Example.\n");

    float elems1[] = {
        1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f,
        7.0f, 8.0f, 9.0f
    };

    matrix_t m1 = create_matrix(3, 3, elems1);
    matrix_t m2 = create_identity_matrix(3);
    matrix_t m3 = add_matrices(m1, m2);
    matrix_t m4 = multiply_matrices(m1, m2);

    print_matrix(m1); printf("\n");
    print_matrix(m2); printf("\n");
    print_matrix(m3); printf("\n");   
    print_matrix(m4); printf("\n");
   
    destroy_matrix(&m1);
    destroy_matrix(&m2);    
    destroy_matrix(&m3);
    destroy_matrix(&m4); 
}
