#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(){ 
   printf(" Matrix Example.\n\r");
   
   //Creation empty matrix
   matrix_float* matrix0 = create_empty_float_matrix( 3, 2 );
   
   //Creation examples
   matrix_float* matrix1 = create_example_matrix( 3 );
   matrix_float* matrix2 = create_identity_matrix( 3 );
  
   //Sum and product
   matrix_float* matrix3 = sum_matrices( matrix1, matrix2 );
   matrix_float* matrix4 = product_matrices( matrix1, matrix1 );
   
   //Transpose
   matrix_float* matrix1_transpose = transpose_matrix( matrix1 );
   
   //Inverse
   matrix_float* matrix_invertible = create_empty_float_matrix( 2, 2 );
   matrix_invertible->p_matrix[0][0] = 2;
   matrix_invertible->p_matrix[0][1] = 7;
   matrix_invertible->p_matrix[1][0] = 2;
   matrix_invertible->p_matrix[1][1] = 8;
   matrix_float* matrix_invertible_inverse = inverse_matrix( matrix_invertible );
  
  
   printf( "Empty matrixx.\r\n" );
   print_matrix( matrix0 );

   printf( "Identity matrix.\r\n" );
   print_matrix( matrix2 );
   
   printf( "Sum and multiplication matrices.\r\n" );
   print_matrix( matrix3 );
   print_matrix( matrix4 );
   
     
   printf( "Matrix1 with transpose.\r\n" );
   print_matrix( matrix1 );
   print_matrix( matrix1_transpose );
   
   printf( "Invertible Matrix with inverse.\r\n" );
   print_matrix( matrix_invertible );
   print_matrix( matrix_invertible_inverse );
   print_matrix( product_matrices( matrix_invertible, matrix_invertible_inverse ) );
   
   
   free_matrix_float( matrix0 );
   free_matrix_float( matrix1 );
   free_matrix_float( matrix1_transpose );
   free_matrix_float( matrix2 );
   free_matrix_float( matrix3 );
   free_matrix_float( matrix4 );
   
   
   free_matrix_float( matrix_invertible );
   free_matrix_float( matrix_invertible_inverse );
  
   return 0; 
}
