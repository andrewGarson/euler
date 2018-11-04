#include <stdio.h>

#define TARGET 1000

int main() {
  int sum = 0;
  for(int i = 3; i < TARGET; i+=3){
    sum += i;
  }

  for(int i = 5; i < TARGET; i+=5){
    sum += i;
  }

  for(int i = 15; i < TARGET; i+=15){
    sum -= i;
  }

  printf("Sum of multiples of 3 or 5 < %d = %d", TARGET, sum);
}

/*
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
