#include "matrix.h"
#include <assert.h>
#include <stdio.h>

typedef struct 
{
    void (*test_function)(void); // Pointer to the test function
    const char *name;            // Name of the test case
} Test_Case;

// TEST for GET_ELEMENT
void TEST_GET_ELEMENT() 
{
    Matrix A = FILL(2, 3, 5);  // FILL a 2x3 Matrix with value 5
    float element = GET_ELEMENT(A, 1, 2);  // Should get 5
    assert(element == 5);
    UNLOAD(&A);
}

// TEST for SET_ELEMENT
void TEST_SET_ELEMENT() 
{
    Matrix A = FILL(2, 3, 0);  // FILL a 2x3 Matrix with value 0
    SET_ELEMENT(A, 1, 2, 7);  // Set element (1, 2) to 7
    assert(GET_ELEMENT(A, 1, 2) == 7);
    UNLOAD(&A);
}

// TEST for RANDOM_MATRIX
void TEST_RANDOM_MATRIX() 
{
    Matrix A = RANDOM_MATRIX(10, 2, 2);  // Create a 2x2 Matrix with Random elements [0, 10]
    assert(A.nrows == 2 && A.ncols == 2);
    UNLOAD(&A);
}

// TEST for PRINT_Matrix
void TEST_PRINT_Matrix() 
{
    Matrix A = FILL(2, 2, 3);  // Create a 2x2 Matrix with value 3
    // Removed PRINT(A);  // Do not print the Matrix
    UNLOAD(&A);
}

// TEST for SHAPE
void TEST_SHAPE() 
{
    Matrix A = FILL(3, 4, 1);  // Create a 3x4 Matrix
    int result = SHAPE(A);  // Should PRINT (3, 4)
    assert(result == 0);
    UNLOAD(&A);
}

// TEST for MATRIX_ADD
void TEST_MATRIX_ADD() 
{
    Matrix A = FILL(2, 2, 5);  // Create 2x2 Matrix with value 5
    Matrix B = FILL(2, 2, 3);  // Create 2x2 Matrix with value 3
    Matrix C = MATRIX_ADD(&A, &B);  // C should be [8, 8; 8, 8]
    assert(GET_ELEMENT(C, 0, 0) == 8);
    assert(GET_ELEMENT(C, 1, 1) == 8);
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for MATRIX_SUBTRACT
void TEST_MATRIX_SUBTRACT() 
{
    Matrix A = FILL(2, 2, 7);  // Create 2x2 Matrix with value 7
    Matrix B = FILL(2, 2, 4);  // Create 2x2 Matrix with value 4
    Matrix C = MATRIX_SUBTRACT(&A, &B);  // C should be [3, 3; 3, 3]
    assert(GET_ELEMENT(C, 0, 0) == 3);
    assert(GET_ELEMENT(C, 1, 1) == 3);
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for HAMADARD_PRODUCT
void TEST_HAMADARD_PRODUCT() 
{
    Matrix A = FILL(2, 2, 2);  // Create 2x2 Matrix with value 2
    Matrix B = FILL(2, 2, 3);  // Create 2x2 Matrix with value 3
    Matrix C = HAMADARD_PRODUCT(&A, &B);  // C should be [6, 6; 6, 6]
    assert(GET_ELEMENT(C, 0, 0) == 6);
    assert(GET_ELEMENT(C, 1, 1) == 6);
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for DOT_PRODUCT
void TEST_DOT_PRODUCT() 
{
    Matrix A = FILL(2, 3, 1);  // 2x3 Matrix
    Matrix B = FILL(3, 2, 2);  // 3x2 Matrix
    Matrix C = DOT_PRODUCT(&A, &B);  // Should be [6, 6; 6, 6]
    assert(C.nrows == 2 && C.ncols == 2);
    assert(GET_ELEMENT(C, 0, 0) == 6);
    assert(GET_ELEMENT(C, 1, 1) == 6);
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for TRANSPOSE
void TEST_TRANSPOSE() 
{
    Matrix A = FILL(2, 3, 1);  // 2x3 Matrix
    Matrix C = TRANSPOSE(&A);  // Should be 3x2 Matrix
    assert(C.nrows == 3 && C.ncols == 2);
    assert(GET_ELEMENT(C, 0, 1) == 1);
    UNLOAD(&A); UNLOAD(&C);
}

// TEST for TEST_MATRIX
void TEST_TEST_MATRIX() 
{
    Matrix A = FILL(2, 2, 5);  // 2x2 Matrix with value 5
    Matrix B = FILL(2, 2, 5);  // 2x2 Matrix with value 5
    assert(TEST_MATRIX(A, B) == true);  // Should return true
    UNLOAD(&A); UNLOAD(&B);
}

// TEST for MSE
void TEST_MSE() 
{
    float pred = 2.5;
    float Y = 2.0;
    assert(MSE(pred, Y) == 0.25);  // Error squared should be 0.25
}

// TEST for REGRESSION
void TEST_REGRESSION() 
{
    Matrix X = FILL(2, 2, 1);    // 2x2 input Matrix
    Matrix Ws = FILL(2, 2, 0.1); // Initial weights
    Matrix bias = FILL(1, 2, 0); // Bias
    Matrix actual = FILL(2, 2, 5);  // Actual output
    REGRESSION(10, X, Ws, bias, actual, 0.1);  // TEST simple REGRESSION
    UNLOAD(&X); UNLOAD(&Ws); UNLOAD(&bias); UNLOAD(&actual);
}

// TEST for UNLOAD
void TEST_UNLOAD() 
{
    Matrix A = FILL(2, 2, 5);  // Create a 2x2 Matrix
    UNLOAD(&A);  // Free memory
    assert(A.A == NULL);  // Ensure memory is freed
}

void run_tests(Test_Case test_cases[], size_t num_tests) 
{
    for (size_t i = 0; i < num_tests; i++) 
	{
        Test_Case test = test_cases[i];
        test.test_function();  // Run the test
        printf("TEST %s passed.\n", test.name);  // Print the success message
    }
}

int main() 
{
    Test_Case tests[] = {
        {TEST_GET_ELEMENT, "GET_ELEMENT"},
        {TEST_SET_ELEMENT, "SET_ELEMENT"},
        {TEST_RANDOM_MATRIX, "RANDOM_MATRIX"},
        {TEST_PRINT_Matrix, "PRINT_Matrix"},
        {TEST_SHAPE, "SHAPE"},
        {TEST_MATRIX_ADD, "MATRIX_ADD"},
        {TEST_MATRIX_SUBTRACT, "MATRIX_SUBTRACT"},
        {TEST_HAMADARD_PRODUCT, "HAMADARD_PRODUCT"},
        {TEST_DOT_PRODUCT, "DOT_PRODUCT"},
        {TEST_TRANSPOSE, "TRANSPOSE"},
        {TEST_TEST_MATRIX, "TEST_MATRIX"},
        {TEST_MSE, "MSE"},
        {TEST_REGRESSION, "REGRESSION"},
        {TEST_UNLOAD, "UNLOAD"}
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, num_tests);  // Run all test cases
    return 0;
}