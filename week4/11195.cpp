// Problem 11195 - Another n-Queen problem
// Vincent Cote - CPSC 3200
// Approach - Recursivly place queens row by row when possible, if it reaches the end of the board add to count

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
        if (!col[i] && !xDia[row + i] && !yDia[row - i + (n - 1)]) {
          col[i] = true;
          xDia[row + i] = true;
          yDia[row - i + (n - 1)] = true;
          placeQueen(row + 1, n);
          col[i] = false;
          xDia[row + i] = false;
          yDia[row - i + (n - 1)] = false;
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
    std::cout<<"Case "<<index<<": "<<count<<std::endl;
    std::fill_n(col, 15, false);
    std::fill_n(xDia, 30, false);
    std::fill_n(yDia, 30, false);
    count = 0;
  }
  return 0;
}