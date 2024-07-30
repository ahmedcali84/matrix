
#include "matrix.h"

Matrix random_matrix(size_t max, size_t nrows , size_t ncols)
{
	int * A = malloc(sizeof(int) * (nrows*ncols));
	if (A == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

	for (size_t i = 0; i < nrows; i++)
	{
		for (size_t j = 0; j < ncols; j++)
		{
			size_t index = i*ncols + j;
			A[index] = rand() % max;
		}
	}

	int *temp = A;

	Matrix dummy = {
		.A = temp,
		.nrows = nrows,
		.ncols = ncols,
	};
	return dummy;
}


void print_matrix(Matrix B, const char *name)
{
	printf("%s = [\n", name);
	for (size_t i = 0; i < B.nrows; i++)
	{
		for (size_t j = 0; j < B.ncols; j++)
		{
			size_t index = i*B.ncols + j;
			printf(" %d ", B.A[index]);
		}
		printf("\n");
	}
	printf("]\n");
	printf("\n");
}


Matrix  matrix_add(Matrix *A , Matrix *B)
{
	Matrix C = {
		.nrows = A->nrows,
		.ncols = A->ncols,
		.A = malloc(sizeof(int) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	if(A->ncols == B->ncols && A->nrows == B->nrows)
	{
		for (size_t i = 0; i < A->nrows; i++)
		{
			for (size_t j = 0; j < A->ncols; j++)
			{
				size_t index = i*A->ncols + j;
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


Matrix  matrix_sub(Matrix *A , Matrix *B)
{
	Matrix C = {
		.nrows = A->nrows,
		.ncols = A->ncols,
		.A = malloc(sizeof(int) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	if(A->ncols == B->ncols && A->nrows == B->nrows)
	{
		for (size_t i = 0; i < A->nrows; i++)
		{
			for (size_t j = 0; j < A->ncols; j++)
			{
				size_t index = i*A->ncols + j;
				C.A[index] = A->A[index] - B->A[index];	
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


Matrix matrix_multiplication(Matrix * A, Matrix * B)
{
	if(A->ncols != B->nrows)
	{
		fprintf(stderr , "Cannot Multiply A->ncols( %zu ) != B->nrows( %zu ).\n", A->ncols,B->nrows);
		exit(EXIT_FAILURE);
	}

	Matrix C = {
		.ncols = B->ncols,
		.nrows = A->nrows,
		.A = malloc(sizeof(int) *(A->nrows*B->ncols)),
	};

	if (C.A == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

	// Ensure the newly allocated memory is zerod out to avoid Garbage Values
    for (size_t i = 0; i < A->nrows * B->ncols; i++)
	{
        C.A[i] = 0;
    }

	for (size_t i = 0; i < A->nrows;i++)
	{
		for (size_t j = 0; j < B->ncols; j++)
		{
			size_t nth_element = 0;
			for (size_t k = 0; k < A->ncols; k++)
			{
				size_t indexA = i * A->ncols + k;
				size_t indexB = k * B->ncols + j;
				nth_element+= A->A[indexA] * B->A[indexB];
			}
			size_t indexC = i * B->ncols + j;
			C.A[indexC] = nth_element;
		}
	}

	return C;
}


// static int determinant(Matrix *A)
// {

// }


Matrix Transpose(Matrix *A)
{
	Matrix C = {
		.nrows = A->ncols,
		.ncols = A->nrows,
		.A = malloc(sizeof(int) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

	for(size_t i = 0; i < A->ncols; i++)
	{
		for (size_t j = 0; j < A->nrows; j++)
		{
			size_t index = (j * A->ncols) + i;
			size_t indexC = (i * A->nrows) + j;
			C.A[indexC] = A->A[index];
		}
	}
	
	return C;
}


void Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b)
{
	for (size_t i = 0 ; i < A.nrows; i++)
	{
		for (size_t j = 0 ; j < A.nrows; j++)
		{
			size_t index = (i * A.ncols) + j;
			assert(A.A[index] == B.A[index]);
		}
	}
	printf("Matrix '%s' = '%s'.\n",matrix_a , matrix_b);
}


void unload(Matrix *B)
{
	free(B->A);
	B->A = NULL;
}