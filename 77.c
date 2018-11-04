#include <stdio.h>
#include <stdlib.h>

#include "lib/list.h"
#include "lib/primes.h"


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

int main() {

  int target = 64;
  ways = calloc(target + 1, sizeof(int));
  ways[0] = 1;
  ways[1] = 0;

  List *primes = list_create();

  int biggest_prime = 1;
  // keep looking until we find a number with over 5000 ways to make it
  while(found_5000(target) == -1){
    
    // extend out list of primes until our biggest prime is too big to be useful
    // this happens when it is > our current target
    //
    // if our biggest prime is too big to use, then we need to increase our target
    // we need to fill in the ways to calculate these new targets using each of the
    // primes we had previously used
    //
    biggest_prime = next_prime(biggest_prime);
    int *copy = calloc(1, sizeof(int));
    *copy = biggest_prime;
    list_insert_back(primes, (void *)copy); 
    printf("Using Prime = %d\n", biggest_prime);


    if(biggest_prime > target) {
      // increase target, expand the ways array accordingly
      // starting at old_target + 1, use each prime to calculate ways for
      // that prime
    }

  }

  int index = found_5000(target);
  printf("Found %d ways to make %d\n", ways[index], index);

  return 0;
}

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
