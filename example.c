#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(){ 
   printf(" Matrix Example.\n\r");
   
   matrix_float* matrix = create_example_matrix( 3 );
  
  print_matrix( matrix );
  
   return 0; 
}
