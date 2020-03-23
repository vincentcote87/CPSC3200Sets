// Problem 10192 - Vacation
// Vincent Cote - CPSC 3200
// Approach - Using the lowest common subsequence approach I start by filling
// the table based on s and t. Once the table is built I look up the value in the table.
#include <iostream>

int table[105][105] = {0};
std::string s, t;

void resetTable() {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			table[i][j] = 0;
}

void fillTable() {
	resetTable();

	for (int i = 1; i <= s.length(); i++) {
		for (int j = 1; j <= t.length(); j++) {
			if (s[i-1] == t[j-1]) {
				table[i][j] = table[i-1][j-1] + 1;
			} else {
				table[i][j] = std::max(table[i-1][j], table[i][j-1]);
			}
		}
	}
}

int main(void) {
	int caseNum = 1;
	while (true) {
		s = t = "";
		std::getline(std::cin, s);
		if (s == "#")
			return 0;
		std::getline(std::cin, t);
		fillTable();
		std::cout<<"Case #"<<caseNum<<": you can visit at most "<<table[s.length()][t.length()]<<" cities."<<std::endl;
		caseNum++;
	}
}
