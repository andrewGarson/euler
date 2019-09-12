#include <stdio.h>
#include <stdlib.h>

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


int *ways;
void expand_ways(int new_target){
  int *new_ways = realloc(ways, new_target + 1);
  if(new_ways) {
    ways = new_ways;
  } else {
    printf("Failed to extend ways array\n");
    exit(1);
  }
}

int found_5000(int target) {
  for(int i = 0; i<=target; i++) {
    if(ways[i] >= 5000) { return i; }
  }
  return -1;
}

int expand_primes(int biggest_prime, List *primes) {
  int *next = calloc(1, sizeof(int));
  *next = next_prime(biggest_prime);
  printf("expand from: %d\n", biggest_prime);
  printf("next: %d\n", *next);
  list_insert_back(primes, next); 
  printf("next prime inserted\n\n");
  return *next;
}

int main() {

  int target = 2;
  expand_ways(target);
  ways[0] = 1; // there is exactly 1 way to make 0 -- use no primes at all
  ways[1] = 0; // there is no way to make 1

  List *primes = list_create();

  int biggest_prime = 1;

  while(ways[target] < 5000) {
    biggest_prime = expand_primes(biggest_prime, primes);
    while(biggest_prime <= target) {
      ListNode *current_prime = primes->head;
      while(current_prime) {
        int prime = *(int *)(current_prime->value);
        for(int n = biggest_prime; n <= target; n++) {

          printf("biggestPrime: %d\n", biggest_prime);
          printf("prime: %d\n", prime);
          printf("target: %d\n", target);
          printf("n: %d\n", target);
          printf("\n");
          printf("ways[%d]: %d\n", n, ways[n]);
          printf("ways[n-prime]: %d\n", ways[n-prime]);
          
          ways[n] += ways[n - prime];
          if(ways[n] >= 5000) {
            printf("biggest prime: %d\n", biggest_prime);
            printf("N: %d\n", n);
            exit(0);
          }
          printf("\n\n");
        }
        current_prime = current_prime->next;
      }
      biggest_prime = expand_primes(biggest_prime, primes);
    }

    printf("Need to expand target\n\n");
    target++;
    expand_ways(target);
    while(target <= biggest_prime) {

      ListNode *current_prime = primes->head;
      while(current_prime) {
        int prime = *(int *)current_prime->value;
        ways[target] += ways[target - prime]; 
        current_prime = current_prime->next;
      }

      if(ways[target] >= 5000) {
        printf("Target: %d\n", target);
      }
      
      target++;
      expand_ways(target);
    }

  
  }

  printf("Found %d ways to make %d\n", ways[target], target);

  return 0;
}

/*
  int main() {

  int target = 64;
  ways = calloc(target + 1, sizeof(int));
  ways[0] = 1;
  ways[1] = 0;

  List *primes = list_create();

  int biggest_prime = 1;
  while(found_5000(target) == -1){

    biggest_prime = next_prime(biggest_prime);
    int *copy = calloc(1, sizeof(int));
    *copy = biggest_prime;
    list_insert_back(primes, (void *)copy); 

    printf("Using Prime = %d\n", biggest_prime);

    if(biggest_prime > target) {
      printf("Prime = %d is bigger than Target = %d\n", biggest_prime, target);
      return 0;
      target *= 2;
      expand_ways(target);
      
      // for each prime do this -- we've already calculated everything
      // up to and including the old target, now we need to apply
      // all of the smaller primes to the new values
      ListNode *cur = primes->head;
      while(NULL != cur) {
        int *prime = (int *)(cur->value);
        for(int j = *prime; j<=target; j++){
          ways[j] += ways[j - *prime];
        }
        cur = cur->next;
      }
    } else {
      printf("Prime = %d is smaller than Target = %d\n", biggest_prime, target);
      for(int j = biggest_prime; j <= target; j++){
        int extend_by = ways[j - biggest_prime];
        ways[j] += extend_by;
        if(extend_by > 0) {
          printf("\tExtended ways[%d] by %d to %d\n", j, extend_by, ways[j]);
        }
      }
    }
  }

  int index = found_5000(target);
  printf("Found %d ways to make %d\n", ways[index], index);

  return 0;
}
*/
