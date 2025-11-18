#include "matrix.h"


/* <-------------------------------------------------------- Local Functions --------------------------------------------------------> */
//Function that returns the absolute value of a float
static float _fab( float num )
{

   if( num < 0.0f )
      return -num;
   else
      return num;
   
}


/* <-------------------------------------------------------- Matrix Creation --------------------------------------------------------> */
//Starting from the number of rows and columns, return an empty matrix_float
matrix_float* create_empty_float_matrix( unsigned short int rows, unsigned short int cols )
{
   
   float * p_matrix = create_simple_float_matrix( rows, cols ); //Call the function that create a simple double pointer float matrix
   
   if( p_matrix == NULL )
      return NULL;
   
   matrix_float * matrix = ( matrix_float * ) malloc ( sizeof( matrix_float ) );
  
   if( matrix == NULL )
   {
      free_simple_float_matrix( p_matrix ); //If the matrix_float is not correctly allocated, free memory and return
      return NULL;
   }
   
   matrix->p_matrix = p_matrix;
   matrix->rows = rows;
   matrix->cols = cols;
   
   basic_double_loop_matrix( matrix, insert_zero_matrix_elements ); //Insert 0 in to the matrix

   
   return matrix;

}

//Create a squared matrix with numbers of the cell corrisponding to an incremental index ( this is used to debug / for testing purpose )
matrix_float* create_example_matrix( unsigned short int rank )
{

   matrix_float* matrix = create_empty_float_matrix( rank, rank ); //Create and empty matrix_float
   
   if( matrix == NULL)
      return NULL;
   
   
   basic_double_loop_matrix( matrix, insert_example_matrix_elements ); //Insert indexed values into the matrix
   
   
   return matrix;
   
}

//Create a matrix_float with 1 on the main diagonal
matrix_float* create_identity_matrix( unsigned short int rank )
{
   matrix_float* matrix = create_empty_float_matrix( rank, rank ); //Create an empty matrix_float
   
   if( matrix == NULL )
      return NULL;
      
   //Inserting 1 on the main diagonal
   for( unsigned short int i = 0; i < rank; i++ )
   {
   
      GET_ELEMENT( matrix, i, i ) = 1;
   
   }
   
   return matrix;
   
}


/* <-------------------------------------------------------- Matrices Operations --------------------------------------------------------> */
//Function that takes in two matrix_float and return their difference
matrix_float* difference_matrices( matrix_float * matrix1, matrix_float * matrix2 )
{
  
   return sum_difference_matrices( matrix1, matrix2, difference_matrices_elements );
   
}

//Function that takes in two matrix_float and return their product
matrix_float* product_matrices( matrix_float * matrix1, matrix_float * matrix2 )
{
   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;

   if( !( matrix1->cols == matrix2->rows ) )
      return NULL;
   
   
   matrix_float* matrix = create_empty_float_matrix( matrix1->rows, matrix2->cols );   
   
   if( matrix == NULL )
   	return NULL;
   
   
   basic_double_loop_matrices( matrix, ( const matrix_float * ) matrix1, ( const matrix_float * ) matrix2, product_matrices_elements );
   
   return matrix;
      
}  

//Function that takes in two matrix_float and return their sum
matrix_float* sum_matrices( matrix_float * matrix1, matrix_float * matrix2 )
{
  
   return sum_difference_matrices( matrix1, matrix2, sum_matrices_elements );
   
}

//Function that takes in a matrix_float and return the transpose
matrix_float* transpose_matrix( matrix_float * matrix )
{
   
   matrix_float* transpose = create_empty_float_matrix( matrix->cols, matrix->rows ); 
   
   if( transpose == NULL )
   	return NULL;

   for( unsigned short int i = 0; i < transpose->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < transpose->cols; j++ )
      {
      
         GET_ELEMENT( transpose, i, j ) = GET_ELEMENT( matrix, j, i );
      
      }
   
   }

   return transpose;

}

