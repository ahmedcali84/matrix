/**
 * @file matrix.h
 * @brief Matrix Library
 *
 * A collection of basic and essential matrix operations for Unix systems.
 *
 * @author Ahmed Ali Mohammed <ahmedcali1984@gmail.com>
 * @version 0.2.0
 * @date April 16, 2025
 */

#ifndef MATRIX_H
#define MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#include <time.h>

// Matrix Structure and Information
typedef struct _matrix {
    float *A;     // Pointer to the array of matrix elements
    size_t nrows; // Number of rows in the matrix
    size_t ncols; // Number of columns in the matrix
} Matrix;

typedef struct _shape {
    size_t rows;
    size_t cols;
} Shape;

/*
************** MATRIX OPERATIONS FUNCTIONS DECLARATIONS *******************
*/

// Core Functions
float get_element(Matrix C, size_t row, size_t col);                      // get specific element from the Matrix
void set_element(Matrix C, size_t row, size_t col, float new_value);      // set a specific element from the Matrix to a new value
Matrix create_matrix(size_t rows, size_t cols);                           // creates an empty Matrix with specified parameters
void unload(Matrix *b);                                                   // Function to free Allocated Memory

// Utility Functions
Matrix random_matrix(size_t nrows, size_t ncols);                         // generates random Matrix(nrows x ncols)
void print_matrix(const Matrix b, const char *name);                      // prints a Matrix
Shape matrix_shape(Matrix A);                                             // returns shape of the Matrix
Matrix fill(size_t nrows, size_t ncols, float fill_value);                // creates a Matrix filled with a specific value

// Operation Functions
Matrix matrix_add(Matrix *a, Matrix *b);                                  // adds two matrices
Matrix matrix_subtract(Matrix *a, Matrix *b);                             // subtracts two matrices
Matrix hadamard_product(Matrix *a, Matrix *b);                            // computes element-wise product of two matrices
Matrix dot_product(Matrix *a, Matrix *b);                                 // computes the dot-product of two matrices
Matrix transpose(Matrix *a);                                              // return transpose of Matrix a
bool test_matrix_equal(Matrix a, Matrix b);                               // test matrices for equality


// Special Macro Functions
#define PRINT(B) print_matrix(B, #B)                                /* Macro definition of a special print function */
#define ALLOCATION_FAILED "Memory Allocation Failed.\n"             /* Return Error String */

/* Macro function For Printing the shape of a Matrix */
#define PRINT_SHAPE(A)\
    do {\
        Shape shape = matrix_shape(*A);\
        printf("Shape: [%zu, %zu]\n", shape.rows, shape.cols);\
    } while (0)

#ifdef __cplusplus
}
#endif

#ifdef MATRIX_IMPLEMENTATION

/*
************** MATRIX OPERATIONS FUNCTIONS IMPLEMENTATIONS *******************
*/

float get_element(Matrix C, size_t row, size_t col) {
    // check for valid indices
    if (row >= C.nrows || col >= C.ncols) {
        fprintf(stderr, "index out of bounds: [%zu, %zu] for Matrix size [%zu, %zu]\n",
                row, col, C.nrows, C.ncols);
        exit(EXIT_FAILURE); // handle the error, exit or return an error value
    }
    
    return C.A[row * C.ncols + col];
}

void set_element(Matrix C, size_t row, size_t col, float new_value) {
    // set the element at the specified row and column to a new value
    C.A[row * C.ncols + col] = new_value;
}

