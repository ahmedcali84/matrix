#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define MATDEF static

// Matrix Struction and Information
typedef struct Matrix
{
	float * A;
	size_t nrows;
	size_t ncols;
} Matrix;

/*
************** MATRIX OPERATIONS FUNCTIONS DECLARATIONS *******************
*/

// Generates random Matrix(nrows x ncols)
MATDEF Matrix random_matrix(int max, size_t nrows , size_t ncols);

// Prints a Matrix
MATDEF void print_matrix(Matrix B, const char *name);

// Macro definition of a special print function
#define PRINT(B) print_matrix(B , #B)

//Prints the shape of the matrix
MATDEF int shape(Matrix A, const char *name);

//Macro definition of a special shape printing function
#define SHAPE(A) shape(A , #A)

// Adds to Matrices
MATDEF Matrix  matrix_add(Matrix *A , Matrix *B);

// Subtracts two Matrices
MATDEF Matrix  matrix_sub(Matrix *A , Matrix *B);

// Computes Element-wise Product of Two Matrices
MATDEF Matrix Hadamard_Product(Matrix * A, Matrix * B);

// Computes the Dot-Product of  two Matrices || Two Vectors || a Vector and a Matrix
MATDEF Matrix dot_product(Matrix * A, Matrix * B);

// Returns the Inverse of a Matrix (in-Works , will update when its finished)
// Matrix inverse(Matrix *A);

// Return Transpose of Matrix A
MATDEF Matrix Transpose(Matrix *A);

// Test Matrices
MATDEF bool Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b);

// Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix
#define TEST_MATRIX(A , B) Test_Matrix(A , B , #A ,#B)

// Creates A Matrix of n,... , n+1 Matrix (For Development Purposes)
MATDEF Matrix create_matrix(size_t nrows, size_t ncols , size_t value);

// Returns the doubled-version of created Matrix (For Development Purposes)
MATDEF Matrix expected_matrix(Matrix *input);

// Function to free Allocated Memory
MATDEF void unload(Matrix *B);


/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/


