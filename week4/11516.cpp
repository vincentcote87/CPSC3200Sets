// Problem 11516 - WiFi
// Vincent Cote - CPSC 3200
// Approach - The check functions returns a bool if it can cover all the houses based on a given distance
// and number of access points.
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

bool check(std::vector<double> &arr, double dist, int n) {
	int index = 0;
	for (int i = 0; i < arr.size(); i++) {
		double apPos = arr[i] + dist;
		n--;
		while ((i < arr.size() - 1) && arr[i + 1] - apPos <= dist) {
			i++;
		}
	}
	return n >= 0;
}

void printAnswer(double ans) {
	double intPart, fractPart;
	fractPart = modf(ans, &intPart);
	std::cout<<intPart;
	if (fractPart < 0.5)
		std::cout<<".0";
	else
		std::cout<<".5";
	std::cout<<std::endl;
}

int main(void) {
	int sets;
	std::cin>>sets;
	while (sets--) {
		int n, m, lines;
		std::cin>>n>>m;
		lines = m;
		std::vector<double> houses;
		while (lines--) {
			int temp;
			std::cin>>temp;
			houses.push_back(temp);
		}
		if (m == n) {
			std::cout<<"0.0"<<std::endl;
		} else {
			sort(houses.begin(), houses.end());
			double hi = *(houses.end() - 1);
			double lo = 0.0;
			double shortest = 0.0;
			while (hi - lo > 0.1) {
				double mid = lo + ((hi - lo)/2);
				if (check(houses, mid, n)) {
					shortest = mid;
					hi = mid;
				} else {
					lo = mid;
				}
			}
			printAnswer(shortest);
		}
	}
  return 0;
}
