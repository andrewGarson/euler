#include <stdio.h>

long long unsigned sum_i_squared(long long unsigned n) {
  return (n * (n+1) * (2*n+1))/6;
}

long long unsigned sum_i(long long unsigned n) {
  return (n*(n+1))/2;
}

int main() {

  long long unsigned _sum_i = sum_i(100);
  long long unsigned _sum_i_squared = sum_i_squared(100);
  printf("sum_i(100): %llu\n", _sum_i);
  printf("sum_i_squared(100): %llu\n", _sum_i_squared);
  printf("%llu\n", (_sum_i * _sum_i) - _sum_i_squared);
}

