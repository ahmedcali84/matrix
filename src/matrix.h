#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>


// Matrix Struction and Information
typedef struct Matrix
{
	float * A;
	float nrows;
	float ncols;
} Matrix;


Matrix allocate(float rows , float cols);

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
Matrix Hadamard_Product(Matrix * A, Matrix * B);
// Multiplies two Matrices
Matrix dot_product(Matrix * A, Matrix * B);
Matrix inverse(Matrix *A);
// Return Transpose of Matrix A
Matrix Transpose(Matrix *A);

// Test Matrices
void Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b);
#define TEST_MATRIX(A , B) Test_Matrix(A , B , #A ,#B)

Matrix create_matrix(float nrows, float ncols);

Matrix expected_matrix(Matrix *input);

float cost(Matrix *p , Matrix *y);
void train(Matrix *x , Matrix *w , Matrix *y , int epochs , float learn , int max);

// Function to free Allocated Memory
void unload(Matrix *B);

#endif //MATRIX_H