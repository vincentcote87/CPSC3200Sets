// Problem 10684 - The jackpot
// Vincent Cote - CPSC 3200
// Approach - To find the longest streak run through the array one element at a time and
// add its value to the running total, keep track of the highest total. If the running total
// ever falls below 0 restart the running total at 0 and continue.
#include <iostream>
#include <vector>

int getMax(std::vector<int> v) {
  int max = 0;
  int tmp = 0;
  for (int i = 0; i < v.size(); i++) {
    tmp += v[i];
    if (tmp > max)
      max = tmp;
    if (tmp < 0)
      tmp = 0;
  }
  return max;
}

int main(void) {
  while (true) {
    int n;
    std::cin>>n;
    if (n == 0)
      return 0;
    std::vector<int> streak;
    while (n--) {
      int temp;
      std::cin>>temp;
      streak.push_back(temp);
    }
    int max = getMax(streak);
    if (max > 0) {
      std::cout<<"The maximum winning streak is "<<max<<"."<<std::endl;
    } else {
      std::cout<<"Losing streak."<<std::endl;
    }
  }
  return 0;
}