#include <stdio.h>
#include <math.h>
#include "lib/primes.h"

#define TARGET 600851475143

int main() {
  int primes[1000];
  generate_primes(primes, 1000);

  int limit = sqrt(TARGET);
  for(int i = 999; i >= 0; i--) {
    if(primes[i] < limit && TARGET % primes[i] == 0) {
      printf("Largest prime factor: %d", primes[i]);
      break;
    }
  }
}

/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?
*/
