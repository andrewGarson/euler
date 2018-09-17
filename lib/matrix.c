#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

Matrix *matrix_create(int rows, int cols){
  Matrix *matrix = calloc(1, sizeof(Matrix));

  matrix->rows = rows;
  matrix->cols = cols;

  matrix->data = calloc(rows, sizeof(int *));
  for(int r = 0; r < rows; r++){
    matrix->data[r] = calloc(cols, sizeof(int *));
  }

  return matrix;
}

void matrix_destroy(Matrix **matrix){

  for(int r = 0; r < (*matrix)->rows; r++){
    free((*matrix)->data[r]);
    (*matrix)->data[r] = NULL;
  }

  free((*matrix)->data);
  (*matrix)->data = NULL;
  (*matrix)->rows = -1;
  (*matrix)->cols = -1;

  matrix = NULL;
}

void matrix_print(Matrix *matrix){

  int column_lengths[matrix->cols];
  int column_length_sum = 0;

  for(int c = 0; c < matrix->cols; c++) {
    column_lengths[c] = 1;
    for(int r = 0; r < matrix->rows; r++){
      int n = matrix->data[r][c];
      if(n == 0) { continue; }

      int length = floor(log10(abs(n))) + 1;
      if(n < 0) { length++; } // account for negative sign

      column_lengths[c] = (length >  column_lengths[c]) ? length : column_lengths[c];
    }
    column_length_sum += column_lengths[c];
  }

  printf("\u250c %*s\u2510\n", column_length_sum + matrix->cols, "");

  for(int r = 0; r < matrix->rows; r++) {
    printf("\u2502 ");
    for(int c = 0; c < matrix->cols; c++) {
      printf("%*d ", column_lengths[c], matrix->data[r][c]);
    }
    printf("\u2502\n");
  }

  printf("\u2514 %*s\u2518\n", column_length_sum + matrix->cols, "");
}

void matrix_load(Matrix *matrix, int rows, int cols, int data[rows][cols]){
  for(int r = 0; r < rows; r++) {
    for(int c = 0; c < cols; c++) {
      matrix->data[r][c] = data[r][c];
    }
  }
}


Matrix *matrix_scale(Matrix *a, int n) {
  Matrix *s = matrix_create(a->rows, a->cols);
  
  for(int r = 0; r < a->rows; r++){
    for(int c = 0; c < a->cols; c++){
      s->data[r][c] = n * a->data[r][c];
    }
  }

  return s;
}

Matrix *matrix_multiply(Matrix *a, Matrix *b){
  Matrix *c = matrix_create(a->rows, b->cols);
  // c = ab
  // c[i][j] = a[i][k] + b[k][j]
  //
  // a->cols MUST EQUAL b->rows
  //

  for(int i = 0; i < a->rows; i++){ // each row in c
    for(int j = 0; j < b->cols; j++){ // each column in c
      for(int k = 0; k < a->cols; k++){ // traverse row in a and col in b
        c->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }

  return c;
}

void matrix_list_print_callback(void *matrix){
  matrix_print((Matrix *)matrix);
  printf("|\n");
  printf("V\n");
}
