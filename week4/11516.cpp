// Problem 11516 - WiFi
// Vincent Cote - CPSC 3200
// Approach -
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
	ans = floor((ans*2)+0.5)/2;
	fractPart = modf(ans, &intPart);
	std::cout<<ans;
	if (fractPart == 0 || intPart == 0)
		std::cout<<".0";
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
			// std::cout.precision(2);
			// std::cout<<(floor((shortest*2)+0.5)/2)<<std::endl;
			printAnswer(shortest);
		}
	}
  return 0;
}