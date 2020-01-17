// Problem 10189 - Minesweeper
// Vincent Cote - CPSC 3200
// Approach - Store the field in a string, append '.' around the field to not require
// boundry checking. For each position in a string that corresponds to an actual field
// input check how many mines are around it. For each mind found in the 8 surrounding
// positions increment the total by 1.

// Presentation error - Giving an extra line at the end of the program
#include <iostream>

int getCount(std::string str, int i, int n) {
  int count = 0;
  int positions[] = {-1, 1, -n-1, -n-2, -n-3, n+1, n+2, n+3};
  for (int j = 0; j < 8; j++) {
    if (str[i + positions[j]] == '*')
      count++;
  }
  return count;
}

int main(void) {
    int n, m, num = 0;
    while (std::cin>>m>>n && n != 0 && m != 0) {
      num++;
      std::cin.ignore();
      std::string temp;
      std::string dummyRow(n + 2, '.');
      std::string grid = dummyRow;
      for (int i = 0; i < m; i++) {
        std::getline(std::cin, temp);
        grid = grid + "." + temp + ".";
      }
      grid += dummyRow;

      std::cout<<"Field #" + std::to_string(num) + ":"<<std::endl;
      for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
          int index = i * (n+2) + j;
          if (grid[index] == '.') {
            std::cout<<getCount(grid, index, n);
          } else {
            std::cout<<grid[index]; // Output mines
          }
        }
        std::cout<<std::endl;
      }
      std::cout<<std::endl;
    }
  return 0;
}