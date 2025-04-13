#include "../src/matrix.h"
#include <assert.h>
#include <time.h>

typedef struct _test_cases {
    const char *name;
    void (*test_function)(void);
} Test_Case;

#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

void run_tests(Test_Case test_cases[], unsigned int num_tests)
{
    for (unsigned int i = 0; i < num_tests; ++i) {
        test_cases[i].test_function();
        printf("    INFO: Test [%d]: \"%s\" passed.\n", i + 1, test_cases[i].name);
    }
}

void TEST_RANDOM_MATRIX()
{
    Matrix A = random_matrix(1000, 500);
    assert(A.A != NULL && "ERROR: Test Random Matrix Failed.\n");
    unload(&A);
}

void TEST_MATRIX_ADDITION()
{
    Matrix A = fill(100, 50, 100.0);
    Matrix B = fill(100, 50, 100.0);
    
    Matrix C = matrix_add(&A, &B);
    double value = get_element(C, 0, 0);
    assert(value == 200.0 && "ERROR: Test Matrix Addition Failed.\n");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

void TEST_MATRIX_SUBTRACTION()
{
    Matrix A = fill(100, 50, 100.0);
    Matrix B = fill(100, 50, 50.0);
    
    Matrix C = matrix_subtract(&A, &B);
    double value = get_element(C, 0, 0);
    assert(value == 50.0 && "ERROR: Test Matrix Addition Failed.\n");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

int main(void)
{
    srand(time(NULL));
    printf("INFO: Testing Matrix Functions...\n");
    Test_Case test_cases[] = {
        {"TEST MATRIX RANDOM",      TEST_RANDOM_MATRIX},
        {"TEST MATRIX ADDITION",    TEST_MATRIX_ADDITION},
        {"TEST MATRIX SUBTRACTION", TEST_MATRIX_SUBTRACTION},
    };
    
    unsigned int num_tests = ARRAY_LEN(test_cases);
    run_tests(test_cases, num_tests);

    printf("INFO: Testing for Matrix functions Done.\n\n");
    return 0;
}
