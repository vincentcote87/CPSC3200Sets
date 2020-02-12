// start from last col and check shortest path for each row, repeat, keep track of direction

#include <iostream>
#include <vector>

struct shortest {
  int val;
  int dir; //1 is up, 2 is right, 3 is down
};

int main(void) {
  while (true) {
    int m, n;
    std::cin>>m>>n;
    if (std::cin.eof())
      break;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int temp;
        std::cin>>temp;
        matrix[i][j] = temp;
      }
      // Process input here
    }
  }
  return 0;
}