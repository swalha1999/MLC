#include <stdlib.h>
#include <stdio.h>

#define MATRIX_AT(m, i, j)  (m)->data[(i) * (m)->_step + (j)]
#define PRINT_MATRIX(m) matrix_print_name(m, #m)

typedef struct {
    size_t rows;
    size_t cols;
    size_t _step;  // number of elements between rows
    float* data;
} Matrix;

Matrix* matrix_alloc(size_t rows, size_t cols);
void matrix_destroy(Matrix* m);
void matrix_print_name(Matrix* m, const char *name);
void matrix_fill(Matrix* m, float value);
Matrix* matrix_copy(Matrix* src);
Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_sub(Matrix* a, Matrix* b);
Matrix* matrix_mul(Matrix* a, Matrix* b);
Matrix* matrix_transpose(Matrix* a);


Matrix* matrix_alloc(size_t rows, size_t cols) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->_step = cols;
    m->data = (float*)malloc(rows * cols * sizeof(float));
    return m;
}

void matrix_destroy(Matrix* m) {
    free(m->data);
    free(m);
}
void matrix_print_data(Matrix* m) {
    for (size_t i = 0; i < m->rows; i++) {
        printf("    |  ");
        for (size_t j = 0; j < m->cols; j++) {
            printf("%f  ", MATRIX_AT(m, i, j));
        }
        printf("|\n");
    }
}

void matrix_print_name(Matrix *m, const char* name) {
    printf("%s = \n", name);
    matrix_print_data(m);
    printf("\n");
}

void matrix_fill(Matrix* m, float value) {
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            MATRIX_AT(m, i, j) = value;
        }
    }
}

Matrix* matrix_copy(Matrix* src) {
    Matrix* dst = matrix_alloc(src->rows, src->cols);
    for (size_t i = 0; i < dst->rows; i++) {
        for (size_t j = 0; j < dst->cols; j++) {
            MATRIX_AT(dst, i, j) = MATRIX_AT(src, i, j);
        }
    }
    return dst;
}




