#include <stdlib.h>
#include <stdio.h>
#include "lib/palindrome.h"

int main() {
  int check[] = {
    1001,
    232,
    29492,
    199,
    80,
    9182819
  };

  long unsigned largest = 0;
  for(int i = 999; i > 99; i--){
    for(int j = 999; j > i; j--){
      long unsigned product = i * j;
      if(product <= largest) { 
        break;  // no value for j can give us an i*j > largest, so go to the next i
      }
      if(is_palindrome(product)){
        printf("%d * %d = %lu\n", i, j, product);
        largest = product;
      }
    }
  }

  printf("%lu", largest);
}

/*
A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit 
numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