Matrix create_matrix(size_t rows, size_t cols) {
    Matrix create;
    create.nrows = rows;
    create.ncols = cols;
    create.A = calloc(sizeof(float), (rows * cols));
    if (create.A == NULL) {
        fprintf(stderr, ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }

    return create;
}

Matrix random_matrix(size_t nrows, size_t ncols) {
    // initialize the Matrix
    Matrix random = create_matrix(nrows, ncols);

    // fill the Matrix with random values
    for (size_t i = 0; i < random.nrows; ++i) {
        for (size_t j = 0; j < random.ncols; ++j) {
            float v = ((float)rand() / RAND_MAX) * 1000 - 500;
            set_element(random, i , j , v);
        }
    }

    return random; // return the generated Matrix
}

void print_matrix(const Matrix b, const char *name) {
    // print the Matrix with its name
    printf("%s = [\n", name);

    for (size_t i = 0; i < b.nrows; ++i) {
        for (size_t j = 0; j < b.ncols; ++j) {
            float value = get_element(b, i , j);
            printf(" %.2f ", value);
        }
        printf("\n");
    }
    printf("]"); // end of Matrix
    printf("\n\n");
}

Shape matrix_shape(Matrix A) {
    // shape of the Matrix (rows, columns)
    Shape shape = {.rows = A.nrows, .cols = A.ncols};
    return shape;
}

Matrix matrix_add(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows) && "addition failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);
    
    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            float a = get_element(*A, i , j);
            float b = get_element(*B, i , j);
            float c = a + b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result Matrix
}

Matrix matrix_subtract(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows) && "subtraction failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);

    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            float a = get_element(*A, i , j);
            float b = get_element(*B, i , j);
            float c = a - b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result
}

Matrix hadamard_product(Matrix *A, Matrix *B) {
    // ensure matrices are of the same size and type
    assert(A->ncols == B->ncols && "matrices dimensions mismatch");
    assert(A->nrows == B->nrows && "matrices dimensions mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);

    // calculate element-wise product
    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            float a , b , c;
            a = get_element(*A, i , j);
            b = get_element(*B, i , j);
            c = a * b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result Matrix
}

Matrix dot_product(Matrix *A, Matrix *B) {
    // check if the matrices can be multiplied
    assert((A->ncols == B->nrows) && "error multiplying: dimensions mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, B->ncols);

    // calculate the dot product
    for (size_t i = 0; i < C.nrows; ++i) {
        for (size_t j = 0; j < C.ncols; ++j) {
            float c = 0;
            for (size_t k = 0; k < A->ncols; ++k) {
                float a , b;
                a = get_element(*A, i , k );
                b = get_element(*B, k , j );
                c += a * b;
            }
            set_element(C , i , j , c);
        }
    }

    return C; // return the result Matrix
}

Matrix transpose(Matrix *A) {
    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->ncols, A->nrows);

    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            float a;
            a = get_element(*A, i , j);
            set_element(C, j , i , a);
        }
    }

    return C; // return the transposed Matrix
}

bool test_matrix_equal(Matrix A, Matrix B) {
    // check if the dimensions match
    assert(((A.ncols == B.ncols) || (A.nrows == B.nrows))&& "not equal: different dimensions.");

    // check if all elements are equal
    for (size_t i = 0; i < A.nrows; ++i) {
        for (size_t j = 0; j < A.ncols; ++j) {
            float a , b;
            a = get_element(A, i, j);
            b = get_element(B, i, j); 
            if (a != b) {
                return false; // not equal
            }
        }
    }

    return true; // equal
}

Matrix fill(size_t nrows, size_t ncols, float fill_value) {
    // initialize Matrix
    Matrix a = create_matrix(nrows, ncols);

    // fill the Matrix with the specified value
    for (size_t i = 0; i < nrows; ++i) {
        for (size_t j = 0; j < ncols; ++j) {
            set_element(a, i , j , fill_value); // set all elements
        }
    }

    return a; // return the filled Matrix
}

void unload(Matrix *B) {
    // free allocated memory for the Matrix
    if (B->A != NULL)
    {
        free(B->A); // free the array of elements
        B->A = NULL; // avoid dangling pointer
    }

    B->nrows = 0; // reset rows
    B->ncols = 0; // reset columns
}

#endif // MATRIX_IMPLEMENTATION

#endif // MATRIX_H
