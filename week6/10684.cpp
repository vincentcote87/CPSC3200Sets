// Kaban's algorithim?
// Code library vecsum.cc

#include <iostream>
#include <vector>

int getMax(std::vector<int> v) {
  int max = 0;
  for (int i = 0; i < v.size(); i++) {
    
  }
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
  }
  return 0;
}