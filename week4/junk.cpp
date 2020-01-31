// Problem 296 - Safebreaker
// Vincent Cote - CPSC 3200
// Approach -
#include <iostream>
#include <vector>

std::string eval(std::string ans, std::string test) {
  int posAndValue = 0;
  int posOnly = 0;
  for (int i = 0; i < 4; i++) {
    if (ans[i] == test[i]) {
      posAndValue++;
      ans.replace(i,1,"*");
      test.replace(i,1,"?");
    }
  }
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if (test[j] == ans[i]) {
        posOnly++;
        test.replace(j,1,"?");
        break;
      }
    }
  return std::to_string(posAndValue) + "/" + std::to_string(posOnly);
}

int main(void) {
  // std::string x = "0000";
  // std::size_t y = x.find("0",4);
  // std::cout<<y<<std::endl;
  while(true) {
    std::string x, y;
    std::cin>>x>>y;
    std::cout<<eval(x,y)<<std::endl;
  }
  return 0;
}