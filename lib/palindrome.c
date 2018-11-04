#include "palindrome.h"

int is_palindrome(int p) {
  int copy = p;
  int reversed = 0;

  while(copy > 0) {
    reversed *= 10;
    reversed += copy % 10;
    copy = copy/10;
  }

  return p == reversed;
}
