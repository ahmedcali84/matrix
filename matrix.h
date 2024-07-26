#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _Matrix
{
	int * A;
	size_t nrows;
	size_t ncols;
} Matrix;


Matrix random_matrix(size_t max, size_t nrows , size_t ncols);
void print_matrix(Matrix B, const char *name);
#define MATRIX_PRINT(B) print_matrix(B , #B)
Matrix  matrix_add(Matrix *A , Matrix *B);
Matrix  matrix_sub(Matrix *A , Matrix *B);
Matrix matrix_multiplication(Matrix * A, Matrix * B);
Matrix Transpose(Matrix *A);
void unload(Matrix *B);

#endif //MATRIX_H