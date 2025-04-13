#include "matrix.h"
#include <stdlib.h>

/*
************** matrix operations functions implementations *******************
*/

MATDEF void get_element(Matrix c, size_t row, size_t col, void *target) {
    // check for valid indices
    if (row >= c.nrows || col >= c.ncols) {
        fprintf(stderr, "index out of bounds: [%zu, %zu] for Matrix size [%zu, %zu]\n",
                row, col, c.nrows, c.ncols);
        exit(EXIT_FAILURE); // handle the error, exit or return an error value
    }

    // retrieve an element from the Matrix at the specified row and column
    void *element = (char *) c.A + (row * c.ncols + col) * c.element_size;
    memcpy(target, element, c.element_size);
}

MATDEF void set_element(Matrix c, size_t row, size_t col, void *value) {
    // set the element at the specified row and column to a new value
    void *element = (char *) c.A + (row * c.ncols + col) * c.element_size;
    memcpy(element, value, c.element_size);
}

Matrix create_matrix(size_t rows, size_t cols, size_t element_size, Element_Type type) {
    Matrix create;
    create.nrows = rows;
    create.ncols = cols;
    create.element_size = element_size;
    create.type = type;
    create.A = calloc(element_size, (rows * cols));
    if (create.A == NULL) {
        fprintf(stderr, ALLOCATION_FAILED);
        exit(EXIT_FAILURE);
    }

    return create;
}

MATDEF Matrix random_matrix(size_t nrows, size_t ncols, size_t element_size, Element_Type type) {
    // initialize the Matrix
    Matrix random = create_matrix(nrows, ncols, element_size, type);

    // fill the Matrix with random values
    switch (random.type) {
        case TYPE_INT:
            for (size_t i = 0; i < random.nrows; ++i) {
                for (size_t j = 0; j < random.ncols; ++j) {
                    int v = (rand() / (RAND_MAX - (RAND_MAX / 2)));
                    set_element(random, i , j , &v);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < random.nrows; ++i) {
                for (size_t j = 0; j < random.ncols; ++j) {
                    double v = ((double)rand() / RAND_MAX) * 1000 - 500;
                    set_element(random, i , j , &v);
                }
            }
            break;

        default:
            fprintf(stderr, "unknown type for the type Matrix");
            exit(EXIT_FAILURE);
    }

    // return the random Matrix
    return random; // return the generated Matrix
}

MATDEF void print_matrix(const Matrix b, const char *name) {
    // print the Matrix with its name
    printf("%s = [\n", name);
    switch (b.type) {
        case TYPE_INT:
            for (size_t i = 0; i < b.nrows; ++i) {
                for (size_t j = 0; j < b.ncols; ++j) {
                    int v;
                    get_element(b, i , j , &v);
                    printf(" %d ", v);
                }
                printf("\n");
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < b.nrows; ++i) {
                for (size_t j = 0; j < b.ncols; ++j) {
                    double v;
                    get_element(b, i , j , &v);
                    printf(" %.2f ", v);
                }
                printf("\n");
            }
            break;

        default:
            fprintf(stderr, "unknown type selected for printing");
            exit(EXIT_FAILURE);
    } 
    printf("]"); // end of Matrix
    printf("\n\n");
}

MATDEF int matrix_shape(Matrix a, const char *name) {
    // print the shape of the Matrix (rows, columns) and its type
    switch (a.type) {
        case TYPE_INT:
            printf("%s(shape: (%zu , %zu), dtype=int)\n", name, a.nrows, a.ncols);
            break;
        case TYPE_DOUBLE:
            printf("%s(shape: (%zu , %zu), dtype=double)\n", name, a.nrows, a.ncols);
            break;
        default:
            printf("unknown type.\n");
            return 1;
    }
    return 0;
}

MATDEF Matrix matrix_add(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows && A->type == B->type) && "addition failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols, A->element_size, A->type);
    
    switch (A->type) {
        case TYPE_INT:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    int a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a + b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    double a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a + b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        default:
            fprintf(stderr, "unknown type for addition matrices");
            exit(EXIT_FAILURE);
    }

    return C; // return the result Matrix
}