//Function that takes in a matrix_float and return the inverse
matrix_float* inverse_matrix( matrix_float * matrix )
{

   if( matrix == NULL || matrix->p_matrix == NULL || !( matrix->cols == matrix->rows ) )
   	return NULL;
   
   
   float* augmented_matrix = create_simple_float_matrix( matrix->rows, 2 * matrix->cols );
   
   if( augmented_matrix == NULL )
      return NULL;

   for( unsigned short int i = 0; i < matrix->rows; i++ )
   {
   
      for( unsigned int j = 0; j < matrix->cols * 2; j++ )
      {
      
         if( j < matrix->cols )
         {
            augmented_matrix[i * (2 * matrix->cols) + j] = GET_ELEMENT( matrix, i, j );
         }
         else if( ( j - matrix->cols ) == i )
         {
            augmented_matrix[i * (2 * matrix->cols) + j] = 1;
         }
         else
         {
            augmented_matrix[i * (2 * matrix->cols) + j] = 0;
         }
         
      }
      
   }
   
   
   for( unsigned short int i = 0; i < matrix->rows; i++ )
   {
   
      unsigned short int pivot_row = i;
      
      for( unsigned short int k = i + 1; k < matrix->rows; k++ )
      {
      
         if( _fab( augmented_matrix[k * (2 * matrix->cols) + i] ) > _fab( augmented_matrix[pivot_row * (2 * matrix->cols) + i] ) )
         {
            pivot_row = k;
         }
         
      }
      
      if ( _fab( augmented_matrix[pivot_row * (2 * matrix->cols) + i] ) < EPSILON ) {
         printf("Singular Matrix.");
         free_simple_float_matrix( augmented_matrix );
         return NULL;
      }

      if (pivot_row != i) 
      {
         for ( unsigned int j = 0; j < 2 * matrix->cols; j++ ) 
         {
         
            float tmp = augmented_matrix[i * (2 * matrix->cols) + j];
            augmented_matrix[i * (2 * matrix->cols) + j] = augmented_matrix[pivot_row * (2 * matrix->cols) + j];
            augmented_matrix[pivot_row * (2 * matrix->cols) + j] = tmp;
            
         }
      }


      float pivot = augmented_matrix[i * (2 * matrix->cols) + i];
      
      for ( unsigned int j = 0; j < 2 * matrix->cols; j++ ) 
      {
      
         augmented_matrix[i * (2 * matrix->cols) + j] /= pivot;
         
      }


      for ( unsigned short int row = 0; row < matrix->rows; row++ ) 
      {
      
         if (row != i)
         {
            float factor = augmented_matrix[row * (2 * matrix->cols) + i];
            
            for ( unsigned int col = 0; col < 2 * matrix->cols; col++ ) 
            { 
               
               augmented_matrix[row * (2 * matrix->cols) + col] -= factor * augmented_matrix[i * (2 * matrix->cols) + col];
               
            }
            
         }
         
      }
      
   }
   
   
   matrix_float* inverse = create_empty_float_matrix( matrix->rows, matrix->rows ); 
   
   if( inverse == NULL || inverse->p_matrix == NULL )
   {
      free_simple_float_matrix( augmented_matrix );
      return NULL;
   }
   
   
   for (unsigned short int i = 0; i < matrix->rows; i++) 
   {
   
        for (unsigned short int j = 0; j < matrix->cols; j++) 
        {
        
            GET_ELEMENT( inverse, i, j ) = augmented_matrix[i * (2 * matrix->cols) + (j + matrix->cols)];
            
        }
        
    }
    
    free_simple_float_matrix( augmented_matrix );
    
    return inverse;
    
}


/* <---------------------------------------------------- Matrix Operations Implementation----------------------------------------------------> */
//Operation that take in a cell of a matrix and substract the two cells of the two matrix_float in input
void difference_matrices_elements( float * result_cell, const matrix_float * matrix1, const matrix_float * matrix2, unsigned short int row, unsigned short int col )
{

   *result_cell = GET_ELEMENT( matrix1, row, col ) - GET_ELEMENT( matrix2, row, col );
   
}

//Operation that take in a cell of a matrix and insert the index of the correspondent cell of the example matrix
void insert_example_matrix_elements( matrix_float * matrix, unsigned short int row, unsigned short int col )
{

   GET_ELEMENT( matrix, row, col ) = ( row * matrix->cols ) + ( col + 1 );
   
}

//Operation that take in a matrix_float and insert zero in the corrispondent cell
void insert_zero_matrix_elements( matrix_float * matrix, unsigned short int row, unsigned short int col )
{

   GET_ELEMENT( matrix, row, col ) = 0;
   
}

