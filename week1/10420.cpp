// 10420 - List of Conquests
// Vincent Cote - CPSC 3200
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

void printAns(std::string contry, int count) {
	std::cout<<contry + " " + std::to_string(count)<<std::endl;
}

int main(void) {
	int n;
	int count;
	std::string line;
	std::vector<std::string> contries;
		std::cin>>n;
		// Build a vector with all the contries
		for (int i = 0; i <= n; i++) {
			std::getline(std::cin, line);
			std::istringstream iss(line);
			iss>>line;
			contries.push_back(line);
		}
		std::sort(contries.begin(), contries.end());
		std::string last = contries[1];
		count = 1;
		for (int i = 2; i < contries.size(); i++) {
			if (contries[i] == last) {
				count++;
			} else {
				printAns(last, count);
				last = contries[i];
				count = 1;
			}
			if (i == contries.size() - 1)
				printAns(last, count);
		}
  return 0;
}
