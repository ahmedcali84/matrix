#include "matrix.h"
#include <stdlib.h>

/*
************** matrix operations functions implementations *******************
*/

MATDEF double get_element(Matrix C, size_t row, size_t col) {
    // check for valid indices
    if (row >= C.nrows || col >= C.ncols) {
        fprintf(stderr, "index out of bounds: [%zu, %zu] for Matrix size [%zu, %zu]\n",
                row, col, C.nrows, C.ncols);
        exit(EXIT_FAILURE); // handle the error, exit or return an error value
    }
    
    return C.A[row * C.ncols + col];
}

MATDEF void set_element(Matrix C, size_t row, size_t col, double new_value) {
    // set the element at the specified row and column to a new value
    C.A[row * C.ncols + col] = new_value;
}

Matrix create_matrix(size_t rows, size_t cols) {
    Matrix create;
    create.nrows = rows;
    create.ncols = cols;
    create.A = calloc(sizeof(double), (rows * cols));
    if (create.A == NULL) {
        fprintf(stderr, ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }

    return create;
}

MATDEF Matrix random_matrix(size_t nrows, size_t ncols) {
    // initialize the Matrix
    Matrix random = create_matrix(nrows, ncols);

    // fill the Matrix with random values
    for (size_t i = 0; i < random.nrows; ++i) {
        for (size_t j = 0; j < random.ncols; ++j) {
            double v = ((double)rand() / RAND_MAX) * 1000 - 500;
            set_element(random, i , j , v);
        }
    }

    return random; // return the generated Matrix
}

MATDEF void print_matrix(const Matrix b, const char *name) {
    // print the Matrix with its name
    printf("%s = [\n", name);

    for (size_t i = 0; i < b.nrows; ++i) {
        for (size_t j = 0; j < b.ncols; ++j) {
            double value = get_element(b, i , j);
            printf(" %.2f ", value);
        }
        printf("\n");
    }
    printf("]"); // end of Matrix
    printf("\n\n");
}

MATDEF Shape matrix_shape(Matrix A) {
    // shape of the Matrix (rows, columns)
    Shape shape = {.rows = A.nrows, .cols = A.ncols};
    return shape;
}

MATDEF Matrix matrix_add(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows) && "addition failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);
    
    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            double a = get_element(*A, i , j);
            double b = get_element(*B, i , j);
            double c = a + b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result Matrix
}

MATDEF Matrix matrix_subtract(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows) && "subtraction failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);

    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            double a = get_element(*A, i , j);
            double b = get_element(*B, i , j);
            double c = a - b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result
}

MATDEF Matrix hadamard_product(Matrix *A, Matrix *B) {
    // ensure matrices are of the same size and type
    assert(A->ncols == B->ncols && "matrices dimensions mismatch");
    assert(A->nrows == B->nrows && "matrices dimensions mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols);

    // calculate element-wise product
    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            double a , b , c;
            a = get_element(*A, i , j);
            b = get_element(*B, i , j);
            c = a * b;
            set_element(C, i , j , c);
        }
    }

    return C; // return the result Matrix
}

MATDEF Matrix dot_product(Matrix *A, Matrix *B) {
    // check if the matrices can be multiplied
    assert((A->ncols == B->nrows) && "error multiplying: dimensions mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, B->ncols);

    // calculate the dot product
    for (size_t i = 0; i < C.nrows; ++i) {
        for (size_t j = 0; j < C.ncols; ++j) {
            double c = 0;
            for (size_t k = 0; k < A->ncols; ++k) {
                double a , b;
                a = get_element(*A, i , k );
                b = get_element(*B, k , j );
                c += a * b;
            }
            set_element(C , i , j , c);
        }
    }

    return C; // return the result Matrix
}

MATDEF Matrix transpose(Matrix *A) {
    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->ncols, A->nrows);

    for (size_t i = 0; i < A->nrows; ++i) {
        for (size_t j = 0; j < A->ncols; ++j) {
            double a;
            a = get_element(*A, i , j);
            set_element(C, j , i , a);
        }
    }

    return C; // return the transposed Matrix
}

MATDEF bool test_matrix_equal(Matrix A, Matrix B) {
    // check if the dimensions match
    assert(((A.ncols == B.ncols) || (A.nrows == B.nrows))&& "not equal: different dimensions.");

    // check if all elements are equal
    for (size_t i = 0; i < A.nrows; ++i) {
        for (size_t j = 0; j < A.ncols; ++j) {
            double a , b;
            a = get_element(A, i, j);
            b = get_element(B, i, j); 
            if (a != b) {
                return false; // not equal
            }
        }
    }

    return true; // equal
}

MATDEF Matrix fill(size_t nrows, size_t ncols, double fill_value) {
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

MATDEF void unload(Matrix *B) {
    // free allocated memory for the Matrix
    if (B->A != NULL)
    {
        free(B->A); // free the array of elements
        B->A = NULL; // avoid dangling pointer
    }

    B->nrows = 0; // reset rows
    B->ncols = 0; // reset columns
}

