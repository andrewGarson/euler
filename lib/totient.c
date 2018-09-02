#include "totient.h"
#include "debug.h"
#include "primes.h"
#include "gcd.h"

unsigned int phi(unsigned int n, int primes[], int primes_count, int phi_cache[]){
  if(phi_cache && phi_cache[n] != 0) {
    log_debug("Found %d in cache\n", n);
    return phi_cache[n];
  }

  int result = 0;

  // we use a generic is_prime check because the primes[] may not have n -- it only goes up
  // to sqrt(n)
  if(n==1) {
    result = 1;
  } else if(is_prime(n)) {
    // if p is prime then phi(p) = p - 1 
    log_debug("Prime %d\n", n);
    result = n - 1;
  } else {
    // - phi(a^k) = a^(k-1) * phi(a)
    // - if gcd(c,d) == 1 then phi(cd) = phi(c) * phi(d)
    // - if p is prime then phi(p) = p -1 
    //
    // find a prime p that divides n k times
    //
    // let c = p^k
    // let d = n / c
    // gcd(c,d) = 1 because they share no prime factors
    //
    // phi(n) = phi(cd) = phi(c) * phi(d)
    // phi(c) = phi(p^k) = p^(k-1) * phi(p)
    // phi(p) = p - 1
    //
    // plugging these in we get
    //
    // phi(c) = phi(p^k) = p^(k-1) * (p - 1) = (p^k - p^(k-1))
    // phi(n) = (p^k - p^(k-1)) * phi(d)
    //
    for(int i = 0; i < primes_count; i++){
      int p = primes[i];
      if( n % p == 0) { 

        // we know there is at least 1 p factor in n
        // keep pulling them out until we can't anymore
        unsigned int c = p; 
        unsigned int d = n / p;
        while(d % p == 0){
          c *= p;
          d /= p;
        }
        // there's a chance that c=n, d=1 after this process 
        // phi(d) = 1, so everything still works
        result = (unsigned int)(c - (c/p)) * phi(d, primes, primes_count, phi_cache);
        break;
      }
    }

    if(result == 0){
      // phi(n) = n * PRODUCT[p|n](1 - 1/p) -- product of all primes that divide n
      // given an integer k
      //  (1 - 1/k) = (k/k - 1/k) = ((k-1)/k)
      // for each of our primes < sqrt(n)
      unsigned long long int numerator = n;
      unsigned long long int denominator = 1;

      for(int i = 0; i<primes_count; i++){
        log_debug("Trying %d\n", primes[i]);
        if(primes[i] > n) { break; }
        if(n % primes[i] == 0){ // p|n
          numerator *= (primes[i] - 1);
          denominator *= primes[i];

          log_debug("Using %d\n", primes[i]);
          log_debug("numerator %llu\n", numerator);
          log_debug("denominator %llu\n", denominator);
        }
      }

      result = (numerator / denominator);
    }
  }

  if(phi_cache) { phi_cache[n] = result; }
  return result;
}

unsigned int phi_gcd(unsigned int n) {
  unsigned int count = 0;
  for(unsigned int i = 1; i < n; i++){
    if(gcd_stein(n, i) == 1){
      count++;
    }
  }
  return count;
}
