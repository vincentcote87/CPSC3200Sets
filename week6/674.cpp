// recursion, going through all the coin types
// f(sum, n) n = # of denomination, sum = the number of ways to solve using n
// denom[] = {1, 5, 10, 25, 50}

// sum of { f(sum - k, n - 1)  int k = sum/denom[n-1]}
// base case f(?, 1) = 1 if ? >= 0

#include <iostream>

int denom[] = {1,5,10,25,50};

int howMany(int sum, int denom) {
  if (denom <= 1)
    return 1;
  int k = sum/denom;
  
}

int main(void) {
  
  return 0;
}