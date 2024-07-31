#include "matrix.h"
#include <time.h>

// Function to apply an activation function element-wise (e.g., ReLU)
void apply_activation(Matrix *A) {
    for (size_t i = 0; i < A->nrows * A->ncols; i++) {
        A->A[i] = (A->A[i] > 0) ? A->A[i] : 0;  // ReLU activation
    }
}


int cost(Matrix *p , Matrix *y)
{
	int cost = 0;
	int total_elements = p->nrows * p->ncols;
	for (size_t i = 0; i < (size_t) total_elements; i++)
	{
		int d = p->A[i] - y->A[i];
		cost += d * d;
	}
	return cost / total_elements;
}


int main(void) //int main(int argc , char **argv)
{

	// if (argc != 6)
	// {
	// 	printf("Usage: %s <max value> (Matrix1) <nrows> <ncols> (Matrix2) <nrows1> <ncols2>.\n", argv[0]);
	// 	return 1;
	// }

	// 1 2 2
	// 2 2 4
	// 3 2 6
	// 4 2 8 
	// 5 2 10
	// 6 2 12
	// 7 2 14

	// size_t max_value = (size_t) atoi(argv[1]);
	// size_t rows = (size_t) atoi(argv[2]);
	// size_t cols = (size_t) atoi(argv[3]);
	// size_t rows1 = (size_t) atoi(argv[4]);
	// size_t cols2 = (size_t) atoi(argv[5]);

	// srand(time(NULL));

	Matrix input = random_matrix(10, 1, 8);
	Matrix weights = random_matrix(10, 8, 8);
	// Matrix bias  = random_matrix(10, 1, 4);
	Matrix expected =  expected_matrix(&input);
	

	// Perform forward pass: Z = input * weights + bias
    Matrix z = matrix_multiplication(&input, &weights);
    // Matrix output = matrix_add(&z, &bias);

	int eps = 1e-1;
	int c = cost(&z , &expected);
	printf("c = %d\n", c);
	for (size_t i = 0; i < 1000000; i++)
	{
		c -= eps;
	}
    // Apply activation function
    // apply_activation(&z);



    // Print the output
	MATRIX_PRINT(input);
    MATRIX_PRINT(z);
	MATRIX_PRINT(expected);
	printf("c = %d\n", c);

    // Free allocated memory
    unload(&input);
    unload(&weights);
    // unload(&bias);
    unload(&z);
    // unload(&output);

	return 0;
}
