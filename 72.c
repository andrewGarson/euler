#include <stdlib.h>
#include <stdio.h>

#include "lib/totient.h"
#include "lib/primes.h"

#define TARGET 1000000

// this problem is basically the sum of totient(n) for n in [2,TARGET]
int main() {

  int *phi_cache;
  phi_cache = calloc((TARGET+1), sizeof(int)); 

  int primes[1000];
  generate_primes(primes, 1000);

  long long sum = 0;

  for(int d = 2; d <= TARGET; d++){
    sum += phi(d, primes, 1000, phi_cache);
  }

  printf("Number of proper reduced fractions: %lld\n", sum);

  return 0;
}


/*
 * Consider the fraction, n/d, where n and d are positive integers. 
 * If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d ≤ 8 
 * in ascending order of size, we get:
 *
 * 1/8, 1/7, 1/6, 1/5, 1/4, 
 * 2/7, 1/3, 3/8, 2/5, 3/7, 
 * 1/2, 4/7, 3/5, 5/8, 2/3, 
 * 5/7, 3/4, 4/5, 5/6, 6/7, 
 * 7/8
 *
 * It can be seen that there are 21 elements in this set.
 *
 * How many elements would be contained in the set of reduced proper 
 * fractions for d ≤ 1,000,000?
 */
