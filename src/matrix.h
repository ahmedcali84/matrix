#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// Matrix Struction and Information
typedef struct _Matrix
{
	int * A;
	size_t nrows;
	size_t ncols;
} Matrix;


// Generates random Matrix(nrows x ncols)
Matrix random_matrix(size_t max, size_t nrows , size_t ncols);

// Prints a Matrix
void print_matrix(Matrix B, const char *name);

// Macro definition of a special print function
#define MATRIX_PRINT(B) print_matrix(B , #B)

// Adds to Matrices
Matrix  matrix_add(Matrix *A , Matrix *B);

// Subtracts two Matrices
Matrix  matrix_sub(Matrix *A , Matrix *B);

// Multiplies two Matrices
Matrix matrix_multiplication(Matrix * A, Matrix * B);

// Return Transpose of Matrix A
Matrix Transpose(Matrix *A);

// Function to free Allocated Memory
void unload(Matrix *B);

#endif //MATRIX_H