// 10055 - Hashmat the Brave Warrior
// Vincent Cote - CPSC 3200
#include <iostream>

int main(void) {
  long long x;
  long long y;
  while (std::cin>>x>>y) {
    long long solution = llabs(x - y);
    std::cout<<solution<<std::endl;
  }
  return 0;
}