MATDEF Matrix matrix_subtract(Matrix *A, Matrix *B) {
    // check if the dimensions of the matrices are the same
    assert((A->ncols == B->ncols && B->nrows == A->nrows && A->type == B->type) && "subtraction failed, matrices shape mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols, A->element_size, A->type);

    switch (A->type) {
        case TYPE_INT:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    int a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a - b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    double a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a - b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        default:
            fprintf(stderr, "unknown type for subtraction matrices");
            exit(EXIT_FAILURE);
    }

    return C; // return the result
}

MATDEF Matrix hadamard_product(Matrix *A, Matrix *B) {
    // ensure matrices are of the same size and type
    assert(A->ncols == B->ncols && "matrices dimensions mismatch");
    assert(A->nrows == B->nrows && "matrices dimensions mismatch");
    assert(A->type  == A->type  && "type mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, A->ncols, A->element_size, A->type);

    // calculate element-wise product
    switch (A->type) {
        case TYPE_INT:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    int a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a * b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    double a , b , c;
                    get_element(*A, i , j , &a);
                    get_element(*B, i , j , &b);
                    c = a * b;
                    set_element(C, i , j , &c);
                }
            }
            break;

        default:
            fprintf(stderr, "unknown type for multiplication matrices");
            exit(EXIT_FAILURE);
    }
    

    return C; // return the result Matrix
}

MATDEF Matrix dot_product(Matrix *A, Matrix *B) {
    // check if the matrices can be multiplied
    assert((A->ncols == B->nrows) && "error multiplying: dimensions mismatch");
    assert((A->type == B->type) && "type mismatch");

    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->nrows, B->ncols, A->element_size, A->type);

    // calculate the dot product
    switch (A->type) {
        case TYPE_INT:
            for (size_t i = 0; i < C.nrows; ++i) {
                for (size_t j = 0; j < C.ncols; ++j) {
                    int c = 0;
                    for (size_t k = 0; k < A->ncols; ++k) {
                        int a , b;
                        get_element(*A, i , k , &a);
                        get_element(*B, k , j , &b);
                        c += a * b;
                    }
                    set_element(C , i , j , &c);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < C.nrows; ++i) {
                for (size_t j = 0; j < C.ncols; ++j) {
                    double c = 0;
                    for (size_t k = 0; k < A->ncols; ++k) {
                        double a , b;
                        get_element(*A, i , k , &a);
                        get_element(*B, k , j , &b);
                        c += a * b;
                    }
                    set_element(C , i , j , &c);
                }
            }
            break;

        default:
            printf("error: unknown type for the multiplication operations.\n");
            exit(EXIT_FAILURE);
    }

    return C; // return the result Matrix
}

MATDEF Matrix transpose(Matrix *A) {
    // initialize a new Matrix for the result
    Matrix C = create_matrix(A->ncols, A->nrows, A->element_size, A->type);

    // calculate the transpose
    switch (A->type) {
        case TYPE_INT:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    int a;
                    get_element(*A, i , j , &a);
                    set_element(C, j , i , &a);
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < A->nrows; ++i) {
                for (size_t j = 0; j < A->ncols; ++j) {
                    double a;
                    get_element(*A, i , j , &a);
                    set_element(C, j , i , &a);
                }
            }
            break;

        default:
            printf("error: unknown type for transpose operation.\n");
            exit(EXIT_FAILURE);
    }

    return C; // return the transposed Matrix
}

MATDEF bool test_matrix_equal(Matrix A, Matrix B, char *Matrix_a, char *Matrix_b) {
    // check if the dimensions match
    assert(((A.ncols == B.ncols) || (A.nrows == B.nrows)) && (A.type == B.type) && "not equal: different dimensions.");

    // check if all elements are equal
    switch (A.type) {
        case TYPE_INT:
            for (size_t i = 0; i < A.nrows; ++i) {
                for (size_t j = 0; j < A.ncols; ++j) {
                    int a , b;
                    get_element(A, i, j, &a);
                    get_element(B, i, j, &b); 
                    if (a != b) {
                        printf("%s and %s are not equal: values differ at (%zu, %zu)\n", Matrix_a, Matrix_b, i, j); // print mismatch
                        return false; // not equal
                    }
                }
            }
            break;

        case TYPE_DOUBLE:
            for (size_t i = 0; i < A.nrows; ++i) {
                for (size_t j = 0; j < A.ncols; ++j) {
                    double a , b;
                    get_element(A, i, j, &a);
                    get_element(B, i, j, &b); 
                    if (a != b) {
                        printf("%s and %s are not equal: values differ at (%zu, %zu)\n", Matrix_a, Matrix_b, i, j); // print mismatch
                        return false; // not equal
                    }
                }
            }
            break;
        
        default:
            printf("unknown type for identifying equal Matrix.\n");
            exit(EXIT_FAILURE);
    }

    printf("%s and %s are equal\n", Matrix_a, Matrix_b); // print equal matrices
    return true; // equal
}

MATDEF Matrix fill(size_t nrows, size_t ncols, size_t element_size, Element_Type type, void *fill_value) {
    // initialize Matrix
    Matrix a = create_matrix(nrows, ncols, element_size, type);

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