MATDEF Matrix random_matrix(int max, size_t nrows , size_t ncols)
{
	float * A = malloc(sizeof(float) * (nrows*ncols));
	if (A == NULL) {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

	for (int i = 0; i < (int) nrows; i++)
	{
		for (int j = 0; j < (int) ncols; j++)
		{
			int index = i*ncols + j;
			A[index] = rand() % max;
		}
	}

	float *temp = A;

	Matrix dummy = {
		.A = temp,
		.nrows = nrows,
		.ncols = ncols,
	};
	return dummy;
}


MATDEF void print_matrix(Matrix B, const char *name)
{
	printf("%s = [\n", name);
	for (int i = 0; i < (int) B.nrows; i++)
	{
		for (int j = 0; j < (int) B.ncols; j++)
		{
			int index = i*B.ncols + j;
			printf(" %.2f ", B.A[index]);
		}
		printf("\n");
	}
	printf("]");
	printf("\n");
}


MATDEF int shape(Matrix A, const char *name)
{
	printf("%s(Shape: (%d , %d))\n",name, (int) A.nrows , (int) A.ncols);
	return 0;
}


MATDEF Matrix  matrix_add(Matrix *A , Matrix *B)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf( "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	if(A->ncols == B->ncols && A->nrows == B->nrows)
	{
		for (int i = 0; i < (int) A->nrows; i++)
		{
			for (int j = 0; j < (int) A->ncols; j++)
			{
				int index = i*A->ncols + j;
				C.A[index] = A->A[index] + B->A[index];	
			}
		}
		
		return C;
	}
	else
	{
		unload(&C);
		fprintf(stderr, "Dimension Error.\n");
		return *(Matrix *) A;
	}
}


MATDEF Matrix  matrix_sub(Matrix *A , Matrix *B)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf( "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	if(A->ncols == B->ncols && A->nrows == B->nrows)
	{
		for (int i = 0; i < (int) A->nrows; i++)
		{
			for (int j = 0; j < (int) A->ncols; j++)
			{
				int index = i*A->ncols + j;
				C.A[index] = A->A[index] - B->A[index];	
			}
		}
		
		return C;
	}
	else
	{
		unload(&C);
		fprintf(stderr,  "Dimension Error.\n");
		return *(Matrix *) A;
	}
}


MATDEF Matrix Hadamard_Product(Matrix * A, Matrix * B)
{
	assert(A->ncols == B->ncols);
	assert(A->nrows == B->nrows);

	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf( "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < (int) A->nrows; i++)
	{
		for (int j = 0; j < (int) A->ncols; j++)
		{
			int index = i*A->ncols + j;
			C.A[index] = A->A[index] * B->A[index];	
		}
	}
	return C;
}

MATDEF Matrix dot_product(Matrix * A, Matrix * B)
{
	if(A->ncols != B->nrows)
	{
		fprintf(stderr ,  "Cannot Multiply A->ncols( %zu ) != B->nrows( %zu ).\n", A->ncols,B->nrows);
		exit(EXIT_FAILURE);
	}

	Matrix C = {
		.ncols = B->ncols,
		.nrows = A->nrows,
		.A = malloc(A->ncols * B->nrows * sizeof(float)),
	};

	assert(C.nrows == A->nrows);
	assert(C.ncols == B->ncols);

	if (C.A == NULL) {
		printf(  "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < (int) A->nrows; i++) 
	{
		for (int j = 0; j < (int) B->ncols; j++) 
		{
			float nth_element = 0;
			for (int k = 0; k < (int) A->ncols; k++) 
			{
				int indexA = i * A->ncols + k;
				int indexB = k * B->ncols + j;
				nth_element += A->A[indexA] * B->A[indexB];
			}
			int indexC = i * C.ncols + j;
			C.A[indexC] = nth_element;
		}
	}

	return C;
}

/*  *************** IN DEVELOPMENT , NOT COMPLETED YET *******************
Matrix inverse(Matrix *A)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf(  "Failed to allocate memory.\n);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < (int) A->ncols; i++)
	{
		for (int j = 0; j < (int) A->nrows; j++)
		{
			int indexC = (i * A->nrows) + j;
			C.A[indexC] = A->A[indexC];
		}
	}
	
	return C;
}
*************************************************************************
*/

MATDEF Matrix Transpose(Matrix *A)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->ncols,
		.ncols = A->nrows,
	};

	if (C.A == NULL)
	{
		printf(  "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < (int) A->ncols; i++)
	{
		for (int j = 0; j < (int) A->nrows; j++)
		{
			int index = (j * A->ncols) + i;
			int indexC = (i * A->nrows) + j;
			C.A[indexC] = A->A[index];
		}
	}
	
	return C;
}


MATDEF Matrix create_matrix(size_t nrows, size_t ncols , size_t value)
{
	Matrix C = {
		.A = malloc(sizeof(float)* nrows * ncols),
		.nrows = nrows,
		.ncols = ncols,
	};

	if (C.A == NULL)
	{
		printf(  "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < (int)nrows; i++)
	{
		for (int j = 0; j < (int)ncols; j++)
		{
			int index = i * ncols + j;
			C.A[index] = value;
		}
	}
	return C;
}


MATDEF Matrix expected_matrix(Matrix *input)
{
	Matrix C = {
		.A = malloc(sizeof(float)* input->nrows * input->ncols),
		.nrows = input->nrows,
		.ncols = input->ncols,
	};

	if (C.A == NULL)
	{
		printf(  "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < (int) input->nrows; i++)
	{
		for (int j = 0; j < (int) input->ncols; j++)
		{
			int index = i * input->ncols + j;
			C.A[index] = input->A[index] * 2;
		}
	}
	return C;
}


MATDEF bool Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b)
{
	for (int i = 0 ; i < (int) A.nrows; i++)
	{
		for (int j = 0 ; j < (int) A.nrows; j++)
		{
			int index = (i * A.ncols) + j;
			if(fabs(A.A[index] - B.A[index]) > 1e-6)
			{
				fprintf(stderr,  "Error: Matrix '%s' != '%s'.\n",matrix_a , matrix_b);
				return false;
			}
		}
	}
	printf("Matrix %s = %s.\n",matrix_a , matrix_b);
	return true;
}


MATDEF void unload(Matrix *B)
{
	free(B->A);
	B->A = NULL;
}

// TODO: MATRIX INVERSION
// TODO: DETERMINANT
// TODO: 


#endif //MATRIX_H
