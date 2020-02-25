// Problem 497 - Strategic Defense Initiative
// Vincent Cote - CPSC 3200
// Approach - Using the dynamic programming approach I run the algorithm on the missile
// array and build the second array showing the longest increasing subsequences for each
// index position. Since there is only one correct solution I know there is only going to
// be a single longest value in the array, from this position I build the sequence backwards
// then print it from back to front.

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<int> getLIS(std::vector<int> li) {
  int n = li.size();
  std::vector<int> arr(n, 1);
  int k;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (li[j] < li[i]) {
        k = arr[j] + 1;
        arr[i] = std::max(arr[i], k);
      }
    }
  }
  return arr;
}

int getLargest(std::vector<int> x) {
  int largest = 1;
  for (int i = 0; i < x.size() - 1; i++) {
    int tmp = std::max(x[i], x[i+1]);
    if (tmp > largest)
      largest = tmp;
  }
  return largest;
}

void printAns(std::vector<int> x, std::vector<int> m) {
  int y = getLargest(x);
  std::vector<int> li;
  li.push_back(INT32_MAX);
  while (y > 0) {
    int tmp = INT32_MIN;
    for (int i = x.size() - 1; i >= 0; i--) {
      if (x[i] == y) {
        if (m[i] > tmp && m[i] < *(li.end() - 1)) {
          tmp = m[i];
        }
      }
    }
    li.push_back(tmp);
    y--;
  }
  for (int i = li.size() - 1; i > 0; i--) {
    std::cout<<li[i]<<std::endl;
  }
}

int main(void) {
  int sets;
  std::cin>>sets;
  std::cin.ignore();
  std::cin.ignore();
  while (sets--) {
    std::vector<int> missiles;
    while (true) {
      std::string line;
		  std::getline(std::cin, line);
      if (line.length() == 0)
        break;
      std::stringstream iss(line);
      int temp;
      iss>>temp;
      missiles.push_back(temp);
    }
    std::vector<int> lis = getLIS(missiles);
    std::cout<<"Max hits: "<<getLargest(lis)<<std::endl;
    printAns(lis, missiles);
    if (sets != 0)
      std::cout<<std::endl;
  }
  return 0;
}