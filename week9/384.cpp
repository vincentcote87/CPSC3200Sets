// Problem 384 - Slurpys
// Vincent Cote - CPSC 3200
// Approach - Two recursive functions used to check if a string is a slump or a slimp.
// To check if a sting is a slurpy it itterates over the entire string splitting it up
// into 2 strings then checking if the first half is a slimp and the other half a slump.
#include <iostream>
#include <string>

bool isSlump(std::string str) {
	if (str.length() > 2) {
		if ((str[0] == 'D' || str[0] == 'E') && str[1] == 'F') {
			str.erase(0, 2);
			while (str.length() > 0) {
				if (str[0] != 'F') {
					if (str[0] == 'G' && str.length() == 1)
						return true;
					return isSlump(str);
				}
				str.erase(str.begin());
			}
		}
	}
	return false;
}

bool isSlimp(std::string str) {
	if (str.length() > 1) {
		if (str == "AH")
			return true;
		if (str[0] == 'A' && str[1] == 'B' && str[str.length() - 1] == 'C') {
			str.erase(0, 2);
			str.erase(str.end() - 1);
			return isSlimp(str);
		}
		if (str[0] == 'A' && str[str.length() - 1] == 'C') {
			str.erase(str.begin());
			str.erase(str.end() - 1);
			return isSlump(str);
		}
	}
	return false;
}

bool isSlurpy(std::string str) {
	std::string slimp = "", slump;
	while (str.length() > 1) {
		slimp += str[0];
		str.erase(str.begin());
		slump = str;
		if (isSlimp(slimp))
			if (isSlump(slump))
				return true;
	}
	return false;
}

int main(void) {
	int n;
	std::cin>>n;
	std::cout<<"SLURPYS OUTPUT"<<std::endl;
	while (n--) {
		std::string str;
		std::cin>>str;
		std::cout<<(isSlurpy(str) ? "YES" : "NO")<<std::endl;
	}
	std::cout<<"END OF OUTPUT"<<std::endl;
}