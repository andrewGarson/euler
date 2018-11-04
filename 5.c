#include <stdio.h>
#include <math.h>

int main() {

  int prime_factors[8] =   {2,  3,  5,  7,  11,  13,  17,  19};
  int max_primes_used[8] = {0,  0,  0,  0,   0,   0,   0,   0};

  for(int i = 2; i <= 20; i++) {
    for(int p = 0; p < 8; p++) {
      int factor = prime_factors[p];
      int n = i;
      int factor_count = 0;
      while(n > 0 && n % factor == 0) {
        factor_count++;
        n /= factor;
      }
      if(factor_count > max_primes_used[p]) {
        max_primes_used[p] = factor_count;
      }

    }
  }

  int value = 1;
  for(int i = 0; i < 8; i++) {
    value *= pow(prime_factors[i], max_primes_used[i]);
  }

  printf("%d", value);

}

/*
 * 2520 is the smallest number that can be divided by each 
 * of the numbers from 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly 
 * divisible by all of the numbers from 1 to 20?
 */