//Operation that take in a matrix_float and print the corrispondent cell
void print_matrix_elements( matrix_float * matrix, unsigned short int row, unsigned short int col )
{

   printf( "%f ", GET_ELEMENT( matrix, row, col ) );
   
   if( col == matrix->cols - 1 )
   	printf( "\r\n" );
   	
}

//Operation that take in a cell of a matrix and product the two cells of the two matrix_float in input
void product_matrices_elements( float * result_cell, const matrix_float * matrix1, const matrix_float * matrix2, unsigned short int row, unsigned short int col )
{
   
   for( unsigned short int k = 0; k < matrix1->cols ; k++ )
   {
         
      *result_cell += GET_ELEMENT( matrix1, row, k ) * GET_ELEMENT( matrix2, k, col );
        
   }
   
}

//Function that takes in input two matrix_float and apply the function sum/difference
matrix_float* sum_difference_matrices( matrix_float * matrix1, matrix_float * matrix2, MatricesBasicOperation operation )
{

   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;
   
   if( !( ( matrix1->rows == matrix2->rows ) && ( matrix1->cols == matrix2->cols ) ) )
   	return NULL;
   
   
   matrix_float* matrix = create_empty_float_matrix( matrix1->rows, matrix1->cols ); 
   
   if( matrix == NULL )
   	return NULL;
   
   basic_double_loop_matrices( matrix, ( const matrix_float * ) matrix1, ( const matrix_float * ) matrix2, operation ); //Operation applied to cells using the basic double loop function ( a function that navigates through the matrix )
   
   
   return matrix;
   
}

//Operation that take in a cell of a matrix and sum the two cells of the two matrix_float in input
void sum_matrices_elements( float * result_cell, const matrix_float * matrix1, const matrix_float * matrix2, unsigned short int row, unsigned short int col )
{

   *result_cell = GET_ELEMENT( matrix1, row, col ) + GET_ELEMENT( matrix2, row, col );
   
}


/* <-------------------------------------------------------- Utility --------------------------------------------------------> */
//Function that takes in input the number of rows and columns, and returns a single pointer float matrix (contigous allocation)
float* create_simple_float_matrix( unsigned short int rows, unsigned short int cols )
{

   float * p_matrix = ( float * ) malloc( rows * cols * sizeof( float ) );
   return p_matrix;

}

//Function that takes in input single pointer float matrix and rows number, and free the memory
void free_simple_float_matrix( float * matrix )
{
   if( matrix == NULL )
      return;

   free( matrix );

   matrix = NULL;
   
}

//Function that takes in input a matrix_float and free the memory
void free_matrix_float( matrix_float * matrix )
{
   if( matrix == NULL )
      return;

   free_simple_float_matrix( matrix->p_matrix ); //In first place, we free the simple float matrix
   
   free( matrix ); //Then, we can free the matrix_float
   matrix = NULL;

}

//Function that takes in input a matrix_float and print the matrix_float
void print_matrix( matrix_float * matrix )
{

   if( matrix == NULL || matrix->p_matrix == NULL )
   {
      printf( "Matrix is null.\r\n" );
      return;
   }

   basic_double_loop_matrix( matrix, print_matrix_elements );

   printf("\r\n");
   
}


/* <-------------------------------------------------------- Matrix Loop Functions --------------------------------------------------------> */
//Function that takes in input an output matrix_float and two input matrix_float and apply the operation
void basic_double_loop_matrices( matrix_float * result, const matrix_float * matrix1, const matrix_float * matrix2, MatricesBasicOperation operation )
{

   for( unsigned short int i = 0; i < result->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < result->cols; j++ )
      {
      
         operation( &GET_ELEMENT(result, i, j), ( const matrix_float * ) matrix1, ( const matrix_float * ) matrix2, i, j);
      
      }
   
   }

}

//Function that takes in input a matrix_float and apply the operation
void basic_double_loop_matrix( matrix_float * matrix, MatrixBasicOperation operation )
{

   for( unsigned short int i = 0; i < matrix->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < matrix->cols; j++ )
      {
      
         operation( matrix, i, j );
      
      }
   
   }

}