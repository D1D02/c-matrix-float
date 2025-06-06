#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(){ 
   printf(" Matrix Example.\n\r");
   
   matrix_float* matrix1 = create_example_matrix( 3 );
   matrix_float* matrix2 = create_identity_matrix( 3 );
  
   matrix_float* matrix3 = sum_matrices( matrix1, matrix2 );
   matrix_float* matrix4 = product_matrices( matrix1, matrix2 );
  
   print_matrix( matrix1 );
   print_matrix( matrix2 );
   print_matrix( matrix3 );
   print_matrix( matrix4 );
  
   return 0; 
}
