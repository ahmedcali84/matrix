#include <matrix.h>
#include <assert.h>
#include <time.h>

typedef struct
{
    void (*test_function)(void); // Pointer to the test function
    const char *name;            // Name of the test case
} Test_Case;


// TEST for GET_ELEMENT
void TEST_GET_ELEMENT() {
    float a = 5.0f;
    Matrix A = FILL(2, 3, sizeof(float), TYPE_FLOAT, &a); // Create a 2x3 matrix filled with 5.0

    // Valid access
    float b;
    GET_ELEMENT(A, 1 , 2 , &b);
    // printf("%lf\n", b);
    assert(b == 5 && "TEST_GET_ELEMENT failed: Expected 5.0");
    UNLOAD(&A); // Clean up
}

// TEST for SET_ELEMENT
void TEST_SET_ELEMENT()
{
    float a = 0;
    Matrix A = FILL(2, 3, sizeof(float), TYPE_FLOAT, &a); // Fill a 2x3 Matrix with value 0
    float c = 7;
    SET_ELEMENT(A, 1, 2, &c);  // Set element (1, 2) to 7

    float b;
    GET_ELEMENT(A, 1 , 2 , &b);
    assert(b == 7 && "SET_ELEMENT failed: expected 7");
    UNLOAD(&A); // Clean up
}

// TEST for RANDOM_MATRIX
void TEST_RANDOM_MATRIX()
{
    Matrix A = RANDOM_MATRIX(2, 2, sizeof(float), TYPE_FLOAT);  // Create a 2x2 Matrix with Random elements [0, 10]
    assert(((A.nrows == 2 && A.ncols == 2) || (A.type == TYPE_FLOAT)) && "RANDOM_MATRIX failed: unexpected dimensions");
    for (size_t i = 0; i < A.nrows; i++) {
        for (size_t j = 0; j < A.ncols; j++) { 
            float a;
            GET_ELEMENT(A, i, j, &a);
            assert((a >= -10 && a < 20) && "RANDOM_MATRIX failed: values out of expected range");
        }
    }

    UNLOAD(&A);
}

// TEST for PRINT_MATRIX
void TEST_PRINT_MATRIX()
{
    float a;
    a = 3;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // Create a 2x2 Matrix with value 3
    for (size_t i = 0; i < A.nrows; i++)
    {
        for (size_t j = 0; j < A.ncols; j++)
        {
            float a;
            GET_ELEMENT(A, i, j, &a);
            assert(a == 3 && "RANDOM_MATRIX failed: values out of expected range");
        }
    }
    PRINT(A);
    UNLOAD(&A);
}

// TEST for SHAPE
void TEST_SHAPE()
{
    float a = 1;
    Matrix A = FILL(3, 4, sizeof(float), TYPE_FLOAT, &a);  // Create a 3x4 Matrix
    int result = SHAPE(A);  // Get shape
    assert(result == 0 && "SHAPE failed: expected result to be a zero value");
    UNLOAD(&A);
}

