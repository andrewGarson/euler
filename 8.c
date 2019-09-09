#include <stdlib.h>
#include <stdio.h>

#define DIGITS 1000
#define RESULT_LENGTH 13

// Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?

void readDigits(int digit[DIGITS]);
unsigned long long largestProduct(int start, int digits[DIGITS]); 
unsigned long long largestProduct_slow(int start, int digits[DIGITS]); 

int lookaheadForZero(int start, int digits[DIGITS]); 
unsigned long long productStartingFrom(int i, int digits[DIGITS]);


int main() {
  int digits[DIGITS];
  readDigits(digits);

  unsigned long long answer = largestProduct(0, digits);
  printf("%llu\n", answer);
}

void readDigits(int digits[DIGITS]) {
  FILE *input = fopen("8.txt", "r");

  if(!input) {
    printf("file read error for 8.txt\n");
    exit(1);
  }

  for(int i = 0; i<DIGITS; i++){
    if(1!=fscanf(input, "%1d", &digits[i])) {
      printf("Error reading digit at index %d\n", i);
      exit(0);
    }
  }
}

unsigned long long largestProduct_slow(int start, int digits[DIGITS]){
  unsigned long long largest = 0;
  for(int i = 0; i < DIGITS - RESULT_LENGTH; i++){
    unsigned long long current = productStartingFrom(i, digits);
    if(current > largest) {
      largest = current;
    }
  }
  return largest;
}

unsigned long long largestProduct(int start, int digits[DIGITS]) {
  int nextZero = -1;
  int index = start;
  // scan ahead until we have enough sequential non-zeroes 
  while((nextZero = lookaheadForZero(index, digits)) != -1) {
    index = nextZero + 1;
  }
  // get the first valid product
  unsigned long long currentProduct = productStartingFrom(index, digits);
  unsigned long long largestProduct = currentProduct;
  index++;

  int max_index = DIGITS - RESULT_LENGTH;

  // at this point, we know that we have 12 non-zeros, but #13 could be a zero
  while(index <= max_index) {
    int previousDigit = digits[index - 1];

    int finalIndex = (index + RESULT_LENGTH) -1;
    int finalDigit = digits[finalIndex];

    if(0 == finalDigit) {
      while((nextZero = lookaheadForZero(index, digits)) != -1) {
        index = nextZero + 1;
        if(index > max_index) { return largestProduct; }
      }
      currentProduct = productStartingFrom(index, digits);

    } else {
      currentProduct /= digits[index-1];
      currentProduct *= digits[(index + RESULT_LENGTH) -1];
    }

    if(currentProduct > largestProduct) {
      largestProduct = currentProduct;
    }

    index++;
  }

  return largestProduct;
}

int lookaheadForZero(int start, int digits[DIGITS]) {
  for(int i = start; i < start + RESULT_LENGTH; i++) {
    if(digits[i] == 0) { return i; }
  }
  return -1;
}

unsigned long long productStartingFrom(int start, int digits[DIGITS]) {
  unsigned long long product = 1;
  for(int i = start; i < start + RESULT_LENGTH; i++) {
    product *= digits[i];
  }
  return product;
}

