#include "matrix.h"

static unsigned short int _min( unsigned short int num1, unsigned short int num2 )
{
   if( num1 < num2 ) return num1;
   if( num2 < num1 ) return num2;
   else return num1;
}


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

matrix_float* create_identity_matrix( unsigned short int rank )
{
   matrix_float* matrix = create_empty_float_matrix( rank, rank );
   
   if( matrix == NULL )
      return NULL;
      
   for( int i = 0; i < rank; i++ )
   {
   
      matrix->p_matrix[i][i] = 1;
   
   }
   
   return matrix;
   
}


matrix_float* sum_matrices( matrix_float * matrix1, matrix_float * matrix2 )
{
   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;
   
   if( !( ( matrix1->rows == matrix2->rows ) && ( matrix1->cols == matrix2->cols ) ) )
   	return NULL;
   
   matrix_float* matrix = create_empty_float_matrix( matrix1->rows, matrix1->cols ); 
   
   for( unsigned short int i = 0; i < matrix1->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < matrix1->cols; j++ )
      {
      
         matrix->p_matrix[i][j] = matrix1->p_matrix[i][j] + matrix2->p_matrix[i][j];
      
      }
   
   }
   
   return matrix;
   
}

matrix_float* product_matrices( matrix_float * matrix1, matrix_float * matrix2 )
{
   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;

   if( !( matrix1->cols == matrix2->rows ) )
      return NULL;
   
   unsigned short int rows = _min( matrix1->rows, matrix2->rows );
   unsigned short int cols = _min( matrix1->cols, matrix2->cols );
   
   
   matrix_float* matrix = create_empty_float_matrix( rows, cols );   
   
   
   for( unsigned short int i = 0; i < rows; i++ )
   {
   
      for( unsigned short int j = 0; j < cols; j++ )
      {
      
         for( unsigned short int k = 0; k < matrix1->cols ; k++ )
         {
         
            matrix->p_matrix[i][j] += matrix1->p_matrix[i][k] * matrix2->p_matrix[k][j];
         
         }
      
      }
   
   }
   
   return matrix;
      
}  


void print_matrix( matrix_float * matrix )
{
   if( matrix == NULL )
      return;

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
