#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/list.h"
#include "lib/primes.h"

/*
 * It is possible to write ten as the sum of primes 
 * in exactly five different ways:
 *
 * 7 + 3
 * 5 + 5
 * 5 + 3 + 2
 * 3 + 3 + 2 + 2
 * 2 + 2 + 2 + 2 + 2
 *
 * What is the first value which can be written as 
 * the sum of primes in over five thousand different ways?
 */

#define TARGET 5000

int main() {
  int max = 9999;
  int ways[10000] = {1};
  int prime = 1;

  while(1) { // forever
    prime = next_prime(prime);
    printf("prime: %d\n", prime);
    for(int i = prime; i <= max; i++){
      ways[i] += ways[i-prime];
    }
    for(int i = 0; i < prime; i++) {
      if(ways[i] >= TARGET) {
        printf("Solution: %d\n", i);
        exit(0);
      }
    }
  }
}
