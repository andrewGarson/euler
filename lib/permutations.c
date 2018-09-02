#include "permutations.h"

#include <stdlib.h>
#include <math.h>

int compare(const void *lhs, const void *rhs){
  return ( *(int*)lhs - *(int*)rhs );
}

int digits(unsigned int n){
  return 1 + (int)(floor(log10(n))); // ceil doesn't work out the same for n = 1
}

int permutation_check(unsigned int n, unsigned int m) {
  int size = digits(n);
  if(digits(m) != size) {
    return 0;
  }

  int digits_n[size];
  int digits_m[size];
  for(int i = 0; i<size; i++){
    digits_n[i] = n % 10;
    digits_m[i] = m % 10;
    n/=10;
    m/=10;
  }
  qsort(digits_n, size, sizeof(int), compare);
  qsort(digits_m, size, sizeof(int), compare);

  for(int i = 0; i<size; i++){
    if(digits_n[i] != digits_m[i]) { return 0; }
  }

  return 1;
}


