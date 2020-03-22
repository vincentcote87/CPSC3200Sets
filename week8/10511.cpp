#include <iostream>
#include <sstream>

int main(void) {
	int t;
	std::cin>>t;
	std::cin.ignore();
	std::cin.ignore();
	while (t--) {
		std::string name[1001];
		std::string party[1001];
		std::string club[80000];
		int lineIndex = 1;
		int clubIndex = 3000;
		while (true) {
			std::string str;
			std::getline(std::cin, str);
			if (str == "")
				break;
			std::istringstream iss(str);
			iss>>name[lineIndex]>>party[lineIndex];
			lineIndex++;
			std::string c;
			while (iss>>c) {
				club[clubIndex] = c;
				clubIndex++;
			}

		}

	}
  return 0;
}