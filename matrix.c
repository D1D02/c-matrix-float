#include "matrix.h"


/* <-------------------------------------------------------- Local Functions --------------------------------------------------------> */
//Function that returns the absolute value of a float
static matrix_type _fab( matrix_type num )
{

   if( num < 0.0f )
      return -num;
   else
      return num;
   
}


/* <-------------------------------------------------------- Matrix Creation --------------------------------------------------------> */
//Starting from the number of rows and columns, return an empty matrix
matrix* create_empty_matrix( unsigned short int rows, unsigned short int cols )
{
   
   matrix_type * p_matrix = create_simple_matrix( rows, cols ); //Call the function that create a simple double pointer float matrix
   
   if( p_matrix == NULL )
      return NULL;
   
   matrix * tmp = ( matrix * ) malloc ( sizeof( matrix ) );
  
   if( tmp == NULL )
   {
      free_simple_matrix( p_matrix ); //If the matrix is not correctly allocated, free memory and return
      return NULL;
   }
   
   tmp->p_matrix = p_matrix;
   tmp->rows = rows;
   tmp->cols = cols;
   
   basic_double_loop_matrix( tmp, insert_zero_matrix_elements ); //Insert 0 in to the matrix

   
   return tmp;

}

//Create a squared matrix with numbers of the cell corrisponding to an incremental index ( this is used to debug / for testing purpose )
matrix* create_example_matrix( unsigned short int rank )
{

   matrix* tmp = create_empty_matrix( rank, rank ); //Create and empty matrix
   
   if( tmp == NULL)
      return NULL;
   
   
   basic_double_loop_matrix( tmp, insert_example_matrix_elements ); //Insert indexed values into the matrix
   
   
   return tmp;
   
}

//Create a matrix with 1 on the main diagonal
matrix* create_identity_matrix( unsigned short int rank )
{
   matrix* tmp = create_empty_matrix( rank, rank ); //Create an empty matrix
   
   if( tmp == NULL )
      return NULL;
      
   //Inserting 1 on the main diagonal
   for( unsigned short int i = 0; i < rank; i++ )
   {
   
      GET_ELEMENT( tmp, i, i ) = 1;
   
   }
   
   return tmp;
   
}


/* <-------------------------------------------------------- Matrices Operations --------------------------------------------------------> */
//Function that takes in two matrix and return their difference
matrix* difference_matrices( matrix * matrix1, matrix * matrix2 )
{
  
   return sum_difference_matrices( matrix1, matrix2, difference_matrices_elements );
   
}

//Function that takes in two matrix and return their product
matrix* product_matrices( matrix * matrix1, matrix * matrix2 )
{
   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;

   if( !( matrix1->cols == matrix2->rows ) )
      return NULL;
   
   
   matrix* tmp = create_empty_matrix( matrix1->rows, matrix2->cols );   
   
   if( tmp == NULL )
   	return NULL;
   
   
   basic_double_loop_matrices( tmp, ( const matrix * ) matrix1, ( const matrix * ) matrix2, product_matrices_elements );
   
   return tmp;
      
}  

//Function that takes in two matrix and return their sum
matrix* sum_matrices( matrix * matrix1, matrix * matrix2 )
{
  
   return sum_difference_matrices( matrix1, matrix2, sum_matrices_elements );
   
}

//Function that takes in a matrix and return the transpose
matrix* transpose_matrix( matrix * tmp )
{
   
   matrix* transpose = create_empty_matrix( tmp->cols, tmp->rows ); 
   
   if( transpose == NULL )
   	return NULL;

   for( unsigned short int i = 0; i < transpose->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < transpose->cols; j++ )
      {
      
         GET_ELEMENT( transpose, i, j ) = GET_ELEMENT( tmp, j, i );
      
      }
   
   }

   return transpose;

}

