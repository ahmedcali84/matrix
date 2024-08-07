/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/

#include "matrix.h"

Matrix random_matrix(int max, float nrows , float ncols)
{
	float * A = malloc(sizeof(float) * (nrows*ncols));
	if (A == NULL) {
        printf(BOLD RED "Failed to allocate memory.\n"RESET);
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


void print_matrix(Matrix B, const char *name)
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
	printf("]\n");
	printf(BOLD YELLOW "[%s]: Shape: (%d , %d)\n" RESET,name,  (int) B.nrows , (int) B.ncols);
	printf("\n");
}


Matrix  matrix_add(Matrix *A , Matrix *B)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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
		fprintf(stderr, BOLD RED "Dimension Error.\n"RESET);
		return *(Matrix *) A;
	}
}


Matrix  matrix_sub(Matrix *A , Matrix *B)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->nrows,
		.ncols = A->ncols,
	};

	if (C.A == NULL)
	{
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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
		fprintf(stderr,BOLD RED "Dimension Error.\n" RESET);
		return *(Matrix *) A;
	}
}


Matrix Hadamard_Product(Matrix * A, Matrix * B)
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
		printf(BOLD RED"Failed to allocate memory.\n"RESET);
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

Matrix dot_product(Matrix * A, Matrix * B)
{
	if(A->ncols != B->nrows)
	{
		fprintf(stderr , BOLD RED"Cannot Multiply A->ncols( %lf ) != B->nrows( %lf ).\n"RESET, A->ncols,B->nrows);
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
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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

Matrix Transpose(Matrix *A)
{
	Matrix C = {
		.A = malloc(sizeof(float)* A->nrows * A->ncols),
		.nrows = A->ncols,
		.ncols = A->nrows,
	};

	if (C.A == NULL)
	{
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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


Matrix create_matrix(float nrows, float ncols , float value)
{
	Matrix C = {
		.A = malloc(sizeof(float)* nrows * ncols),
		.nrows = nrows,
		.ncols = ncols,
	};

	if (C.A == NULL)
	{
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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


Matrix expected_matrix(Matrix *input)
{
	Matrix C = {
		.A = malloc(sizeof(float)* input->nrows * input->ncols),
		.nrows = input->nrows,
		.ncols = input->ncols,
	};

	if (C.A == NULL)
	{
		printf(BOLD RED "Failed to allocate memory.\n"RESET);
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


bool Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b)
{
	for (int i = 0 ; i < (int) A.nrows; i++)
	{
		for (int j = 0 ; j < (int) A.nrows; j++)
		{
			int index = (i * A.ncols) + j;
			if(A.A[index] != B.A[index])
			{
				fprintf(stderr, BOLD RED"Error: Matrix '%s' != '%s'.\n" RESET,matrix_a , matrix_b);
				return false;
			}
		}
	}
	printf(BOLD GREEN "Matrix '%s' = '%s'.\n"RESET,matrix_a , matrix_b);
	return true;
}


void unload(Matrix *B)
{
	free(B->A);
	B->A = NULL;
}
