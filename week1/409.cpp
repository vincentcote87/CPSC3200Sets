// Problem 409 - Excuses, Excuses!
// Vincent Cote - CPSC 3200
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int main(void) {
    int numOfWords;
    int numOfExcuses;
    int count = 0;
    int worst = 0;
    int index = 0;
    std::string temp;
    std::string worstExcuse;
    std::string currentExcuse;
    std::vector<std::string> words;

    while (true) {
        index++;
        count = -1;
        worst = -1;
        worstExcuse = "";
        words.clear();
        std::cin>>numOfWords>>numOfExcuses;
        if (std::cin.eof())
          break;
        for (int i = 0; i < numOfWords; i++) {
            std::cin>>temp;
            words.push_back(temp);
        }
        std::cin.ignore();
        for (int i = 0; i < numOfExcuses; i++) {
          count = 0;
          std::getline(std::cin, temp);
          currentExcuse = temp;
          for (int j = 0; j < temp.length(); j++) {
            isalpha(temp[j]) ? temp[j] = tolower(temp[j]) : temp[j] = ' ';
          }
          std::istringstream iss(temp);
          while (iss >> temp) {
            if (std::find(words.begin(), words.end(), temp) != words.end()) {
              count++;
            }
          }
          if (count > worst) {
            worst = count;
            worstExcuse = "\n" + currentExcuse;
          } else if (count == worst)
            worstExcuse += "\n" + currentExcuse;
      }
      std::cout<<"Excuse Set #" + std::to_string(index);
      std::cout<<worstExcuse<<std::endl<<std::endl;
    }
    return 0;
}