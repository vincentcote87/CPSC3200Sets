// Problem 296 - Safebreaker
// Vincent Cote - CPSC 3200
// Approach - Run through all possible values from 0000 to 9999 and test if the
// possible solution against the input data, if it provides the same result only once
// then we found the secret code, if it gives more then one then it is indeterminate
// else if it finds none it is impossible.
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
  int sets;
  std::cin>>sets;
  while (sets--) {
    int guesses;
    std::cin>>guesses;
    std::vector<std::string> codes;
    std::vector<std::string> results;
    std::vector<std::string> answers;
    if(guesses == 0) { // hacky way to get indeterminate when input is 0
      answers.push_back("indeterminate");
      answers.push_back("indeterminate");
    }
    while (guesses--) {
      std::string code, result;
      std::cin>>code>>result;
      codes.push_back(code);
      results.push_back(result);
    }
    for (int a = 0; a < 10; a++)
      for(int b = 0; b < 10; b++)
        for (int c = 0; c < 10; c++)
          for (int d = 0; d < 10; d++) {
            std::string ans = std::to_string(a) + std::to_string(b) + std::to_string(c) + std::to_string(d);
            for (int i = 0; i < codes.size(); i++) {
              if (eval(ans, codes[i]) != results[i]) {
                break;
              }
              if (i == codes.size() - 1)
                answers.push_back(ans);
            }
          }
    if (answers.size() == 0)
      std::cout<<"impossible"<<std::endl;
    else if (answers.size() == 1)
      std::cout<<answers[0]<<std::endl;
    else
      std::cout<<"indeterminate"<<std::endl;
  }
  return 0;
}