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

//Get Specific Element from the Matrix
MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col);

// Set a specific element from the matrix to a new value
MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value);

// Generates random Matrix(nrows x ncols)
MATDEF Matrix RANDOM_MATRIX(int max, size_t nrows , size_t ncols);

// Prints a Matrix
MATDEF void PRINT_MATRIX(Matrix B, const char *name);

// Macro definition of a special print function
#define PRINT(B) PRINT_MATRIX(B , #B)

//Prints the SHAPE of the matrix
MATDEF int MATRIX_SHAPE(Matrix A, const char *name);

//Macro definition of a special SHAPE printing function
#define SHAPE(A) MATRIX_SHAPE(A , #A)

// Adds to Matrices
MATDEF Matrix  MATRIX_ADD(Matrix *A , Matrix *B);

// Subtracts two Matrices
MATDEF Matrix  MATRIX_SUBTRACT(Matrix *A , Matrix *B);

// Computes Element-wise Product of Two Matrices
MATDEF Matrix HAMADARD_PRODUCT(Matrix * A, Matrix * B);

// Computes the Dot-Product of  two Matrices || Two Vectors || a Vector and a Matrix
MATDEF Matrix DOT_PRODUCT(Matrix * A, Matrix * B);

// Return TRANSPOSE of Matrix A
MATDEF Matrix TRANSPOSE(Matrix *A);

// Test Matrices
MATDEF bool TEST_MATRIX_EQUAL(Matrix A , Matrix B , char *matrix_a , char *matrix_b);

// Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix
#define TEST_MATRIX(A , B) TEST_MATRIX_EQUAL(A , B , #A ,#B)

// Creates A Matrix of n,... , n+1 Matrix (For Development Purposes)
MATDEF Matrix FILL(size_t nrows, size_t ncols , size_t FILL_value);

// Returns the doubled-version of created Matrix (For Development Purposes)
MATDEF Matrix EXPECTED_MATRIX(Matrix *input);

// Cost Function (CALCULATES MEAN SQUARE ERROR)
MATDEF float MSE(float pred, float Y);

// Simple Linear REGRESSION
MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha);

// Function to free Allocated Memory
MATDEF void UNLOAD(Matrix *B);


/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/

MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col)
{
	return C.A[row * C.ncols + col];
}

MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value)
{
	C.A[row * C.ncols + col] = value;
}

MATDEF Matrix RANDOM_MATRIX(int max, size_t nrows , size_t ncols)
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
			A[index] = ((float) rand() / (float) RAND_MAX) * max;
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

MATDEF void PRINT_MATRIX(Matrix B, const char *name)
{
	printf("%s = [\n", name);
	for (int i = 0; i < (int) B.nrows; i++)
	{
		for (int j = 0; j < (int) B.ncols; j++)
		{
			int index = i*B.ncols + j;
			printf(" %f ", B.A[index]);
		}
		printf("\n");
	}
	printf("]");
	printf("\n\n");
}

MATDEF int MATRIX_SHAPE(Matrix A, const char *name)
{
	printf("%s(SHAPE: (%d , %d))\n",name, (int) A.nrows , (int) A.ncols);
	return 0;
}

MATDEF Matrix  MATRIX_ADD(Matrix *A , Matrix *B)
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
		UNLOAD(&C);
		fprintf(stderr, "Dimension Error.\n");
		return *(Matrix *) A;
	}
}

MATDEF Matrix  MATRIX_SUBTRACT(Matrix *A , Matrix *B)
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
		UNLOAD(&C);
		fprintf(stderr,  "Dimension Error.\n");
		return *(Matrix *) A;
	}
}

MATDEF Matrix HAMADARD_PRODUCT(Matrix * A, Matrix * B)
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

MATDEF Matrix DOT_PRODUCT(Matrix * A, Matrix * B)
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

MATDEF Matrix TRANSPOSE(Matrix *A)
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

MATDEF Matrix FILL(size_t nrows, size_t ncols , size_t FILL_value)
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
			C.A[index] = FILL_value;
		}
	}
	return C;
}

MATDEF Matrix EXPECTED_MATRIX(Matrix *input)
{
	Matrix C = FILL(1, 1, 2);

	Matrix output = DOT_PRODUCT(input, &C);
	return output;
}

MATDEF bool TEST_MATRIX_EQUAL(Matrix A , Matrix B , char *matrix_a , char *matrix_b)
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

MATDEF float MSE(float pred, float Y)
{
	float d = pred - Y;
	return d*d;
}

MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha)
{
	Matrix pred = DOT_PRODUCT(&Ws, &X);

	for (size_t i = 0; i < pred.nrows; ++i) 
	{
        for (size_t j = 0; j < pred.ncols; ++j) 
		{
            int index = i * pred.ncols + j;
            pred.A[index] += GET_ELEMENT(bias, 0, j); // Add bias to each prediction
        }
    }
	printf("Initial Predictions: ");
	PRINT(pred);
	for (int epoch = 0; epoch < epochs; ++epoch)
	{
		for (size_t i = 0; i < Ws.nrows; ++i)
		{
			for (size_t j = 0; j < Ws.ncols; ++j)
			{
				float w = GET_ELEMENT(Ws, i, j);

				float gradient = 0.0f;
				for (size_t k = 0; k < pred.nrows; ++k)
				{
					for (size_t m = 0; m < pred.ncols; ++m)
					{
						int index = k * pred.ncols + m;
						float error = actual.A[index] - pred.A[index];
						gradient+= (-2 * error * GET_ELEMENT(X, index, j));
					}
				}
				w = w - alpha * gradient;
				SET_ELEMENT(Ws, i , j , w);
			}
		}

		Matrix new_pred = DOT_PRODUCT(&Ws, &X);
		for (size_t i = 0; i < new_pred.nrows; ++i) 
		{
            for (size_t j = 0; j < new_pred.ncols; ++j) 
			{
                int index = i * new_pred.ncols + j;
                new_pred.A[index] += GET_ELEMENT(bias, 0, j);
            }
        }
		UNLOAD(&pred);
		pred = new_pred;

		if (epoch % 1 == 0 || epoch == epochs - 1)
		{
			for (size_t i = 0; i < pred.nrows; ++i)
			{
				for (size_t j = 0; j < pred.ncols; ++j)
				{
					int index = i * pred.ncols + j;
					printf("Epoch =  %d, Cost = %f, Pred: %f, Actual = %f\n", epoch, MSE(pred.A[index], actual.A[index]), pred.A[index], actual.A[index]);
				}
			}
		}
	}
	PRINT(pred);
	UNLOAD(&pred);
}

MATDEF void UNLOAD(Matrix *B)
{
	free(B->A);
	B->A = NULL;
}

#endif //MATRIX_H
