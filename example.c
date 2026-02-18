#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(){ 
   printf(" Matrix Example.\n\r");
   
   //Creation empty matrix
   matrix* matrix0 = create_empty_matrix( 3, 2 );
   
   //Creation examples
   matrix* matrix1 = create_example_matrix( 3 );
   matrix* matrix2 = create_identity_matrix( 3 );
  
   //Sum and product
   matrix* matrix3 = sum_matrices( matrix1, matrix2 );
   matrix* matrix4 = product_matrices( matrix1, matrix1 );
   
   //Transpose
   matrix* matrix1_transpose = transpose_matrix( matrix1 );
   
   matrix * matrix5 = create_empty_matrix( 2, 3 );
   GET_ELEMENT( matrix5, 0, 0 ) = 1;
   GET_ELEMENT( matrix5, 1, 2 ) = 1;
   matrix* matrix5_transpose = transpose_matrix( matrix5 );
   
   //Inverse
   matrix* matrix_invertible = create_empty_matrix( 2, 2 );
   GET_ELEMENT( matrix_invertible, 0, 0 ) = 2;
   GET_ELEMENT( matrix_invertible, 0, 1 ) = 7;
   GET_ELEMENT( matrix_invertible, 1, 0 ) = 2;
   GET_ELEMENT( matrix_invertible, 1, 1 ) = 8;
   matrix* matrix_invertible_inverse = inverse_matrix( matrix_invertible );
  
  
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
   
   
   printf( "Matrix5 with transpose.\r\n" );
   print_matrix( matrix5 );
   print_matrix( matrix5_transpose );
   
   
   printf( "Invertible Matrix with inverse.\r\n" );
   print_matrix( matrix_invertible );
   print_matrix( matrix_invertible_inverse );
   print_matrix( product_matrices( matrix_invertible, matrix_invertible_inverse ) );
   
   printf(" Sum and Difference between matrix1 and matrix2.\r\n" );
   print_matrix( sum_matrices( matrix1, matrix2 ) );
   print_matrix( difference_matrices( matrix1, matrix2 ) );
   
   free_matrix( matrix0 );
   free_matrix( matrix1 );
   free_matrix( matrix1_transpose );
   free_matrix( matrix2 );
   free_matrix( matrix3 );
   free_matrix( matrix4 );
   free_matrix( matrix5 );
   free_matrix( matrix5_transpose );
   
   
   free_matrix( matrix_invertible );
   free_matrix( matrix_invertible_inverse );
  
   return 0; 
}
