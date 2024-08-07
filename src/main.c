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

	Matrix V1 = random_matrix(max_value , 1 , 20);
	Matrix V2 = random_matrix(max_value , 1 , 20);
	Matrix V_T  = Transpose(&V2);

	Matrix V3_dot = dot_product(&V1 , &V_T);

	MATRIX_PRINT(V1);
	MATRIX_PRINT(V2);
	MATRIX_PRINT(V_T);
	MATRIX_PRINT(V3_dot);

	unload(&V1);
	unload(&V2);
	unload(&V_T);
	unload(&V3_dot);

	return 0;
}

