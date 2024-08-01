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

	Matrix input = random_matrix(max_value , 5, 5);
	Matrix weights = random_matrix(max_value, 5 , 5);
	Matrix expected =  expected_matrix(&input);
	Matrix output = dot_product(&input , &weights);

    // Print the output
	printf("Initial Values\n");
	MATRIX_PRINT(input);
    MATRIX_PRINT(weights);
	MATRIX_PRINT(expected);
	MATRIX_PRINT(output);

	double learning_rate = 0.0001;
	int epochs = 1000000;
	int max = 100000;
	train(&input , &weights , &expected , epochs , learning_rate , max);

    // Free allocated memory
	Matrix Test = random_matrix(max_value ,5 , 5);
	Matrix True =  expected_matrix(&Test);
	Matrix predicted = dot_product(&Test , &weights);

	MATRIX_PRINT(Test);
	MATRIX_PRINT(True);
	MATRIX_PRINT(predicted);
	MATRIX_PRINT(weights);

	unload(&input);
	unload(&weights);
	unload(&expected);
	unload(&output);
	unload(&Test);
	unload(&True);
	unload(&predicted);
	return 0;
}

