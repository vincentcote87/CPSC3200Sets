// Problem 10656 - Maximum Sum (II)
// Vincent Cote - CPSC 3200
// Approach - Loop through the inputs, if it is not zero add it to the vector. After all inputs
// have been processed, if the vector is empty then it means all inputs where 0 therefore
// push a single 0 to the vector and print ans.
#include <iostream>
#include <vector>

void printAns(std::vector<int> ans) {
    for (int i = 0; i < ans.size(); i++) {
        std::cout<<ans[i];
        if (i != ans.size() - 1)
            std::cout<<" ";
    }
    std::cout<<std::endl;
}

int main(void) {
    while (true) {
        int n;
        std::cin>>n;
        if (n == 0)
            return 0;
        std::vector<int> subSeq;
        while (n--) {
            int temp;
            std::cin>>temp;
            if (temp != 0)
                subSeq.push_back(temp);
        }
        if (subSeq.size() <= 0)
            subSeq.push_back(0);
        printAns(subSeq);
    }

    return 0;
}