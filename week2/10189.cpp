// Problem 10189 - Minesweeper
// Vincent Cote - CPSC 3200
#include <iostream>

int getCount(std::string str, int i) {
  int count = 0;

  return count;
}

int main(void) {
    int n, m;
    while (std::cin>>m>>n && n != 0 && m != 0) {
      std::cin.ignore();
      std::string temp;
      std::string dummyRow(n + 2, '.');
      std::string grid = dummyRow;
      for (int i = 0; i < m; i++) {
        std::getline(std::cin, temp);
        grid = grid + "." + temp + ".";
      }
      grid += dummyRow;

      for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
          int index = i * (n+2) + j;
          if (grid[index] == '.') {
            std::cout<<getCount(grid, index);
          } else {
            std::cout<<grid[index];
          }
        }
        std::cout<<std::endl;
      }



      std::cout<<grid<<std::endl;



      // std::string row1(n + 2, '.');

      // std::string row2 = "", row3 = "";
      // std::getline(std::cin, row2);
      // std::getline(std::cin, row3);
      // row2 = "." + row2 + ".";
      // row3 = "." + row3 + ".";
      // for (int i = 1; i < row2.length() - 1; i++) {
      //   if (row2[i] == '.') {
      //     for ( int j = 0; j < 3; j++) {

      //     }
      //   } else {
      //     std::cout<<row2[i];
      //   }
      // }



      // std::cout<<row1<<std::endl;
      // std::cout<<row2<<std::endl;
      // std::cout<<row3<<std::endl;
    }
  return 0;
}