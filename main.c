#include "matrix.h"

int main(int argc , char **argv)
{

	if (argc != 2)
	{
		printf("Usage: %s <max value for your matrix values>.\n", argv[0]);
		return 1;
	}

	int cols;
	printf("Cols: ");
	scanf("%d", &cols);

	int rows;
	printf("Rows: ");
	scanf("%d", &rows);
	printf("\n");

	Matrix init  = random_matrix( (size_t) atoi(argv[1]), rows , cols);
	Matrix init1 = random_matrix( (size_t) atoi(argv[1]), rows , cols);

	Matrix sub = matrix_sub(&init , &init1);
	Matrix add = matrix_add(&init , &init1);
	Matrix mult = matrix_multiplication(&init , &init1);
	Matrix T = Transpose(&init);
	Matrix dot1 = matrix_multiplication(&T , &init1 );

	MATRIX_PRINT(init);
	MATRIX_PRINT(init1);
	MATRIX_PRINT(sub);
	MATRIX_PRINT(add);
	MATRIX_PRINT(mult);
	MATRIX_PRINT(T);
	MATRIX_PRINT(dot1);

	unload(&init);
	unload(&init1);
	unload(&sub);
	unload(&add);
	unload(&mult);
	unload(&T);
	unload(&dot1);
	return 0;
}
