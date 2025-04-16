#define MATRIX_IMPLEMENTATION
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
        printf("    INFO: Test [%03d]: \"%s\" passed.\n", i + 1, test_cases[i].name);
    }
}

void TEST_RANDOM_MATRIX()
{
    Matrix A = random_matrix(1000, 500);
    assert(A.A != NULL && "ERROR: Test Random Matrix Failed.");
    unload(&A);
}

void TEST_MATRIX_ADDITION()
{
    Matrix A = fill(100, 100, 100.0);
    Matrix B = fill(100, 100, 100.0);
    
    Matrix C = matrix_add(&A, &B);
    float value = get_element(C, 0, 0);
    assert(value == 200.0 && "ERROR: Test Matrix Addition Failed.");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

void TEST_MATRIX_SUBTRACTION()
{
    Matrix A = fill(100, 100, 100.0);
    Matrix B = fill(100, 100, 50.0);
    
    Matrix C = matrix_subtract(&A, &B);
    float value = get_element(C, 0, 0);
    assert(value == 50.0 && "ERROR: Test Matrix Addition Failed.");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

void TEST_HADAMARD_PRODUCT(void)
{
    Matrix A = fill(100, 100, 100.0);
    Matrix B = fill(100, 100, 100.0);

    Matrix C = hadamard_product(&A, &B);
    float value = get_element(C, 0, 0);
    assert(value == 10000.0 && "ERROR: Test Hadamard Product failed.");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

void TEST_DOT_PRODUCT(void)
{
    Matrix A = fill(2, 2, 100.0);
    Matrix B = fill(2, 2, 100.0);

    Matrix C = dot_product(&A, &B);
    float value = get_element(C, 0, 0);
    assert(value == 20000.0 && "ERROR: Dot Product failed.");
    
    unload(&A);
    unload(&B);
    unload(&C);
}

void TEST_GET_ELEMENT(void)
{
    Matrix A = fill(100, 100, 100.0);
    float value = get_element(A, 0, 0);
    assert(value == 100.0 && "ERROR: Test Get Element Failed");
    unload(&A);
}

void TEST_SET_ELEMENT(void)
{
    Matrix A = fill(100, 100, 100.0);
    float value = 200.0;
    set_element(A, 0, 99, value);
    
    float get_value = get_element(A, 0, 99);
    assert(get_value == 200.0 && "ERROR: Test Set Element Failed.");
    unload(&A);
}

void TEST_MATRIX_CREATION(void)
{
    Matrix A = create_matrix(100, 100);
    assert((A.A != NULL || A.ncols == 100 || A.nrows == 100) && "ERROR: Test Matriix Creation failed.");
    unload(&A);
}

void TEST_MATRIX_SHAPE(void)
{
    Matrix A = create_matrix(100, 100);
    Shape shape = matrix_shape(A);
    assert((shape.rows == A.nrows || shape.cols == A.ncols)&& "ERROR: Test Matrix Shape Failed.");
    unload(&A);
}

void TEST_MATRIX_TRANSPOSE(void)
{
    Matrix A = random_matrix(5, 5);
    float value = get_element(A,0, 4);
  
    Matrix C = transpose(&A);
    float value_transposed = get_element(C, 4 , 0);
    assert(value == value_transposed && "ERROR: Test Matrix Transposed Failed.");
    
    unload(&A);
    unload(&C);
}

void TEST_MATRIX_EQUAL(void)
{
    Matrix A = fill(100, 100, 100.0);
    Matrix B = fill(100, 100, 100.0);
    assert(test_matrix_equal(A, B) && "ERROR: Test Matrix Equal Failed.");
    
    unload(&A);
    unload(&B);
}

void TEST_MATRIX_FILL(void)
{
    Matrix A = fill(100, 100, 100.0);
    float value = get_element(A, 0 , 0);
    assert((A.A != NULL || value == 100.0) && "ERROR: Test Matrix Fill Failed");
    unload(&A);
}

void TEST_MATRIX_UNLOAD(void)
{
    Matrix A = random_matrix(100, 100);
    unload(&A);

    assert((A.A == NULL || A.ncols == 0 || A.nrows == 0) && "ERROR: Test Matrix Unload Failed.");
}

int main(void)
{
    srand(time(NULL));
    printf("INFO: Testing Matrix Functions...\n");

    Test_Case test_cases[] = {
        {"TEST MATRIX RANDOM",      TEST_RANDOM_MATRIX},
        {"TEST MATRIX ADDITION",    TEST_MATRIX_ADDITION},
        {"TEST MATRIX SUBTRACTION", TEST_MATRIX_SUBTRACTION},
        {"TEST HADAMARD PRODUCT",   TEST_HADAMARD_PRODUCT},
        {"TEST DOT PRODUCT",        TEST_DOT_PRODUCT},
        {"TEST GET ELEMENT",        TEST_GET_ELEMENT},
        {"TEST SET ELEMENT",        TEST_SET_ELEMENT},
        {"TEST MATRIX CREATION",    TEST_MATRIX_CREATION},
        {"TEST MATRIX SHAPE",       TEST_MATRIX_SHAPE},
        {"TEST MATRIX TRANSPOSE",   TEST_MATRIX_TRANSPOSE},
        {"TEST MATRIX EQUALITY",    TEST_MATRIX_EQUAL},
        {"TEST MATRIX FILL",        TEST_MATRIX_FILL},
        {"TEST MATRIX UNLOAD",      TEST_MATRIX_UNLOAD},
    };
    
    unsigned int num_tests = ARRAY_LEN(test_cases);
    run_tests(test_cases, num_tests);

    printf("INFO: Testing for Matrix functions Done.\nINFO: All Tests Passed.\n\n");
    return 0;
}
