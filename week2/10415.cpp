// Problem 10415 - Ed Alto Saxophone Player
// Vincent Cote - CPSC 3200
// Approach - Maintain an array for each possible note, maintain a second 2D array for the finger possitions.
// For each note read from input get the fingers required for that note using the index from the notes
// array to get the proper array from the fingers 2D array. I also keep track of the last note, if the current
// fingers required are in the last note do not count them again, else increase by 1 for each finger. The current
// finger counts are maintained in an array of size 11 with the 0 position not used.
#include <iostream>

const std::string notes = "cdefgabCDEFGAB";

const int fingers[14][7] = {
	{2,3,4,7,8,9,10},
	{2,3,4,7,8,9,0},
	{2,3,4,7,8,0,0},
	{2,3,4,7,0,0,0},
	{2,3,4,0,0,0,0},
	{2,3,0,0,0,0,0},
	{2,0,0,0,0,0,0},
	{3,0,0,0,0,0,0},
	{1,2,3,4,7,8,9},
	{1,2,3,4,7,8,0},
	{1,2,3,4,7,0,0},
	{1,2,3,4,0,0,0},
	{1,2,3,0,0,0,0},
	{1,2,0,0,0,0,0}
};

bool inLast(char lastNote, int note) {
	if (lastNote == 'z')
		return false;
	int ind = notes.find(lastNote);
	for (int i = 0; i < 7; i++) {
		if (fingers[ind][i] == note)
			return true;
	}
	return false;
}

int main(void) {
	int x;
	std::cin>>x;
	std::cin.ignore();
	for (int i = 0; i < x; i++) {
		std::string line;
		std::getline(std::cin, line);
		int presses[11] = {0};
		char last = 'z';
		for (int j = 0; j < line.length(); j++) {
			for (int k = 0; k < 7; k++) {
				int note = fingers[notes.find(line[j])][k];
				if (!inLast(last, note))
					presses[note]++;
			}
			last = line[j];
		}
		for (int j = 1; j <= 10; j++) {
			std::cout<<presses[j]<<(j == 10 ? "" : " ");
		}
		std::cout<<std::endl;
	}
	return 0;
}