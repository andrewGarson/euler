#ifndef _TOTIENT_H_
#define _TOTIENT_H_

/*
 * Calculates phi(n) using a recursive approach based on properties of phi(n)
 *
 * We require a primes[] containing all of the primes upto sqrt(n)
 *
 * if phi_cache is provided then we will set phi_cache[n] before returning
 *
 * n            - number we want to calculate phi(n)
 * primes[]     - array containing primes at least up to sqrt(n)
 * primes_count - size of primes[]
 * phi_cache[]  - optional array containing at least n+1 entries initialized to 0
 *                where we can lookup/store intermediary values for a recursive approach
 *                create this outside the function call if you want to share work across
 *                multiple calls to phi
 *
 * returns phi(n)
 */
unsigned int phi(unsigned int n, int primes[], int primes_count, int phi_cache[]);

/*
 * Directly calculates phi(n) based upon the definition
 *  this is slower, but doesn't require calculation of a primes[] 
 */
unsigned int phi_gcd(unsigned int n);

#endif

