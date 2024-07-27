#include "matrix.h"

int main(int argc , char **argv)
{

	if (argc != 4)
	{
		printf("Usage: %s <max value> <nrows> <ncols>.\n", argv[0]);
		return 1;
	}

	size_t max_value = (size_t) atoi(argv[1]);
	size_t rows = (size_t) atoi(argv[2]);
	size_t cols = (size_t) atoi(argv[3]);

	Matrix init  = random_matrix(max_value, rows, cols);
	Matrix init1 = random_matrix(max_value, rows, cols);

	Matrix sub = matrix_sub(&init , &init1);
	Matrix add = matrix_add(&init , &init1);
	Matrix mult = matrix_multiplication(&init , &init1);
	Matrix T = Transpose(&init);

	MATRIX_PRINT(init);
	MATRIX_PRINT(init1);
	MATRIX_PRINT(sub);
	MATRIX_PRINT(add);
	MATRIX_PRINT(mult);
	MATRIX_PRINT(T);

	unload(&init);
	unload(&init1);
	unload(&sub);
	unload(&add);
	unload(&mult);
	unload(&T);
	return 0;
}
