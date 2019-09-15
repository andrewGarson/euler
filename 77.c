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

typedef struct {
  List *primes;
  int largest_prime;
  int* ways;
  int ways_length;
  int target;
} ProblemState;

void print_ways(ProblemState *state) {
  for(int i = 0; i < state->ways_length; i++){
    printf("%d: %d\n", i, state->ways[i]);
  }
}

void expand_ways(ProblemState *state) {
  state->ways = realloc(state->ways, (2*state->ways_length)*sizeof(int));
  memset(state->ways +  state->ways_length, 0, state->ways_length * sizeof(int));
  state->ways_length = 2*state->ways_length;
  printf("\nExpanded ways array\n");
}

int expand_primes(int biggest_prime, List *primes) {
  int *next = calloc(1, sizeof(int));
  *next = next_prime(biggest_prime);
  list_insert_back(primes, next); 
  printf("expanding primes to ");
  print_integer_list(primes);
  return *next;
}

ProblemState *initialize() {
  ProblemState *state = calloc(1, sizeof(ProblemState));
  state->primes = list_create();
  int_list_insert_back(state->primes, 2);
  state->largest_prime = 2;

  state->ways = (int *)calloc(3, sizeof(int));
  state->ways_length = 3;
  state->ways[0] = 1;
  state->ways[1] = 0;
  state->ways[2] = 1;

  state->target = 2;
  return state;
}

void extend_primes(ProblemState *state) {
  while(state->largest_prime <= state->target) {
    printf("largest_prime: %d <= target: %d\n", state->largest_prime, state->target);
    int p = next_prime(state->largest_prime);
    int_list_insert_back(state->primes, p);
    state->largest_prime = p;
    printf("Extended primes to include %d\n", p);
    print_integer_list(state->primes);


    // for every number n between our new prime and our current target,
    // we need to update the ways to make that number that include
    // our new prime p
    printf("Our new prime is %d\n", p);
    for(int n = p; n <= state->target; n++) {
      printf("We can use that to make %d in %d ways\n", n, state->ways[n-p]);
      state->ways[n] += state->ways[n-p];
    }

    print_ways(state);
  }
}

void extend_target(ProblemState *state) {
  while(state->target < state->largest_prime) { // < or <= ??
    printf("target: %d < largest_prime: %d\n", state->target, state->largest_prime);
    state->target++;
    if(state->target >= state->ways_length) { expand_ways(state); }

    ListNode *current_prime_node = state->primes->head;
    while(current_prime_node) {

      int prime= *((int *)(current_prime_node->value));
      if(prime > state->target) {
        printf("We can't use %d to make %d\n", prime, state->target);
        break;
      }
      printf("We can use %d to make %d in %d ways\n", prime, state->target, state->ways[state->target - prime]);
      state->ways[state->target] += state->ways[state->target - prime];

      current_prime_node = current_prime_node->next;
    }

    print_ways(state);
  }
}

int main() {
  ProblemState *state = initialize();

  while(state->ways[state->target] < 5000) {
    printf("Extend primes\n");
    extend_primes(state);
    printf("\n");
    printf("Extend target\n");
    extend_target(state);
    printf("\n\n");
  }

  printf("N: %d", state->target);
}

