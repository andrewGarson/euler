#include <stdio.h>
#include "lib/primes.h"

int main(){
  int prime = 1;
  for(int i = 0; i < 10001; i++) {
    prime = next_prime(prime);
  }
  printf("%d", prime);
}
