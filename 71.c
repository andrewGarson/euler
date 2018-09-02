#include <stdlib.h>
#include <stdio.h>

#include "lib/gcd.h"
#include "lib/debug.h"

#define TARGET 1000000

typedef struct {
  int numerator;
  int denominator;
} Fraction;

int main() {

  log_set_level(DEBUG);

  Fraction three_sevenths = {3, 7};
  Fraction result = {2,5};

  // Approach: 
  // loop over all the denominators 3->TARGET 
  //    there is only 1 proper reduced fraction when d = 2 (1/2) which is > 3/7
  // we need to constrain which numerators so we only check n's for which
  //    result < n/d < 3/7
  // since we are only checking proper fractions, we'll never have to deal with
  // n/d being equal to one of our endpoints -- otherwise it would not be reduced
  //
  // we want to find start and end values for n that make n/d as close to our result and 3/7
  // as possible without passing outside them 
  //
  for(long long d = 3; d < TARGET; d++){
    /*
     * find the value for start so that 
     *  result_n/result_d = start / d
     *  start = (d * result_n) / result_d
     *    if this divides evenly then we have a denominator that is a multiple of result_d
     *      and (start/d) == result
     *    if it doesn't, then because we're using integer division truncation
     *      (start / d) < result < (start + 1) / d
     *    we want to add 1 to start so we are minimally larger than result in both cases
     *
     *  end / d = 3 / 7
     *  end = (3 * d) / 7
     *    if d%7 == 1 then end/d = 3/7 so we need to subtract 1 from end
     *    if d%7 =/= 1 then end/d will be minimally smaller than 3/7 because of truncation
     *
     */
    long long start = ((d * result.numerator) / result.denominator) + 1;
    long long end = (3 * d)/7;
    if(d % 7 == 0) { end--; }

    if(d % 10000 == 0) {
      printf("d: %lld\n", d);
    }

    int step = 1;
    if(d%2 == 0){
      step = 2;
      if(start % 2 == 0) {
        start++;
      }
    }

    if(start < 0) {
      log_debug("HOW THE HELL???\n");
      log_debug("result: %d/%d\n", result.numerator, result.denominator);
      log_debug("start: %lld, end: %lld\n", start, end);
      log_debug("start = (%d * %d) / %d\n", d, result.numerator, result.denominator);
      return 1;
    }

    for(long long  n = start; n <= end; n+=step){
      if(gcd_stein(n,d) == 1) {
        log_debug("setting result = %d/%d\n", n, d);
        result.numerator = n;
        result.denominator = d;
      }
    }
  }

  printf("\n\nFinal Result:\n");
  printf("%d/%d\n", result.numerator, result.denominator);

}

/*
 * Consider the fraction, n/d, where n and d are positive integers. 
 * If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 *
 * If we list the set of reduced proper fractions for d ≤ 8 in 
 * ascending order of size, we get:
 *
 *      1/8, 1/7, 1/6, 1/5, 1/4, 
 *      2/7, 1/3, 3/8, 2/5, 3/7, <<-----
 *      1/2, 4/7, 3/5, 5/8, 2/3, 
 *      5/7, 3/4, 4/5, 5/6, 6/7, 
 *      7/8
 *
 * It can be seen that 2/5 is the fraction immediately to the left of 3/7.
 *
 * By listing the set of reduced proper fractions for d ≤ 1,000,000 in 
 * ascending order of size, find the numerator of the fraction immediately 
 * to the left of 3/7.
 */
