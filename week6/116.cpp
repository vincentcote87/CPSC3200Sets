// start from last col and check shortest path for each row, repeat, keep track of direction

#include <iostream>
#include <vector>

struct sumStruct {
  int sum;
  int dir;
  sumStruct(int s, int d) {
    sum = s;
    dir = d;
  }
};

int getMin(const int x[3]) {
  int smallest = x[0];
  int index = 0;
  for (int i = 0; i < 3; i++) {
    if (x[i] <= smallest) {
      smallest = x[i];
      index = i;
    }
  }
  return index;
}

int main(void) {
  while (true) {
    int m, n;
    std::cin>>m>>n;
    if (std::cin.eof())
      break;
    std::vector<std::vector<int> > matrix(m, std::vector<int>(n, -1));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int temp;
        std::cin>>temp;
        matrix[i][j] = temp;
      }
    }
    sumStruct tmpSum(-1, -2);
    std::vector<std::vector<sumStruct> > sumMatrix(m, std::vector<sumStruct>(n, tmpSum));
    for (int i = 0; i < m; i++) {
      sumStruct tmpSum(matrix[i][n-1], -2);
      sumMatrix[i][n-1] = tmpSum;
    }

    for(int col = n - 2; col >= 0; col--) {
      for (int row = m - 1; row >= 0; row--) {
        int rows[3] = {(row + 1) % m, (row - 1) >= 0 ? row - 1 : m - 1, row};
        int val[3] = {matrix[rows[0]][col + 1], matrix[rows[1]][col + 1], matrix[rows[2]][col + 1]};
        int minIndex = getMin(val);
        sumMatrix[row][col].sum = matrix[row][col] + sumMatrix[rows[minIndex]][col + 1].sum;
        sumMatrix[row][col].dir = minIndex - 1;
      }
    }

    int shortest = INT16_MAX;
    int index = 0;
    for (int i = 0; i < m; i++) {
      if (sumMatrix[i][0].sum < shortest) {
        shortest = sumMatrix[i][0].sum;
        index = i;
      }
    }
    int direction = index;
    for (int i = 0; i < n; i++) {
      std::cout<<direction + 1;
      if (i != n - 1)
        std::cout<<" ";
      int temp = direction + sumMatrix[direction][i].dir;
      direction = temp >= 0 ? temp % m : m - 1;
    }
    std::cout<<std::endl<<sumMatrix[index][0].sum<<std::endl;
  }
  return 0;
}