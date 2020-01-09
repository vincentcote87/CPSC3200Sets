// Problem 305 - Joseph
// Vincent Cote - CPSC 3200
#include <iostream>

bool isValid(const int m, const int k) {
    int i = 0;
    int total = 2 * k;
    while (total > k) {
        i = (i-1+m) % total;
        if (i >= k)
            total--;
        else
            return false;
    }
    return true;
}

int main (void) {
    int ans[14];
    int k;
    // pre-calculate all possible values
    for (int k = 1; k < 14; ++k) {
        int m = k;
        while (!isValid(m, k))
            m++;
        ans[k] = m;
    }

    while (true) {
        std::cin>>k;
        if (k == 0)
            return 0;
        std::cout<<ans[k]<<std::endl;
    }
}
