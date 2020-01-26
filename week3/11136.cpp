// Problem 11136 Hoax or What
// Vincent Cote - CPSC 3200
// Approach - Using a multiset as the data structure, while iterating through the bills take the front and back of the multiset
// to get the difference which is added to a running total then remove them from the set.
#include <iostream>
#include <set>

int main(void) {
	int days;
	while (true) {
		std::cin>>days;
		if (days == 0)
			return 0;
		std::multiset<int> mSet;
		long long totalPaid = 0;
		while (days--) {
			int k;
			std::cin>>k;
			while(k--) {
				int temp;
				std::cin>>temp;
				mSet.insert(temp);
			}
			int lowest = *mSet.begin();
			int highest = *(--mSet.end());
			totalPaid += highest - lowest;
			mSet.erase(mSet.begin());
			mSet.erase(--mSet.end());
		}
		std::cout<<totalPaid<<std::endl;
	}
}