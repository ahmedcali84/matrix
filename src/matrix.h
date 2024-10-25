#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

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

MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col);                                        // Get Specific Element from the Matrix
MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value);                            // Set a specific element from the matrix to a new value
MATDEF Matrix RANDOM_MATRIX(size_t nrows, size_t ncols);                                           // Generates random Matrix(nrows x ncols)
MATDEF void PRINT_MATRIX(Matrix B, const char *name);                                              // Prints a Matrix
MATDEF int MATRIX_SHAPE(Matrix A, const char *name);                                               // Prints the SHAPE of the matrix
MATDEF Matrix MATRIX_ADD(Matrix *A, Matrix *B);                                                    // Adds two Matrices
MATDEF Matrix MATRIX_SUBTRACT(Matrix *A, Matrix *B);                                               // Subtracts two Matrices
MATDEF Matrix HADAMARD_PRODUCT(Matrix *A, Matrix *B);                                              // Computes Element-wise Product of Two Matrices
MATDEF Matrix* DOT_PRODUCT(Matrix *A, Matrix *B);                                                  // Computes the Dot-Product of two Matrices
MATDEF Matrix TRANSPOSE(Matrix *A);                                                                // Return TRANSPOSE of Matrix A
MATDEF bool TEST_MATRIX_EQUAL(Matrix A, Matrix B, char *matrix_a, char *matrix_b);                 // Test Matrices for equality
MATDEF Matrix FILL(size_t nrows, size_t ncols, float FILL_value);                                  // Creates A Matrix filled with a specific value (For Development Purposes)
MATDEF Matrix EXPECTED_MATRIX(size_t nrows, size_t ncols, float value);                            // Returns the doubled-version of created Matrix (For Development Purposes)
MATDEF float MSE(float pred, float Y);                                                             // Cost Function (CALCULATES MEAN SQUARE ERROR)
MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha);  // Linear REGRESSION
MATDEF void UNLOAD(Matrix *B);                                                                     // Function to free Allocated Memory

// Special Macro Functions
#define PRINT(B) PRINT_MATRIX(B, #B)                                                               // Macro definition of a special print function
#define SHAPE(A) MATRIX_SHAPE(A, #A)                                                               // Macro definition of a special SHAPE printing function
#define TEST_MATRIX(A, B) TEST_MATRIX_EQUAL(A, B, #A, #B)                                          // Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix


/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/

MATDEF float GET_ELEMENT(Matrix C, size_t row, size_t col)
{
    // Check for valid indices
    if (row >= C.nrows || col >= C.ncols) {
        fprintf(stderr, "Index out of bounds: [%zu, %zu] for matrix size [%zu, %zu]\n",
                row, col, C.nrows, C.ncols);
        exit(EXIT_FAILURE); // Handle the error, exit or return an error value
    }
    
    // Retrieve an element from the matrix at the specified row and column
    return C.A[row * C.ncols + col];
}

MATDEF void SET_ELEMENT(Matrix C, size_t row, size_t col, float value)
{
    // Set the element at the specified row and column to a new value
    C.A[row * C.ncols + col] = value;
}

MATDEF Matrix RANDOM_MATRIX(size_t nrows, size_t ncols)
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
            A[index] = (float)rand() / RAND_MAX * 20.0f - 10.0f; // random values between -1 and 1
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

MATDEF Matrix HADAMARD_PRODUCT(Matrix *A, Matrix *B)
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

