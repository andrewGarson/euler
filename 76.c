#include <stdio.h>

#define TARGET 100

int main() {
  int ways[TARGET + 1] = {1}; // index 0 = 1, all others = 0

  for(int i = 1; i < TARGET; i++){
    for(int j = i; j <= TARGET; j++){
      ways[j] += ways[j-i];
    }
  }

  printf("%d", ways[TARGET]);
}


// The number of ways to add up to N is the sum of the 
// ways to add up to all the numbers less than N
//
// Let target = 10
// i = 5
// j will = 5, 6, 7, 8, 9
//
//
