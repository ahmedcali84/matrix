#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#define MATDEF static // Define a macro for static functions

// Matrix Structure and Information
typedef struct Matrix
{
    float *A;         // Pointer to the array of matrix elements
    size_t nrows;     // Number of rows in the matrix
    size_t ncols;     // Number of columns in the matrix
} Matrix;

/*
************** MATRIX OPERATIONS FUNCTIONS DECLARATIONS *******************
*/

// Get Specific Element from the Matrix
MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col);

// Set a specific element from the matrix to a new value
MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value);

// Generates random Matrix(nrows x ncols)
MATDEF Matrix RANDOM_MATRIX(int max, size_t nrows, size_t ncols);

// Prints a Matrix
MATDEF void PRINT_MATRIX(Matrix B, const char *name);

// Macro definition of a special print function
#define PRINT(B) PRINT_MATRIX(B, #B)

// Prints the SHAPE of the matrix
MATDEF int MATRIX_SHAPE(Matrix A, const char *name);

// Macro definition of a special SHAPE printing function
#define SHAPE(A) MATRIX_SHAPE(A, #A)

// Adds two Matrices
MATDEF Matrix MATRIX_ADD(Matrix *A, Matrix *B);

// Subtracts two Matrices
MATDEF Matrix MATRIX_SUBTRACT(Matrix *A, Matrix *B);

// Computes Element-wise Product of Two Matrices
MATDEF Matrix HAMADARD_PRODUCT(Matrix *A, Matrix *B);

// Computes the Dot-Product of two Matrices || Two Vectors || a Vector and a Matrix
MATDEF Matrix DOT_PRODUCT(Matrix *A, Matrix *B);

// Return TRANSPOSE of Matrix A
MATDEF Matrix TRANSPOSE(Matrix *A);

// Test Matrices for equality
MATDEF bool TEST_MATRIX_EQUAL(Matrix A, Matrix B, char *matrix_a, char *matrix_b);

// Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix
#define TEST_MATRIX(A, B) TEST_MATRIX_EQUAL(A, B, #A, #B)

// Creates A Matrix filled with a specific value (For Development Purposes)
MATDEF Matrix FILL(size_t nrows, size_t ncols, size_t FILL_value);

// Returns the doubled-version of created Matrix (For Development Purposes)
MATDEF Matrix EXPECTED_MATRIX(Matrix *input);

// Cost Function (CALCULATES MEAN SQUARE ERROR)
MATDEF float MSE(float pred, float Y);

// Simple Linear REGRESSION
MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha);

// Function to free Allocated Memory
MATDEF void UNLOAD(Matrix *B);

/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/

MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col)
{
    // Retrieve an element from the matrix at the specified row and column
    return C.A[row * C.ncols + col];
}

MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value)
{
    // Set the element at the specified row and column to a new value
    C.A[row * C.ncols + col] = value;
}

MATDEF Matrix RANDOM_MATRIX(int max, size_t nrows, size_t ncols)
{
    // Allocate memory for the matrix elements
    float *A = malloc(sizeof(float) * (nrows * ncols));
    if (A == NULL) {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }

    // Fill the matrix with random values
    for (int i = 0; i < (int)nrows; i++)
    {
        for (int j = 0; j < (int)ncols; j++)
        {
            int index = i * ncols + j;
            A[index] = ((float)rand() / (float)RAND_MAX) * max; // Scale random value
        }
    }

    // Create a Matrix struct with the allocated array
    float *temp = A;
    Matrix dummy = {
        .A = temp,
        .nrows = nrows,
        .ncols = ncols,
    };
    return dummy; // Return the generated matrix
}

MATDEF void PRINT_MATRIX(Matrix B, const char *name)
{
    // Print the matrix with its name
    printf("%s = [\n", name);
    for (int i = 0; i < (int)B.nrows; i++)
    {
        for (int j = 0; j < (int)B.ncols; j++)
        {
            int index = i * B.ncols + j;
            printf(" %f ", B.A[index]); // Print each element
        }
        printf("\n");
    }
    printf("]"); // End of matrix
    printf("\n\n");
}

MATDEF int MATRIX_SHAPE(Matrix A, const char *name)
{
    // Print the shape of the matrix (rows, columns)
    printf("%s(SHAPE: (%d , %d))\n", name, (int)A.nrows, (int)A.ncols);
    return 0; // Return 0 for successful execution
}

