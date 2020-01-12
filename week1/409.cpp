// Problem 409 - Excuses, Excuses!
// Vincent Cote - CPSC 3200
#include <iostream>
#include <vector>
#include <sstream>

int main(void) {
    int numOfWords;
    int numOfExcuses;
    int count = 0;
    std::string temp;
    std::string worstExcuse;
    std::vector<std::string> words;
    std::vector<std::string> excuses;

    while (!std::cin.eof()) {
        std::cin>>numOfWords>>numOfExcuses;
        for (int i = 0; i < numOfWords; i++) {
            std::cin>>temp;
            words.push_back(temp);
        }
        for (int i = 0; i < numOfExcuses; i++) {
            std::getline(std::cin, temp);

            std::istringstream iss(temp);
            while (iss >> temp) {
                for (int i = 0; i < temp.size(); i++) {
                    isalpha(temp[i]) ? temp[i] = tolower(temp[i]) : temp[i] = ' ';
                    // std::cout<<temp[i]<<std::endl;
                }
                std::cout<<temp<<std::endl;
            }
            // excuses.push_back(temp);
        }

        // std::cout<<numOfWords<<" "<<numOfExcuses<<std::endl;
    }


    return 0;
}