// TEST for MATRIX_ADD
void TEST_MATRIX_ADD()
{
    float a = 5;
    float b = 3;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // Create 2x2 Matrix with value 5
    Matrix B = FILL(2, 2, sizeof(float), TYPE_FLOAT, &b);  // Create 2x2 Matrix with value 3
    Matrix C = MATRIX_ADD(&A, &B);  // C should be [8, 8; 8, 8]
    float c;
    float d;
    GET_ELEMENT(C, 0 , 0 , &c);
    GET_ELEMENT(C, 1 , 1 , &d);
    //PRINT(A);
    //PRINT(B);
    //PRINT(C);
    assert(fabs(c - 8.0) < 1e-6 && "MATRIX_ADD failed: expected 8 at (0, 0)");
    assert(fabs(c - 8.0) < 1e-6 && "MATRIX_ADD failed: expected 8 at (1, 1)");
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for MATRIX_SUBTRACT
void TEST_MATRIX_SUBTRACT()
{
    float a = 7;
    float b = 4;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // Create 2x2 Matrix with value 7
    Matrix B = FILL(2, 2, sizeof(float), TYPE_FLOAT, &b);  // Create 2x2 Matrix with value 4
    Matrix C = MATRIX_SUBTRACT(&A, &B);  // C should be [3, 3; 3, 3]
    float c;
    float d;
    GET_ELEMENT(C, 0 , 0 , &c);
    GET_ELEMENT(C, 1 , 1 , &d);
    assert(fabs(c - 3) < 1e-6 && "MATRIX_SUBTRACT failed: expected 3 at (0, 0)");
    assert(fabs(d - 3) < 1e-6 && "MATRIX_SUBTRACT failed: expected 3 at (1, 1)");
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for HADAMARD_PRODUCT
void TEST_HADAMARD_PRODUCT()
{
    float a = 2;
    float b = 3;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // Create 2x2 Matrix with value 2
    Matrix B = FILL(2, 2, sizeof(float), TYPE_FLOAT, &b);  // Create 2x2 Matrix with value 3
    Matrix C = HADAMARD_PRODUCT(&A, &B);  // C should be [6, 6; 6, 6]
    float c;
    float d;
    GET_ELEMENT(C, 0 , 0 , &c);
    GET_ELEMENT(C, 1 , 1 , &d);
    assert(c == 6 && "HADAMARD_PRODUCT failed: expected 6 at (0, 0)");
    assert(d == 6 && "HADAMARD_PRODUCT failed: expected 6 at (1, 1)");
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for DOT_PRODUCT
void TEST_DOT_PRODUCT()
{
    float a = 1;
    float b = 2;
    Matrix A = FILL(2, 3, sizeof(float), TYPE_FLOAT, &a);  // Create 2x3 Matrix with value 1
    Matrix B = FILL(3, 2, sizeof(float), TYPE_FLOAT, &b);  // Create 3x2 Matrix with value 2
    //PRINT(A); 
    //PRINT(B);
    Matrix C = DOT_PRODUCT(&A, &B);  // Should be [6, 6; 6, 6]
    float c, d;
    GET_ELEMENT(C, 0 , 0 , &c);
    GET_ELEMENT(C, 1 , 1 , &d);
    //PRINT(C);
    assert(fabs(c - 6) < 1e-6 && "DOT_PRODUCT failed: expected 6 at (0, 0)");
    assert(fabs(d - 6) < 1e-6 && "DOT_PRODUCT failed: expected 6 at (1, 1)");
    UNLOAD(&A); UNLOAD(&B); UNLOAD(&C);
}

// TEST for TRANSPOSE
void TEST_TRANSPOSE()
{
    float a = 1;
    Matrix A = FILL(2, 3, sizeof(float), TYPE_FLOAT, &a);  // 2x3 Matrix
    Matrix C = TRANSPOSE(&A);  // Should be 3x2 Matrix
    assert(C.nrows == 3 && C.ncols == 2 && "TRANSPOSE failed: unexpected dimensions");
    float b;
    GET_ELEMENT(C, 0 , 1 , &b);
    assert(b == 1 && "TRANSPOSE failed: expected 1 at (0, 1)");
    UNLOAD(&A); UNLOAD(&C);
}

// TEST for TEST_MATRIX
void TEST_TEST_MATRIX()
{
    float a = 5;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // 2x2 Matrix with value 5
    Matrix B = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // 2x2 Matrix with value 5
    assert(TEST_MATRIX(A, B) == true && "TEST_MATRIX failed: expected true");
    UNLOAD(&A); UNLOAD(&B);
}

// TEST for UNLOAD
void TEST_UNLOAD()
{
    float a = 5;
    Matrix A = FILL(2, 2, sizeof(float), TYPE_FLOAT, &a);  // Create a 2x2 Matrix
    UNLOAD(&A);  // Free memory
    assert(A.A == NULL && "UNLOAD failed: memory not freed");
}

void run_tests(Test_Case test_cases[], size_t num_tests)
{
    for (size_t i = 0; i < num_tests; i++)
    {
        Test_Case test = test_cases[i];
        test.test_function();  // Run the test
        printf("[TEST %zu]: %s passed.\n",i+1, test.name);  // Print the success message
    }
}

int main()
{
    srand(time(NULL));
    Test_Case tests[] = {
        {TEST_GET_ELEMENT, "GET_ELEMENT"},
        {TEST_SET_ELEMENT, "SET_ELEMENT"},
        {TEST_RANDOM_MATRIX, "RANDOM_MATRIX"},
        {TEST_PRINT_MATRIX, "PRINT_MATRIX"},
        {TEST_SHAPE, "SHAPE"},
        {TEST_MATRIX_ADD, "MATRIX_ADD"},
        {TEST_MATRIX_SUBTRACT, "MATRIX_SUBTRACT"},
        {TEST_HADAMARD_PRODUCT, "HADAMARD_PRODUCT"},
        {TEST_DOT_PRODUCT, "DOT_PRODUCT"},
        {TEST_TRANSPOSE, "TRANSPOSE"},
        {TEST_TEST_MATRIX, "TEST_MATRIX"},
        {TEST_UNLOAD, "UNLOAD"},
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    run_tests(tests, num_tests);  // Run all tests
    return 0;
}
