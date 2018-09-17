#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct _Matrix {
  int rows;
  int cols;
  int **data;
} Matrix;

Matrix *matrix_create(int rows, int cols);
void matrix_load(Matrix *matrix, int rows, int cols, int data[rows][cols]);
void matrix_destroy(Matrix **matrix);

void matrix_print(Matrix *matrix);

Matrix *matrix_scale(Matrix *a, int n);
Matrix *matrix_multiply(Matrix *a, Matrix *b);

void matrix_list_print_callback(void *matrix);

#endif
