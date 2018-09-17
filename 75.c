#include <stdio.h>

#include "lib/debug.h"
#include "lib/matrix.h"
#include "lib/list.h"

#define TARGET 1500000

Matrix *barning_a = NULL; 
Matrix *barning_b = NULL;
Matrix *barning_c = NULL;

void setup_barning_matrices() {
 barning_a = matrix_create(3,3);
 int data_a[3][3] = {
   { 1, -2, 2 },
   { 2, -1, 2 },
   { 2, -2, 3 }
 };
 matrix_load(barning_a, 3, 3, data_a);

 barning_b = matrix_create(3,3);
 int data_b[3][3] = {
   { 1, 2, 2 },
   { 2, 1, 2 },
   { 2, 2, 3 }
 };
 matrix_load(barning_b, 3, 3, data_b);

 barning_c = matrix_create(3,3);
 int data_c[3][3] = {
   { -1, 2, 2 },
   { -2, 1, 2 },
   { -2, 2, 3 }
 };
 matrix_load(barning_c, 3, 3, data_c);

}

int sum_column_vector(Matrix *v) {
  int sum = 0;
  for(int r = 0; r < v->rows; r++){
    sum += v->data[r][0];
  }
  return sum;
}



int main(){

  // how many times we get a pythagorean triple that sums to each index
  // e.g. sum_counts[1234] = 4 would mean that we found 4 triples that
  // sum up to 1234
  int perimeter_counts[TARGET + 1] = {0};

  setup_barning_matrices();

  List *triples_queue = list_create();

  // using the Barning method, the 3-tree of pythagorean triples is
  // rooted at [3,4,5]
  Matrix *three_four_five = matrix_create(3, 1);
  three_four_five->data[0][0] = 3;
  three_four_five->data[1][0] = 4;
  three_four_five->data[2][0] = 5;

  list_insert_back(triples_queue, three_four_five);

  while(0 < triples_queue->length){
    Matrix *triple;
    list_get_front(triples_queue, ((void **)(&triple)));
    list_remove_front(triples_queue);

    int perimeter = sum_column_vector(triple);
    for(int i = perimeter; i <= TARGET; i+=perimeter){
      perimeter_counts[i]++;
    }

    if(perimeter < TARGET) {
      list_insert_back(triples_queue, matrix_multiply(barning_a, triple));
      list_insert_back(triples_queue, matrix_multiply(barning_b, triple));
      list_insert_back(triples_queue, matrix_multiply(barning_c, triple));
    }
  }

  int exactly_one_triple = 0;
  for(int i = 0; i <= TARGET; i++) {
    if(perimeter_counts[i] == 1) {
      exactly_one_triple++;
    }
  }

  printf("%d lengths have exactly one triple\n", exactly_one_triple);

  return 0;
}
/*
 It turns out that 12 cm is the smallest length of wire that can be 
 bent to form an integer sided right angle triangle in exactly one way, 
 but there are many more examples.

 12 cm: (3,4,5)
 24 cm: (6,8,10)
 30 cm: (5,12,13)
 36 cm: (9,12,15)
 40 cm: (8,15,17)
 48 cm: (12,16,20)

 In contrast, some lengths of wire, like 20 cm, 
 cannot be bent to form an integer sided right angle triangle, 
 and other lengths allow more than one solution to be found; 
 for example, using 120 cm it is possible to form exactly three 
 different integer sided right angle triangles.

 120 cm: (30,40,50), (20,48,52), (24,45,51)

 Given that L is the length of the wire, for how many values of 
 L ≤ 1,500,000 can exactly one integer sided right angle triangle 
 be formed?
*/
