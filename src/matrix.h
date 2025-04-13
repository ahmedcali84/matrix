/**
 * @file matrix.h
 * @brief Matrix Library
 *
 * A collection of basic and essential matrix operations for Unix systems.
 *
 * @author Ahmed Ali Mohammed <ahmedcali1984@gmail.com>
 * @version 0.1.0
 * @date January 30, 2025
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
#include <float.h>
#include <string.h>
#include <assert.h>

#define MATDEF extern

// Matrix Structure and Information
typedef struct Matrix {
    double *A;             // Pointer to the array of matrix elements
    size_t nrows;        // Number of rows in the matrix
    size_t ncols;        // Number of columns in the matrix
} Matrix;

/*
************** MATRIX OPERATIONS FUNCTIONS DECLARATIONS *******************
*/

MATDEF double get_element(Matrix C, size_t row, size_t col);                                   // get specific element from the Matrix
MATDEF void set_element(Matrix C, size_t row, size_t col, double value);                                    // set a specific element from the Matrix to a new value
MATDEF Matrix create_matrix(size_t rows, size_t cols);             // creates an empty Matrix with specified parameters
MATDEF Matrix random_matrix(size_t nrows, size_t ncols);           // generates random Matrix(nrows x ncols)
MATDEF void print_matrix(const Matrix b, const char *name);                                                // prints a Matrix
MATDEF int matrix_shape(Matrix a, const char *name);                                                       // prints the shape of the Matrix
MATDEF Matrix matrix_add(Matrix *a, Matrix *b);                                                            // adds two matrices
MATDEF Matrix matrix_subtract(Matrix *a, Matrix *b);                                                       // subtracts two matrices
MATDEF Matrix hadamard_product(Matrix *a, Matrix *b);                                                      // computes element-wise product of two matrices
MATDEF Matrix dot_product(Matrix *a, Matrix *b);                                                           // computes the dot-product of two matrices
MATDEF Matrix transpose(Matrix *a);                                                                        // return transpose of Matrix a
MATDEF bool test_matrix_equal(Matrix a, Matrix b, char *Matrix_a, char *Matrix_b);                         // test matrices for equality
MATDEF Matrix fill(size_t nrows, size_t ncols, double fill_value);  // creates a Matrix filled with a specific value (for development purposes)
MATDEF void unload(Matrix *b);                                                                             // Function to free Allocated Memory

// Special Macro Functions
#define PRINT(B) print_matrix(B, #B)                                                                       // Macro definition of a special print function
#define SHAPE(A) matrix_shape(A, #A)                                                                       // Macro definition of a special SHAPE printing function
#define TEST_MATRIX(A, B) test_matrix_equal(A, B, #A, #B)                                                  // Special Macro Version of Test Matrix Function also prints the variable-name of the Matrix
#define ALLOCATION_FAILED "Memory Allocation Failed.\n"

#ifdef __cplusplus
}
#endif

#endif // MATRIX_H
