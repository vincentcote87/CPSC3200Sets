// start from last col and check shortest path for each row, repeat, keep track of direction

#include <iostream>
#include <vector>

struct sumStruct {
  int sum;
  int dir;
}

int getMin(const int x[3]) {
  int smallest = x[0];
  int index = 0;
  for (int i = 0; i < 3; i++) {
    if (x[i] <= smallest)
      index = i;
  }
  return index;
}

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
    }
    std::vector<std::vector<sumStruct>> sumMatrix;
    // std::vector<int> path;
    // int total = INT16_MAX;
    // for (int i = m - 1; i >= 0; i--) {
    //   std::vector<int> tmpPath;
    //   tmpPath.push_back(i);
    //   int tmpTotal = matrix[i][n-1];
    //   for (int col = n - 1; col > 0; col--) {
    //     int row = tmpPath.back();
    //     int vals[3] = {matrix[((row -1) >= 0 ? row - 1 : m - 1)][col - 1], matrix[row][col - 1], matrix[(row + 1) % m][col - 1]};
    //     int minIndex = getMin(vals);
    //     tmpTotal += vals[minIndex];
    //     if (minIndex == 2)
    //       tmpPath.push_back((row + 1) % m);
    //     else if (minIndex == 1)
    //       tmpPath.push_back(row);
    //     else
    //       tmpPath.push_back((row -1) >= 0 ? row - 1 : m - 1);
    //   }
    //   if (tmpTotal <= total) {
    //     total = tmpTotal;
    //     path = tmpPath;
    //   }
    // }
    // for (int i = path.size() - 1; i >= 0; i--) {
    //   std::cout<<path[i] + 1<<" ";
    // }
    // std::cout<<std::endl<<total<<std::endl;
  }
  return 0;
}