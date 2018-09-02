#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "lib/debug.h"

#include "lib/totient.h"
#include "lib/permutations.h"
#include "lib/primes.h"

#define TARGET 10000000

struct Result {
  int n;
  int phi_n;
  double ratio;
};

int main(int argc, char *argv[]){
  int *phi_cache; 
  phi_cache = calloc((TARGET+1), sizeof(int)); // 40MB cache -- lol

  // calculate the first 1000 primes to use as a hint to our phi function
  // we only need up to sqrt(TARGET), and this is more than sufficient
  // and takes less than a second
  log_set_level(NONE);
  int primes[1000];
  generate_primes(primes, 1000);
  log_set_level(INFO);

  struct Result result;
  result.n = 2;
  result.phi_n = 1;
  result.ratio = 2;

  for(unsigned int n = 3; n < TARGET; n++) {
    unsigned int phi_n = phi(n, primes, 1000, phi_cache);
    double ratio = (1.0*n) / phi_n;

    if(n % 100000 == 0) {
      printf("n: %d\n", n);
      printf("phi_n: %d\n", phi_n);
      printf("ratio: %f\n\n", ratio);
    }

    if(ratio < result.ratio && permutation_check(n, phi_n)){
      result.n = n;
      result.phi_n = phi_n;
      result.ratio = ratio;
    }
  }

  printf("phi(%d): %d - %d/%d = %f\n", result.n, result.phi_n, result.n, result.phi_n, result.ratio);

  return 0;
}

/*
Euler's Totient function, φ(n) [sometimes called the phi function], 
is used to determine the number of positive numbers less than or 
equal to n which are relatively prime to n. 

Relatively Prime
  two numbers are relatively prime if they share no common factors except for 1

For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.

Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.

Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.
*/
