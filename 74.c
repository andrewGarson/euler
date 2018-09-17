#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "lib/list.h"
#include "lib/hashset.h"
#include "lib/debug.h"

#define TARGET 1000000

int sum_of_digit_factorials(int n) {
  static int digit_factorials[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

  int sum = 0;
  while(n) {
    sum += digit_factorials[n%10];
    n /= 10;
  }
  return sum;
}



int factorial_cycle(int n, int *cycle_length_cache, int cache_size) {

  List *list = list_create();

  int current = n;
  int index_of_current = -1;

  // build up our list until we either create a cycle or run into
  // a number we know to be part of a cycle
  //
  // any number we've encountered before will have a value in the cache
  // the number will either be on an arm or the first number in a loop
  while(cycle_length_cache[current] == 0 && index_of_current == -1){
    int *value = calloc(1, sizeof(int));
    *value = current;
    log_debug("Checking: %d\n", current);
    list_insert_back(list, value);

    current = sum_of_digit_factorials(current);
    int *new_current = calloc(1, sizeof(int));
    *new_current = current;
    index_of_current = list_index_of(list, new_current, &int_list_equality);
  }

  // can't check for index_of_current == -1 to differentiate the
  // two cases because we default it to -1 and its possible that 
  // the original n has been handled before
  if(cycle_length_cache[current] > 0) {
    log_debug("Found existing cycle at %d\n", current);
    // we encountered a number we've handled before -- named current
    // current will not be in the list
    int total_cycle_count = list->length + cycle_length_cache[current];
    int i = 0;
    ListNode *node = list->head;
    while(node){
      cycle_length_cache[*((int *)(node->value))] = total_cycle_count - i;
      i++;
      node = node->next;
    }
  } else {
    log_debug("Found new cycle at %d\n", current);
    // we created a new loop
    // every index >= index_of_current gets the same value

    ListNode * node = list->head;
    for(int i = 0; i < list->length; i++){
      if(i < index_of_current) {
        cycle_length_cache[*((int *)(node->value))] = list->length - i;
      } else {
        cycle_length_cache[*((int *)(node->value))] = list->length - index_of_current;
      }
      node = node->next;
    }
  }

  list_destroy(&list);
  return cycle_length_cache[n];
}

int main() {

  log_set_level(INFO);

  //printf("540 -> %d\n\n", sum_of_digit_factorials(540));
  
  // the biggest number we care about is 1000000
  // the largets sum of factorials less than this will belong to
  // 999999 whose sum of factorials will be 6*9!, so we need to
  // maintain cycle counts for all integers up to that number
  int cache_size = 6 * (9*8*7*6*5*4*3*2);
  int *cycle_length_cache = calloc(cache_size, sizeof(int));
  
  //factorial_cycle(69, cycle_length_cache, cache_size);
  //return 0;

  int result = 0;

  for(int i = 0; i<TARGET; i++) {
    int cycle_length = factorial_cycle(i, cycle_length_cache, cache_size);
    printf("%d has cycle length %d\n", i, cycle_length);
    if(cycle_length == 60){
      result++;
    }
  }

  printf("\n\nFound %d chains with 60 unique entries\n", result);

  return 0;
}

/*
   The number 145 is well known for the property that the sum of the factorial 
   of its digits is equal to 145:

   1! + 4! + 5! = 1 + 24 + 120 = 145

   Perhaps less well known is 169, in that it produces the longest chain of 
   numbers that link back to 169; it turns out that there are only 
   three such loops that exist:

   169 → 363601 → 1454 → 169
   871 → 45361 → 871
   872 → 45362 → 872

   It is not difficult to prove that EVERY starting number will eventually 
   get stuck in a loop. For example,

   69 → 363600 → 1454 → 169 → 363601 (→ 1454)
   78 → 45360 → 871 → 45361 (→ 871)
   540 → 145 (→ 145)

   Starting with 69 produces a chain of five non-repeating terms, 
   but the longest non-repeating chain with a starting number below 
   one million is sixty terms.

   How many chains, with a starting number below one million, 
   contain exactly sixty non-repeating terms?
   */
