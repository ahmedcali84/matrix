
#include "matrix.h"

Matrix random_matrix(int max, double nrows , double ncols)
{
	double * A = malloc(sizeof(double) * (nrows*ncols));
	if (A == NULL) {
        perror("Failed to allocate memory");
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

	double *temp = A;

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
			printf(" %lf ", B.A[index]);
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
		.A = malloc(sizeof(double) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
		perror("Failed to allocate memory");
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


Matrix  matrix_sub(Matrix *A , Matrix *B)
{
	Matrix C = {
		.nrows = A->nrows,
		.ncols = A->ncols,
		.A = malloc(sizeof(double) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
		perror("Failed to allocate memory");
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
		fprintf(stderr, "Dimension Error.\n");
		return *(Matrix *) A;
	}
}


Matrix Hadamard_Product(Matrix * A, Matrix * B)
{
	assert(A->ncols == B->ncols);
	assert(A->nrows == B->nrows);

	Matrix C = {
		.ncols = B->ncols,
		.nrows = A->nrows,
		.A = malloc(A->ncols * B->nrows * sizeof(double)),
	};

	if (C.A == NULL) {
		perror("Failed to allocate memory");
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
		fprintf(stderr , "Cannot Multiply A->ncols( %lf ) != B->nrows( %lf ).\n", A->ncols,B->nrows);
		exit(EXIT_FAILURE);
	}

	Matrix C = {
		.ncols = B->ncols,
		.nrows = A->nrows,
		.A = malloc(A->ncols * B->nrows * sizeof(double)),
	};

	assert(C.nrows == A->nrows);
	assert(C.ncols == B->ncols);

	if (C.A == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < (int) A->nrows; i++) 
	{
		for (int j = 0; j < (int) B->ncols; j++) 
		{
			double nth_element = 0;
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


Matrix Transpose(Matrix *A)
{
	Matrix C = {
		.nrows = A->ncols,
		.ncols = A->nrows,
		.A = malloc(sizeof(double) * (A->ncols * A->nrows)),
	};

	if (C.A == NULL) {
        perror("Failed to allocate memory");
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


Matrix create_matrix(double nrows, double ncols)
{
	Matrix C = {
		.A = malloc(nrows * ncols*sizeof(double)),
		.ncols = ncols,
		.nrows = nrows,
	};

	if (C.A == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	double k = 0;
	for (int i = 0; i < (int)nrows; i++)
	{
		for (int j = 0; j < (int)ncols; j++)
		{
			int index = i * ncols + j;
			C.A[index] = k + 1;
			k++;
		}
	}
	return C;
}


Matrix expected_matrix(Matrix *input)
{
	Matrix C = {
		.A = (double *)calloc((input->nrows * input->ncols), sizeof(double)),
		.ncols = input->ncols,
		.nrows = input->nrows,
	};

	if (C.A == NULL)
	{
		perror("Failed to allocate memory");
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


void Test_Matrix(Matrix A , Matrix B , char *matrix_a , char *matrix_b)
{
	for (int i = 0 ; i < (int) A.nrows; i++)
	{
		for (int j = 0 ; j < (int) A.nrows; j++)
		{
			int index = (i * A.ncols) + j;
			assert(A.A[index] == B.A[index]);
		}
	}
	printf("Matrix '%s' = '%s'.\n",matrix_a , matrix_b);
}


double cost(Matrix *p , Matrix *y)
{
	double cost = 0;
	double total_elements = p->nrows * p->ncols;
	for (int i = 0; i < (int) total_elements; i++)
	{
		double d = p->A[i] - y->A[i];
		cost += d * d;
	}
	return cost / total_elements;
}


void train(Matrix *x , Matrix *w , Matrix *y , int epochs , double learn , int max)
{
	Matrix z ;
	double initial_cost , final_cost;
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		z =  dot_product(x , w);
		initial_cost = cost(&z , y);
		for (int i = 0; i < (int) w->nrows; i++)
		{
			for (int j = 0; j < (int) w->ncols; j++)
			{
				double gradient = 0.0;
                for (int k = 0; k < (int)x->nrows; k++) {
                    int index_z = k * z.ncols + j; // Assuming z is of shape [x->nrows x->ncols]
                    int index_x = k * x->ncols + i; // Assuming x is of shape [x->nrows x->ncols]
                    gradient += (z.A[index_z] - y->A[index_z]) * x->A[index_x];
                }
                int index_w = i * w->ncols + j;
                w->A[index_w] -= (learn / x->nrows) * gradient;
            }
        }
		if (epoch % max == 0 || epoch == epochs - 1) {
            printf("Epoch %d, Cost: %lf\n", epoch, initial_cost);
        }
		unload(&z);
	}



	z = dot_product(x ,w);
	final_cost = cost(&z , y);
	printf("Final Cost = %lf\n", final_cost);

	unload(&z);
}


void unload(Matrix *B)
{
	free(B->A);
	B->A = NULL;
}