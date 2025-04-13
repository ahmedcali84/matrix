#include "../src/matrix.h"
#include <assert.h>
#include <stdio.h>
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
    Matrix A = random_matrix(4, 4, sizeof(int), TYPE_INT);
    assert((A.A != NULL || A.type == TYPE_DOUBLE) && "ERROR: Test Failed.\n");
    unload(&A);
}

int main(void)
{
    srand(time(NULL));
    
    printf("INFO: Testing Matrix Functions of TYPE INTEGERS....\n");
    Test_Case test_cases[] = {
        {"RANDOM_MATRIX", TEST_RANDOM_MATRIX},
    };
    
    unsigned int num_tests = ARRAY_LEN(test_cases);
    run_tests(test_cases, num_tests);
    
    printf("INFO: Testing for Matrix Functions of TYPE INTEGERS Done.\n\n");
    return 0;
}
