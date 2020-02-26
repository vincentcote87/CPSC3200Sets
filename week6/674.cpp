// Problem 674 - Coin Change
// Vincent Cote - CPSC 3200
// Approach - Since the total number of coins we need to consider is small I start by building
// a table with all the values for how many ways each sum can be calculated then I access
// this value from the table. Since the table is initialized with 1 for the first element and
// 0 for the rest, when i = 0 will fill the table with 1 (meaning with coins of 1 there is
// 1 way to get the sum).
#include <iostream>

int denom[] = {1,5,10,25,50};
long int table[7550] = {1};

void fillTable() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7500; j++) {
      table[denom[i] + j] += table[j];
    }
  }
}

int main(void) {
  fillTable();
  int sum;
  while(std::cin>>sum) {
    std::cout<<table[sum]<<std::endl;
  }
  return 0;
}
