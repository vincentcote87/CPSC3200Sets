// Problem 305 - Joseph
// Vincent Cote - CPSC 3200

//TO SLOW :(
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

int main(void) {
    int k;
    int m;
    while (true) {
        std::cin>>k;
        if (k == 0)
            return 0;
        m = k;
        while (!isValid(m, k))
            m++;
        std::cout<<m<<std::endl;
    }

}