//Function that takes in a matrix and return the inverse
matrix* inverse_matrix( matrix * tmp )
{

   if( tmp == NULL || tmp->p_matrix == NULL || !( tmp->cols == tmp->rows ) )
   	return NULL;
   
   
   float* augmented_matrix = create_simple_matrix( tmp->rows, 2 * tmp->cols );
   
   if( augmented_matrix == NULL )
      return NULL;

   for( unsigned short int i = 0; i < tmp->rows; i++ )
   {
   
      for( unsigned int j = 0; j < tmp->cols * 2; j++ )
      {
      
         if( j < tmp->cols )
         {
            augmented_matrix[i * (2 * tmp->cols) + j] = GET_ELEMENT( tmp, i, j );
         }
         else if( ( j - tmp->cols ) == i )
         {
            augmented_matrix[i * (2 * tmp->cols) + j] = 1;
         }
         else
         {
            augmented_matrix[i * (2 * tmp->cols) + j] = 0;
         }
         
      }
      
   }
   
   
   for( unsigned short int i = 0; i < tmp->rows; i++ )
   {
   
      unsigned short int pivot_row = i;
      
      for( unsigned short int k = i + 1; k < tmp->rows; k++ )
      {
      
         if( _fab( augmented_matrix[k * (2 * tmp->cols) + i] ) > _fab( augmented_matrix[pivot_row * (2 * tmp->cols) + i] ) )
         {
            pivot_row = k;
         }
         
      }
      
      if ( _fab( augmented_matrix[pivot_row * (2 * tmp->cols) + i] ) < EPSILON ) {
         printf("Singular Matrix.");
         free_simple_matrix( augmented_matrix );
         return NULL;
      }

      if (pivot_row != i) 
      {
         for ( unsigned int j = 0; j < 2 * tmp->cols; j++ ) 
         {
         
            matrix_type tmp1 = augmented_matrix[i * (2 * tmp->cols) + j];
            augmented_matrix[i * (2 * tmp->cols) + j] = augmented_matrix[pivot_row * (2 * tmp->cols) + j];
            augmented_matrix[pivot_row * (2 * tmp->cols) + j] = tmp1;
            
         }
      }


      matrix_type pivot = augmented_matrix[i * (2 * tmp->cols) + i];
      
      for ( unsigned int j = 0; j < 2 * tmp->cols; j++ ) 
      {
      
         augmented_matrix[i * (2 * tmp->cols) + j] /= pivot;
         
      }


      for ( unsigned short int row = 0; row < tmp->rows; row++ ) 
      {
      
         if (row != i)
         {
            matrix_type factor = augmented_matrix[row * (2 * tmp->cols) + i];
            
            for ( unsigned int col = 0; col < 2 * tmp->cols; col++ ) 
            { 
               
               augmented_matrix[row * (2 * tmp->cols) + col] -= factor * augmented_matrix[i * (2 * tmp->cols) + col];
               
            }
            
         }
         
      }
      
   }
   
   
   matrix* inverse = create_empty_matrix( tmp->rows, tmp->rows ); 
   
   if( inverse == NULL || inverse->p_matrix == NULL )
   {
      free_simple_matrix( augmented_matrix );
      return NULL;
   }
   
   
   for (unsigned short int i = 0; i < tmp->rows; i++) 
   {
   
        for (unsigned short int j = 0; j < tmp->cols; j++) 
        {
        
            GET_ELEMENT( inverse, i, j ) = augmented_matrix[i * (2 * tmp->cols) + (j + tmp->cols)];
            
        }
        
    }
    
    free_simple_matrix( augmented_matrix );
    
    return inverse;
    
}


/* <---------------------------------------------------- Matrix Operations Implementation----------------------------------------------------> */
//Operation that take in a cell of a matrix and substract the two cells of the two matrix in input
void difference_matrices_elements( float * result_cell, const matrix * matrix1, const matrix * matrix2, unsigned short int row, unsigned short int col )
{

   *result_cell = GET_ELEMENT( matrix1, row, col ) - GET_ELEMENT( matrix2, row, col );
   
}

//Operation that take in a cell of a matrix and insert the index of the correspondent cell of the example matrix
void insert_example_matrix_elements( matrix * tmp, unsigned short int row, unsigned short int col )
{

   GET_ELEMENT( tmp, row, col ) = ( row * tmp->cols ) + ( col + 1 );
   
}

//Operation that take in a matrix and insert zero in the corrispondent cell
void insert_zero_matrix_elements( matrix * tmp, unsigned short int row, unsigned short int col )
{

   GET_ELEMENT( tmp, row, col ) = 0;
   
}

