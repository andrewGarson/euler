#include "gcd.h"

unsigned int gcd_stein(unsigned int u, unsigned int v){
  if(u == 0) { return v; }
  if(v == 0) { return u; }
  int shift;
  
  // __builting_ctz returns the count of trailing zeros in the number
  // calling this on (u | v) will give us the number of times 2 divides into each
  shift = __builtin_ctz(u | v);

  // remove all powers of 2 from u -- they are either accounted for in shift or not shared
  // u is now odd
  u >>= __builtin_ctz(u); 
  do {
    // remove all powers of 2 from v -- they are either accounted for in shift or not shared
    // u and v are both odd
    v >>= __builtin_ctz(v); 
    if(u > v){
      unsigned int t = u; 
      u = v; 
      v = t; //swap u and v so that v > u always and we can only handle 1 of two symetrical cases
    }
    v = v - u; // v will be even so the shift above will be needed

  } while(v!= 0);

  return u << shift; // restore shared 2's
}
