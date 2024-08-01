#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Matrix Struction and Information
typedef struct Matrix
{
	double * A;
	double nrows;
	double ncols;
} Matrix;


// Generates random Matrix(nrows x ncols)
Matrix random_matrix(int max, double nrows , double ncols);

// Prints a Matrix
void print_matrix(Matrix B, const char *name);

// Macro definition of a special print function
#define MATRIX_PRINT(B) print_matrix(B , #B)

// Adds to Matrices
Matrix  matrix_add(Matrix *A , Matrix *B);

// Subtracts two Matrices
Matrix  matrix_sub(Matrix *A , Matrix *B);

// Multiplies two Matrices
Matrix dot_product(Matrix * A, Matrix * B);

// Return Transpose of Matrix A
Matrix Transpose(Matrix *A);

// Test Matrices
void Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b);
#define TEST_MATRIX(A , B) Test_Matrix(A , B , #A ,#B)

Matrix create_matrix(double nrows, double ncols);

Matrix expected_matrix(Matrix *input);

double cost(Matrix *p , Matrix *y);
void train(Matrix *x , Matrix *w , Matrix *y , int epochs , double learn , int max);

// Function to free Allocated Memory
void unload(Matrix *B);

#endif //MATRIX_H