//Operation that take in a matrix and print the corrispondent cell
void print_matrix_elements( matrix * tmp, unsigned short int row, unsigned short int col )
{

   printf( "%f ", GET_ELEMENT( tmp, row, col ) );
   
   if( col == tmp->cols - 1 )
   	printf( "\r\n" );
   	
}

//Operation that take in a cell of a matrix and product the two cells of the two matrix in input
void product_matrices_elements( matrix_type * result_cell, const matrix * matrix1, const matrix * matrix2, unsigned short int row, unsigned short int col )
{
   
   for( unsigned short int k = 0; k < matrix1->cols ; k++ )
   {
         
      *result_cell += GET_ELEMENT( matrix1, row, k ) * GET_ELEMENT( matrix2, k, col );
        
   }
   
}

//Function that takes in input two matrix and apply the function sum/difference
matrix* sum_difference_matrices( matrix * matrix1, matrix * matrix2, MatricesBasicOperation operation )
{

   if( matrix1 == NULL || matrix2 == NULL )
   	return NULL;
   
   if( !( ( matrix1->rows == matrix2->rows ) && ( matrix1->cols == matrix2->cols ) ) )
   	return NULL;
   
   
   matrix* tmp = create_empty_matrix( matrix1->rows, matrix1->cols ); 
   
   if( tmp == NULL )
   	return NULL;
   
   basic_double_loop_matrices( tmp, ( const matrix * ) matrix1, ( const matrix * ) matrix2, operation ); //Operation applied to cells using the basic double loop function ( a function that navigates through the matrix )
   
   
   return tmp;
   
}

//Operation that take in a cell of a matrix and sum the two cells of the two matrix in input
void sum_matrices_elements( matrix_type * result_cell, const matrix * matrix1, const matrix * matrix2, unsigned short int row, unsigned short int col )
{

   *result_cell = GET_ELEMENT( matrix1, row, col ) + GET_ELEMENT( matrix2, row, col );
   
}


/* <-------------------------------------------------------- Utility --------------------------------------------------------> */
//Function that takes in input the number of rows and columns, and returns a single pointer float matrix (contigous allocation)
matrix_type* create_simple_matrix( unsigned short int rows, unsigned short int cols )
{

   matrix_type * p_matrix = ( matrix_type * ) malloc( rows * cols * sizeof( matrix_type ) );
   return p_matrix;

}

//Function that takes in input single pointer float matrix and rows number, and free the memory
void free_simple_matrix( matrix_type * tmp )
{
   if( tmp == NULL )
      return;

   free( tmp );

   tmp = NULL;
   
}

//Function that takes in input a matrix and free the memory
void free_matrix( matrix * tmp )
{
   if( tmp == NULL )
      return;

   free_simple_matrix( tmp->p_matrix ); //In first place, we free the simple float matrix
   
   free( tmp ); //Then, we can free the matrix
   tmp = NULL;

}

//Function that takes in input a matrix and print the matrix
void print_matrix( matrix * tmp )
{

   if( tmp == NULL || tmp->p_matrix == NULL )
   {
      printf( "Matrix is null.\r\n" );
      return;
   }

   basic_double_loop_matrix( tmp, print_matrix_elements );

   printf("\r\n");
   
}


/* <-------------------------------------------------------- Matrix Loop Functions --------------------------------------------------------> */
//Function that takes in input an output matrix and two input matrix and apply the operation
void basic_double_loop_matrices( matrix * result, const matrix * matrix1, const matrix * matrix2, MatricesBasicOperation operation )
{

   for( unsigned short int i = 0; i < result->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < result->cols; j++ )
      {
      
         operation( &GET_ELEMENT(result, i, j), ( const matrix * ) matrix1, ( const matrix * ) matrix2, i, j);
      
      }
   
   }

}

//Function that takes in input a matrix and apply the operation
void basic_double_loop_matrix( matrix * tmp, MatrixBasicOperation operation )
{

   for( unsigned short int i = 0; i < tmp->rows; i++ )
   {
   
      for( unsigned short int j = 0; j < tmp->cols; j++ )
      {
      
         operation( tmp, i, j );
      
      }
   
   }

}