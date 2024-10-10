#include "matrix.h"
#include <time.h>

#define MAX_VALUE 4

int main(int argc , char **argv)
{
	srand(time(NULL));
	int max_value;

	if (argc != 2)
	{
		printf("Usage: %s <max-value>.\n", argv[0]);
		max_value = MAX_VALUE;
	}
	else
	{
		max_value = atoi(argv[1]);
	}

	printf("Max value is: %d\n", max_value);

	Matrix V1 = random_matrix(max_value , 2 , 2);
	Matrix V2 = random_matrix(max_value , 2 , 2);
	Matrix V2_T  = Transpose(&V2);
	Matrix Add = matrix_add(&V1, &V2);

	Matrix V1_V2_T_dot = dot_product(&V1 , &V2_T);
	Matrix V2_V2_T_dot = dot_product(&V2 , &V2_T);
	Matrix C = dot_product(&V1, &V2);

	PRINT(V1);
	PRINT(V2);
	PRINT(V2_T);
	PRINT(V1_V2_T_dot);
	PRINT(V2_V2_T_dot);
	PRINT(Add);
	PRINT(C);

	SHAPE(C);

	unload(&V1);
	unload(&V2);
	unload(&V2_T);
	unload(&V1_V2_T_dot);
	unload(&V2_V2_T_dot);
	unload(&Add);
	unload(&C);

	return 0;
}