MATDEF Matrix MATRIX_ADD(Matrix *A, Matrix *B)
{
    // Initialize a new matrix for the result
    Matrix C = {
        .A = malloc(sizeof(float) * A->nrows * A->ncols),
        .nrows = A->nrows,
        .ncols = A->ncols,
    };

    // Check for memory allocation failure
    if (C.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Check if dimensions match for addition
    if (A->ncols == B->ncols && A->nrows == B->nrows)
    {
        for (int i = 0; i < (int)A->nrows; i++)
        {
            for (int j = 0; j < (int)A->ncols; j++)
            {
                int index = i * A->ncols + j;
                C.A[index] = A->A[index] + B->A[index]; // Element-wise addition
            }
        }
        return C; // Return the result matrix
    }
    else
    {
        UNLOAD(&C); // Free allocated memory on error
        fprintf(stderr, "Dimension Error.\n"); // Print error message
        return *(Matrix *)A; // Return the first matrix (unsuccessful operation)
    }
}

MATDEF Matrix MATRIX_SUBTRACT(Matrix *A, Matrix *B)
{
    // Initialize a new matrix for the result
    Matrix C = {
        .A = malloc(sizeof(float) * A->nrows * A->ncols),
        .nrows = A->nrows,
        .ncols = A->ncols,
    };

    // Check for memory allocation failure
    if (C.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Check if dimensions match for subtraction
    if (A->ncols == B->ncols && A->nrows == B->nrows)
    {
        for (int i = 0; i < (int)A->nrows; i++)
        {
            for (int j = 0; j < (int)A->ncols; j++)
            {
                int index = i * A->ncols + j;
                C.A[index] = A->A[index] - B->A[index]; // Element-wise subtraction
            }
        }
        return C; // Return the result matrix
    }
    else
    {
        UNLOAD(&C); // Free allocated memory on error
        fprintf(stderr, "Dimension Error.\n"); // Print error message
        return *(Matrix *)A; // Return the first matrix (unsuccessful operation)
    }
}

MATDEF Matrix HAMADARD_PRODUCT(Matrix *A, Matrix *B)
{
    // Ensure matrices are of the same size
    assert(A->ncols == B->ncols);
    assert(A->nrows == B->nrows);

    // Initialize a new matrix for the result
    Matrix C = {
        .A = malloc(sizeof(float) * A->nrows * A->ncols),
        .nrows = A->nrows,
        .ncols = A->ncols,
    };

    // Check for memory allocation failure
    if (C.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate element-wise product
    for (int i = 0; i < (int)A->nrows; i++)
    {
        for (int j = 0; j < (int)A->ncols; j++)
        {
            int index = i * A->ncols + j;
            C.A[index] = A->A[index] * B->A[index]; // Element-wise multiplication
        }
    }
    return C; // Return the result matrix
}

MATDEF Matrix DOT_PRODUCT(Matrix *A, Matrix *B)
{
    // Check if the matrices can be multiplied
    if (A->ncols != B->nrows)
    {
        fprintf(stderr, "Cannot Multiply A->ncols( %zu ) != B->nrows( %zu ).\n", A->ncols, B->nrows);
        exit(EXIT_FAILURE);
    }

    // Initialize a new matrix for the result
    Matrix C = {
        .A = malloc(sizeof(float) * A->nrows * B->ncols),
        .nrows = A->nrows,
        .ncols = B->ncols,
    };

    // Check for memory allocation failure
    if (C.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the dot product
    for (int i = 0; i < (int)C.nrows; i++)
    {
        for (int j = 0; j < (int)C.ncols; j++)
        {
            C.A[i * C.ncols + j] = 0; // Initialize to zero
            for (int k = 0; k < (int)A->ncols; k++)
            {
                C.A[i * C.ncols + j] += A->A[i * A->ncols + k] * B->A[k * B->ncols + j]; // Sum products
            }
        }
    }
    return C; // Return the result matrix
}

MATDEF Matrix TRANSPOSE(Matrix *A)
{
    // Initialize a new matrix for the result
    Matrix C = {
        .A = malloc(sizeof(float) * A->nrows * A->ncols),
        .nrows = A->ncols,
        .ncols = A->nrows,
    };

    // Check for memory allocation failure
    if (C.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the transpose
    for (int i = 0; i < (int)A->nrows; i++)
    {
        for (int j = 0; j < (int)A->ncols; j++)
        {
            C.A[j * C.ncols + i] = A->A[i * A->ncols + j]; // Swap indices
        }
    }
    return C; // Return the transposed matrix
}

MATDEF bool TEST_MATRIX_EQUAL(Matrix A, Matrix B, char *matrix_a, char *matrix_b)
{
    // Check if the dimensions match
    if (A.ncols != B.ncols || A.nrows != B.nrows)
    {
        printf("%s and %s are NOT EQUAL: Different Dimensions\n", matrix_a, matrix_b); // Print dimension mismatch
        return false; // Not equal
    }

    // Check if all elements are equal
    for (int i = 0; i < (int)A.nrows; i++)
    {
        for (int j = 0; j < (int)A.ncols; j++)
        {
            if (GET_ELEMENT(A, i, j) != GET_ELEMENT(B, i, j)) // Compare elements
            {
                printf("%s and %s are NOT EQUAL: Values differ at (%d, %d)\n", matrix_a, matrix_b, i, j); // Print mismatch
                return false; // Not equal
            }
        }
    }
    printf("%s and %s are EQUAL\n", matrix_a, matrix_b); // Print equal matrices
    return true; // Equal
}

MATDEF Matrix FILL(size_t nrows, size_t ncols, size_t FILL_value)
{
    // Allocate memory for the matrix
    Matrix A;
    A.nrows = nrows;
    A.ncols = ncols;
    A.A = malloc(sizeof(float) * (nrows * ncols));

    // Check for memory allocation failure
    if (A.A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Fill the matrix with the specified value
    for (size_t i = 0; i < nrows; i++)
        for (size_t j = 0; j < ncols; j++)
            A.A[i * ncols + j] = (float)FILL_value; // Set all elements

    return A; // Return the filled matrix
}

MATDEF Matrix EXPECTED_MATRIX(Matrix *input)
{
    // Return a filled matrix (used for testing)
    return FILL(input->nrows, input->ncols, 1); // Fill with 1
}

MATDEF float MSE(float pred, float Y)
{
    // Calculate mean square error
    return powf(pred - Y, 2); // Return the square of the difference
}

MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha)
{
    // Loop over the specified number of epochs for training
    for (int i = 0; i < epochs; i++)
    {
        Matrix preds = DOT_PRODUCT(&X, &Ws); // Calculate predictions
        preds = MATRIX_ADD(&preds, &bias); // Add bias to predictions

        // Calculate loss and print it
        float loss = 0;
        for (int j = 0; j < (int)preds.nrows; j++)
        {
            loss += MSE(GET_ELEMENT(preds, j, 0), GET_ELEMENT(actual, j, 0)); // Accumulate MSE
        }
        printf("Epoch %d: Loss = %f\n", i + 1, loss / preds.nrows); // Print average loss

        // Update weights and bias based on gradient descent
        for (int j = 0; j < (int)Ws.nrows; j++)
        {
            float gradient = 0;
            for (int k = 0; k < (int)preds.nrows; k++)
            {
                gradient += (GET_ELEMENT(preds, k, 0) - GET_ELEMENT(actual, k, 0)) * GET_ELEMENT(X, k, j); // Calculate gradient
            }
            SET_ELEMENT(Ws, j, 0, GET_ELEMENT(Ws, j, 0) - alpha * (gradient / preds.nrows)); // Update weights
        }
        for (int j = 0; j < (int)bias.nrows; j++)
        {
            float gradient = 0;
            for (int k = 0; k < (int)preds.nrows; k++)
            {
                gradient += (GET_ELEMENT(preds, k, 0) - GET_ELEMENT(actual, k, 0)); // Calculate bias gradient
            }
            SET_ELEMENT(bias, j, 0, GET_ELEMENT(bias, j, 0) - alpha * (gradient / preds.nrows)); // Update bias
        }

        UNLOAD(&preds); // Free allocated memory for predictions
    }
}

MATDEF void UNLOAD(Matrix *B)
{
    // Free allocated memory for the matrix
    if (B->A != NULL)
    {
        free(B->A); // Free the array of elements
        B->A = NULL; // Avoid dangling pointer
    }
    B->nrows = 0; // Reset rows
    B->ncols = 0; // Reset columns
}

#endif // MATRIX_H
