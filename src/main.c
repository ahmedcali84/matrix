#include "matrix.h"
#include <time.h>

int main(int argc , char **argv)
{

	if (argc != 6)
	{
		printf("Usage: %s <max value> (Matrix1) <nrows> <ncols> (Matrix2) <nrows1> <ncols2>.\n", argv[0]);
		return 1;
	}

	size_t max_value = (size_t) atoi(argv[1]);
	size_t rows = (size_t) atoi(argv[2]);
	size_t cols = (size_t) atoi(argv[3]);
	size_t rows1 = (size_t) atoi(argv[4]);
	size_t cols2 = (size_t) atoi(argv[5]);

	srand(time(NULL));

	Matrix init  = random_matrix(max_value, rows, cols);
	Matrix init1 = random_matrix(max_value, rows1, cols2);

	Matrix sub = matrix_sub(&init , &init1);
	Matrix add = matrix_add(&init , &init1);
	Matrix mult = matrix_multiplication(&init , &init1);
	Matrix T1 = Transpose(&init);
	Matrix T2 = Transpose(&init1);
	Matrix add1 = matrix_add(&T1 , &T2);
	Matrix T3 = Transpose(&add);
	Matrix originit = Transpose(&init);
	Matrix originit2 = Transpose(&originit);

	MATRIX_PRINT(init);
	MATRIX_PRINT(init1);
	MATRIX_PRINT(sub);
	MATRIX_PRINT(add);
	MATRIX_PRINT(mult);
	MATRIX_PRINT(T1);
	MATRIX_PRINT(T2);
	MATRIX_PRINT(add1);
	MATRIX_PRINT(T3);
	MATRIX_PRINT(originit2);
	TEST_MATRIX(add1 , T3);

	unload(&init);
	unload(&init1);
	unload(&sub);
	unload(&add);
	unload(&mult);
	unload(&T1);
	unload(&T2);
	unload(&add1);
	unload(&T3);
	unload(&originit);
	unload(&originit2);
	return 0;
}
