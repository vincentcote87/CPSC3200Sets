// Problem 11195 - Another n-Queen problem
// Vincent Cote - CPSC 3200
// Approach -
#include <iostream>
#include <algorithm>

bool col[15] = {false};
bool xDia[30] = {false};
bool yDia[30] = {false};
char grid[15][15] = {'.'};
int count = 0;

void placeQueen(int row, int n) {
  if (row >= n)
    count++;
  else {
    for (int i = 0; i < n; i++) {
      if (grid[row][i] != '*') {
        if (!(col[i] && xDia[row + i] && yDia[row - i + (n - 1)])) {
          col[i] = true;
          xDia[row + i] = true;
          yDia[row - i + (n - 1)] = true;
          placeQueen(row + 1, n);
        }
      }
    }
  }
}

int main(void) {
  int index = 0;
  while (true) {
    index++;
    int n;
    std::cin>>n;
    if (n == 0)
          break;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char temp;
        std::cin>>temp;
        grid[i][j] = temp;
      }
    }
    placeQueen(0, n);
    std::cout<<count<<std::endl;

  }
  return 0;
}

// recursive function to add queen
// bool col[15] = {false}
// diagonal from left to right - row + col
// diagonal from right to left -