#ifndef _PRIMES_H_
#define _PRIMES_H_

int is_prime(int p);
int miller_rabin(int p, int witnesses[], int witness_count);
int next_prime(int n);

void generate_primes(int primes[], int how_many);
void print_primes_table(int primes[], int count);

#endif