MATDEF Matrix* DOT_PRODUCT(Matrix *A, Matrix *B)
{
    // Check if the matrices can be multiplied
    if (A->ncols != B->nrows) 
    {
        fprintf(stderr, "Cannot Multiply A->ncols( %zu ) != B->nrows( %zu ).\n", A->ncols, B->nrows);
        exit(EXIT_FAILURE);
    }

    // Initialize a new matrix for the result
    Matrix *C = malloc(sizeof(Matrix));

    C->nrows = A->nrows;
    C->ncols = B->ncols;
    C->A = malloc(sizeof(float) * C->nrows * C->ncols);

    // Check for memory allocation failure
    if (C->A == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the dot product
    for (int i = 0; i < (int)C->nrows; i++)
    {
        for (int j = 0; j < (int)C->ncols; j++)
        {
            C->A[i * C->ncols + j] = 0; // Initialize to zero
            for (int k = 0; k < (int)A->ncols; k++)
            {
                C->A[i * C->ncols + j] += A->A[i * A->ncols + k] * B->A[k * B->ncols + j]; // Sum products
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

MATDEF Matrix FILL(size_t nrows, size_t ncols, float FILL_value)
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
    {
        for (size_t j = 0; j < ncols; j++)
        {
            A.A[i * ncols + j] = FILL_value; // Set all elements
        }
    }
    return A; // Return the filled matrix
}

MATDEF Matrix EXPECTED_MATRIX(size_t nrows, size_t ncols, float value)
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
    {
        for (size_t j = 0; j < ncols; j++)
        {
            A.A[i * ncols + j] = (value * (value + j)); // Set all elements
        }
    }
    return A; // Return the filled matrix
}

MATDEF float MSE(float pred, float Y)
{
    // Calculate mean square error
    return powf(pred - Y, 2); // Return the square of the difference
}

MATDEF void REGRESSION(int epochs, Matrix X, Matrix Ws, Matrix bias, Matrix actual, float alpha)
{
    // Calculate initial predictions by performing the dot product of weights and input features
    Matrix *pred = DOT_PRODUCT(&X, &Ws);

    // Print initial predictions Before Bias
    printf("Initial Predictions Before Bias: ");
    PRINT(*pred);

    // Add bias to each prediction
    for (size_t i = 0; i < pred->nrows; ++i) 
    {
        for (size_t j = 0; j < pred->ncols; ++j) 
        {
            size_t index = i * pred->ncols + j;
            pred->A[index] += GET_ELEMENT(bias, 0, 0); // Add bias to each prediction
        }
    }
    
    // Print initial predictions After Bias
    printf("Initial Predictions After Bias: ");
    PRINT(*pred);

    // Main loop for the number of epochs
    for (int epoch = 0; epoch < epochs; ++epoch)
    {
        float total_cost = 0.0;
        // Update weights for each feature
        for (size_t i = 0; i < Ws.nrows; ++i)
        {
            for (size_t j = 0; j < Ws.ncols; ++j)
            {
                float w = GET_ELEMENT(Ws, i, j); // Retrieve the current weight
                float b = GET_ELEMENT(bias, 0, j); // Retrieve the current bias

                float gradient_w = 0.0f; // Initialize gradient for this weight
                float gradient_b = 0.0f; // Initialize gradient for this bias

                // Calculate gradients based on predictions and actual values
                for (size_t k = 0; k < pred->nrows; ++k)
                {
                    for (size_t m = 0; m < pred->ncols; ++m)
                    {
                        size_t index_pred = k * pred->ncols + m;
                        size_t index_actual = k * actual.ncols + m; // Adjust according to actual dimensions
                        
                        if (index_pred < pred->nrows * pred->ncols && index_actual < actual.nrows * actual.ncols) // Ensure indices are valid
                        {
                            // Calculate the error between actual and predicted values
                            float error = actual.A[index_actual] - pred->A[index_pred];
                            // Accumulate the gradient for the weight
                            gradient_w += (-2 * error * GET_ELEMENT(X, k, j)); // X index based on row k
                            gradient_b += (-2 * error); // bias doesnn't depend on X

                            // Accumulate the total cost (Mean Squared Error)
                            total_cost += error * error;
                        }
                    }
                }
                // Update the weight using gradient descent
                w = w - alpha * gradient_w;
                SET_ELEMENT(Ws, i, j, w); // Set the new weight

                b = b - alpha * gradient_b;
                SET_ELEMENT(bias, 0, j, b); // Set the new weight
            }
        }

        // Recalculate predictions after updating weights
        Matrix *new_pred = DOT_PRODUCT(&X, &Ws);
        
        // Add bias to the new predictions
        for (size_t i = 0; i < new_pred->nrows; ++i) 
        {
            for (size_t j = 0; j < new_pred->ncols; ++j) 
            {
                size_t index = i * new_pred->ncols + j;
                new_pred->A[index] += GET_ELEMENT(bias, 0, 0);
            }
        }
        
        // Unload the old predictions
        UNLOAD(pred);
        pred = new_pred; // Update predictions with the new values

        // Compute average total cost
        total_cost /= (pred->nrows * pred->ncols); 

        // Print cost and predictions at each epoch
        if (epoch % 10 == 0 || epoch == epochs - 1)
        {
            for (size_t i = 0; i < pred->nrows; ++i)
            {
                for (size_t j = 0; j < pred->ncols; ++j)
                {
                    size_t index = i * pred->ncols + j;
                    if (index < pred->nrows * pred->ncols) // Ensure index is valid
                    {
                        // Calculate and print the Mean Squared Error (MSE), predicted value, and actual value
                        printf("Epoch =  %d, Cost = %f, Pred: %f, Actual = %f\n", 
                               epoch, total_cost, 
                               pred->A[index], actual.A[index]);
                    }
                }
            }
        }
    }
    
    // Print final predictions after training
    // PRINT(*pred);
    UNLOAD(pred); // Clean up memory for predictions
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
