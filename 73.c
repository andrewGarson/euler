#include <stdlib.h>
#include <stdio.h>

#include "lib/gcd.h"
#include "lib/debug.h"

#define TARGET 12000

typedef struct {
  int numerator;
  int denominator;
} Fraction;

int main() {

  log_set_level(DEBUG);

  long long count = 0;
  Fraction upper = {1,2};
  Fraction lower = {1,3};


  // start/d = lower.numerator/lower.denominator
  // start = (d * lower.numerator / lower.denominator)
  //
  // end/d = upper.numerator / upper.denominator
  // end = (d * upper.numerator) / upper.denominator

  for(long long d = 2; d <= TARGET; d++){

    long long start = ((d * lower.numerator) / lower.denominator) + 1;
    long long end = (d * upper.numerator)/upper.denominator;

    if(gcd_stein(d, upper.denominator) != 1) { end--; }


    /*
    printf("d: %lld\n", d);
    printf("start = ((%lld * %d) / %d) + 1 = %lld\n", d, lower.numerator, lower.denominator, start);
    printf("end = ((%lld * %d) / %d) = %lld\n", d, upper.numerator, upper.denominator, end);
    */
    for(long long  n = start; n <= end; n++){
      if(gcd_stein(n,d) == 1) {
        //printf("%lld/%lld\n", n, d);
        count++;
      }
    }
    printf("\n");
  }

  printf("\n\nCount: %lld\n", count);
}
