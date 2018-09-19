#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TARGET 1000

const int denominations[] = {1, 2, 5, 10, 20, 50, 100, 200};

int cache[TARGET + 1][9];

int memoized_solution(int target, int coin_index){
  if(coin_index <= 0) { return 1; } // we only have 1p coins left
  int t = target;
  if(cache[t][coin_index] > 0) { return cache[t][coin_index]; }
  
  int ways = 0;
  while(target >= 0) {
    ways += memoized_solution(target, coin_index - 1);
    target -= denominations[coin_index];
  }
  cache[t][coin_index] = ways;
  return ways;
}

int recursive_solution(int target, int coin_index) {
  if(target == 0 || coin_index == 0) {
    return 1;
  }

  int ways = 0;
  int c = denominations[coin_index];
  // when the largest coin is c we can use up to floor(target/c) of those coins
  // for each number of c value coins, we need to count the ways to make up the rest
  // if target == 200 
  //    when c == 200, 
  //      we recurse with (0, 100), which returns 1 -- there is only 1 way to get 200 with 200 cois
  //    when c == 100
  //      we can use 0x 100 coins and we will recurse with (200, 50) -- get 200 with 50 and smaller
  //      we can use 1x 100 coins and we will recuse with (100, 50) -- get 100 with 50 and smaller
  //      we can use 2x 100 coins and we will recuse with (0, 50) -- get 0 -- yields 1
  //    when c == 50
  //      we can use 0-4x 50 coins and we will recuse with the remainder and 20 coins 
  //
  //    this continues down until we either have made up our total or our largest coin available is 1
  //    when that happens, we only have 1 choice on what to do (namely 1 + 1 + 1 ...)
  for(int i = 0; i<= target/c; i++){
    ways += recursive_solution(target - i*c, coin_index - 1);
  }

  return ways;
}

long int dynamic_bottom_up(int target){
  long int ways[target + 1];
  memset(ways, 0, (target+1)*sizeof(long int));
  ways[0] = 1;

  /*  each total j can be made many different ways from all the coins <= j
   *
   *  for each coin <= j, we can rewrite j as 
   *    c + (j -c)
   *  meaning we can use 1 coin of c value plus all the different
   *  ways of making (j-c) -- importantly, this can include more c values
   *  
   *  if we start at the bottom, with j = our lowest coin c
   *  then all the j values up to target can have at least a single c
   *  
   *  ways[0] = 1 is our initialization to handle the case where c == j
   *      there's only 1 way to make j with at least 1 c in that case
   *
   *  first
   *  when c = 1, j ranges from 1 to target
   *    ways[1] += ways[0]
   *    ways[2] += ways[1]
   *    ...
   *    ways[target] += ways[target - 1]
   *
   *  there is only 1 way to make each value using only pennies
   *
   *  next
   *  when c = 5, j ranges from 5 to target
   *  ways[5] += ways[0]
   *  ways[6] += ways[1]
   *  ...
   *  ways[10] += ways[5] -- which we just updated a moment    
   *  ...
   *  ways[target] += ways[target - 5]
   *  by adding in nickels, we've created more ways to generate each 
   *  j >= 5 
   */

  for(int i = 0; i < 8; i++){
    for(int j = denominations[i]; j <= target; j++){
      ways[j] += ways[j - denominations[i]];
    }
  }
  return ways[target];
}

int main() {
  printf("How many ways using English coins can you get to %dp?\n\n", TARGET);
  printf("Recursive Solution: %d\n", recursive_solution(TARGET, 7));
  printf("Memoized Solution:  %d\n", memoized_solution(TARGET, 7));
  printf("Dynamic Solution:  %ld\n", dynamic_bottom_up(TARGET));
  
}




/*
 * In England the currency is made up of pound, £, and pence, p, 
 * and there are eight coins in general circulation:
 *
 * 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
 * It is possible to make £2 in the following way:
 *
 * 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
 *
 * How many different ways can £2 be made using any number of coins?
 *
 */
