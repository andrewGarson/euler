#include <stdio.h>
#include <limits.h>

#include "debug.h"
#include "primes.h"

void generate_primes(int primes[], int how_many) {
  int count = 0;
  int n = 2;
  while(count < how_many){
    if(is_prime(n)){
      primes[count] = n;
      count++;
    }
    n++;
  }
}

void print_primes_table(int primes[], int count) {
  for(int i = 0; i<count; i++){
    printf("%6d", primes[i]);
    if(i % 20 == 19) { // 20 per row
      printf("\n");
    }
  }
}

int mod_exp(long long base, long long exponent, long long modulus) {
  if(modulus == 1) { return 0; }

  int result = 1;
  base = base % modulus;
  while(exponent > 0){
    if(exponent % 2 == 1) {
      result = (result * base) % modulus;
    }
    exponent = exponent >> 1;
    base = (base * base) % modulus;
  }

  return result;
}

/*
Output: composite if n is composite, otherwise prime
write n−1 as 2s·d by factoring powers of 2 from n−1
repeat for all {\displaystyle a\in [2,\min(n-1,\lfloor 2(\ln n)^{2}\rfloor )]} a\in [2,\min(n-1,\lfloor 2(\ln n)^{2}\rfloor )]:
    if {\displaystyle a^{d}\not \equiv 1{\pmod {n}}{\text{ and }}a^{2^{r}\cdot d}\not \equiv -1{\pmod {n}}{\text{ for all }}r\in [0,s-1]} a^{d}\not \equiv 1{\pmod {n}}{\text{ and }}a^{2^{r}\cdot d}\not \equiv -1{\pmod {n}}{\text{ for all }}r\in [0,s-1] then
            return composite
return prime
*/

int miller_rabin(int n, int witnesses[], int witness_count){

  log_debug("miller_rabin(%d)\n", n);

  if(n < 1) { 
    log_debug("n < 1 not prime\n");
    return 0; 
  } // 0 and negatives are not prime

  if(n < 4) { 
    log_debug("1 <= n < 4 prime\n");
    return 1; 
  }

  if(n%2 == 0) { 
    log_debug("n < 1 not prime\n");
    return 0; 
  } //even number > 2 are not prime

  for(int i = 0; i < witness_count; i++){
    log_debug("checking %d == witnesses[%d]=%d\n", n, i, witnesses[i]);
    if(n == witnesses[i]) { return 1; }
  }

  //write n − 1 as (2^r)*d with d odd by factoring powers of 2 from n − 1
  int m = n - 1; // we need n later, so put n-1 in another variable
  int s = __builtin_ctz(m); // number of 0's at the end of n-1 = number of 2's in factorization
  int d = m >> s; // shift off the 2's to get d

  log_debug("about to enter witness loop\n");
  log_debug("n: %d\n", n);
  log_debug("m: %d\n", m);
  log_debug("s: %d\n", s);
  log_debug("d: %d\n", d);
  log_debug("\n");

  for(int i = 0; i<witness_count; i++){
    int a = witnesses[i];
    log_debug("          a: %d\n", a);

    int a_d_mod_n = mod_exp(a, d, n);
    log_debug("  a^d mod n: %d\n", a_d_mod_n);

    if(a_d_mod_n == 1) { goto OUTER_LOOP; }
    for(int r = 0; r < s; r++){
      log_debug("                 r: %d\n", r);
      int a_two_r_d_mod_n = mod_exp(a, (1<<r)*d, n);
      log_debug("    a^(2^r)d mod n: %d\n", a_two_r_d_mod_n);
      log_debug("\n");
      if(a_two_r_d_mod_n == m) {
        goto OUTER_LOOP;
      }
    }

    log_debug("%d is composite", n);
    return 0;

OUTER_LOOP:
    ;
  }

  log_debug("%d is prime", n);
  return 1;
}

int is_prime(int p){
  // doing the probabilistic Miller-Rabin primality check with specific lists of primes 
  // for it's "a" values (witnesses) have been proven to be 100% accurate up to certain
  // numbers
  // proven sufficient to guarantee the algorithm will be truthful for numbers up to
  // [2, 3]                               1,373,653
  // [31, 73]                             9,080,191
  // [2, 7, 61]                       4,759,123,141
  // [2, 3, 5, 7, 11]             2,152,302,898,747
  // [2, 3, 5, 7, 11, 13]         3,474,749,660,383
  // [2, 3, 5, 7, 11, 13, 17]   341,550,071,728,321
  //
  // max int32                        2,147,483,647
  // max uint32                       4,294,967,295
  //
  // therefore we can do just 3 itterations and get an accurate result for 32 bit integers
  int small_primes[] = {2, 7, 61};
  return miller_rabin(p, small_primes, 3);
}

int next_prime(int n){
  if(n < 2) { return 2; }
  for(int m = n + 1; m <= INT_MAX; m++){
    if(is_prime(m)) { return m; }
  }
  return -1;
}
