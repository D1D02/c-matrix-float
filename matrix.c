#include "matrix.h"

matrix_float* create_empty_float_matrix( unsigned short int rows, unsigned short int cols )
{
   
   matrix_float * matrix = ( matrix_float * ) malloc ( sizeof( matrix_float ) );
   float ** p_matrix = ( float ** ) malloc( rows * sizeof( float * ) );
   
   if( p_matrix == NULL || matrix == NULL )
   	return NULL;
   
   for( unsigned short int i = 0; i < rows; i++ )
   {
   	
   	p_matrix[i] = ( float * ) malloc( cols * sizeof( float * ) );
   	
   	if( p_matrix[i] == NULL )
   	{
   	   
   	   for( unsigned short int k = 0; k < i; k++ ) 
   	   {
   	
   	      free( p_matrix[k] );
   	
   	   }   
   	   
   	   free( p_matrix );
   	   return NULL;
	
	}
   
   }
   
   for( unsigned short int i = 0; i < rows; i++ )
   {
      for( unsigned short int j = 0; j < cols; j++ ) 
      {
   	
          p_matrix[i][j] = 0;
   	 
      }   

   }
 
   matrix->p_matrix = p_matrix;
   matrix->rows = rows;
   matrix->cols = cols;
   
   return matrix;

}

matrix_float* create_example_matrix( unsigned short int rank )
{

   matrix_float* matrix = create_empty_float_matrix( rank, rank );
   
   if( matrix == NULL)
      return NULL;
   
   unsigned int k = 1;
   
   for( unsigned short int i = 0; i < rank; i++ )
   {
      
      for( unsigned short int j = 0; j < rank; j++ )
      {
      
         matrix->p_matrix[i][j] = k;
         k++;
      
      }
      
   }
   
   return matrix;
   
}

void print_matrix( matrix_float * matrix )
{
   for( unsigned short int i = 0; i < matrix->rows; i++ )
   {
      
      for( unsigned short int j = 0; j < matrix->cols; j++ )
      {
      
         printf("%f ", matrix->p_matrix[i][j] );
      
      }
      
      printf("\r\n");
   
   }

   printf("\r\n");
   
}
