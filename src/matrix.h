#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>


// Define escape codes for text formatting
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"


// Matrix Struction and Information
typedef struct Matrix
{
	float * A;
	float nrows;
	float ncols;
} Matrix;

/*
************** MATRIX OPERATIONS FUNCTIONS DECLARATIONS *******************
*/

// Generates random Matrix(nrows x ncols)
Matrix random_matrix(int max, float nrows , float ncols);

// Prints a Matrix
void print_matrix(Matrix B, const char *name);

// Macro definition of a special print function
#define MATRIX_PRINT(B) print_matrix(B , #B)

// Adds to Matrices
Matrix  matrix_add(Matrix *A , Matrix *B);

// Subtracts two Matrices
Matrix  matrix_sub(Matrix *A , Matrix *B);

// Computes Element-wise Product of Two Matrices
Matrix Hadamard_Product(Matrix * A, Matrix * B);

// Computes the Dot-Product of  two Matrices || Two Vectors || a Vector and a Matrix
Matrix dot_product(Matrix * A, Matrix * B);

// Returns the Inverse of a Matrix (in-Works , will update when its finished)
// Matrix inverse(Matrix *A);

// Return Transpose of Matrix A
Matrix Transpose(Matrix *A);

// Test Matrices
bool Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b);

// Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix
#define TEST_MATRIX(A , B) Test_Matrix(A , B , #A ,#B)

// Creates A Matrix of n,... , n+1 Matrix (For Development Purposes)
Matrix create_matrix(float nrows, float ncols , float value);

// Returns the doubled-version of created Matrix (For Development Purposes)
Matrix expected_matrix(Matrix *input);

// Function to free Allocated Memory
void unload(Matrix *B);

#endif //MATRIX_H
