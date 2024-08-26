#include "matrix.h"
#include <time.h>

int main(int argc , char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <max-value>.\n",argv[0]);
		return 1;
	}

	srand(time(NULL));

	int max_value = atoi(argv[1]);

	Matrix V1 = random_matrix(max_value , 1 , 3);
	Matrix V2 = random_matrix(max_value , 1 , 3);
	Matrix V2_T  = Transpose(&V2);

	// Matrix V1_V2_dot = dot_product(&V1 , &V2);
	Matrix V1_V2_T_dot = dot_product(&V1 , &V2_T);
	Matrix V2_V2_T_dot = dot_product(&V2 , &V2_T);

	MATRIX_PRINT(V1);
	MATRIX_PRINT(V2);
	MATRIX_PRINT(V2_T);
	// MATRIX_PRINT(V1_V2_dot);
	MATRIX_PRINT(V1_V2_T_dot);
	MATRIX_PRINT(V2_V2_T_dot);

	unload(&V1);
	unload(&V2);
	unload(&V2_T);
	// unload(&V1_V2_dot);
	unload(&V1_V2_T_dot);
	unload(&V2_V2_T_dot);

	return 0;
}

