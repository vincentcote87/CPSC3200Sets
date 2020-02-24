// Problem 116 - Unidirectional TSP
// Vincent Cote - CPSC 3200
// Approach - Build a matrix with the same size of the input, starting from the bottom right add up
// the min of the 3 possible positions, keep this running sum in the new matrix. Once the minumum
// has been found check which direction it came from, if they are equal keep the smallest row index.
// keep track of direction with -1, 0, 1 to identify which row it came from.
#include <iostream>
#include <vector>
#include <algorithm>

struct sumStruct {
  int sum;
  int dir;
  sumStruct(int s, int d) {
    sum = s;
    dir = d;
  }
};

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
        int pos[3] = {(row + m - 1) % m, row, (row + 1) % m};
        int minVal = std::min(sumMatrix[pos[0]][col + 1].sum, std::min(sumMatrix[pos[1]][col + 1].sum, sumMatrix[pos[2]][col + 1].sum));
        sumMatrix[row][col].sum = matrix[row][col] + minVal;
        for (int k = 0; k < 3; k++) {
          int x[3] = {-1, 0, 1};
          int smallest = INT16_MAX;
          if (sumMatrix[pos[0] % m][col + 1].sum == minVal) {
            if (pos[0] < smallest) {
              smallest = pos[0];
              sumMatrix[row][col].dir = x[0];

            }
          }
          if (sumMatrix[pos[1]][col + 1].sum == minVal) {
            if (pos[1] < smallest) {
              smallest = pos[1];
              sumMatrix[row][col].dir = x[1];
            }
          }
          if (sumMatrix[pos[2]][col + 1].sum == minVal) {
            if (pos[2] < smallest) {
              smallest = pos[2];
              sumMatrix[row][col].dir = x[2];
            }
          }
        }
      }
    }

    // Get row with smallest element in position 0
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