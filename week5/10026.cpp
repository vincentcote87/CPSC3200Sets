// Problem 10026 - Shoemaker's Problem
// Vincent Cote - CPSC 3200
// Approach - Use a struct to keep track of the job id as well as the ratio between the time and the fine
// Ass discussed in class J1 < J2 iff t1/s1 < t2/s2. Once the data has been processed from the input
// sort the vector on the ratio attribute to get this list
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Job {
    int jobId;
    double ratio;

    Job(int id, double r) {
        jobId = id;
        ratio = r;
    }
};

bool compareRatios(const Job &x, const Job &y) {
    return x.ratio < y.ratio;
}

int main(void) {
    int sets;
    std::cin>>sets;

    while (sets--) {
        std::cin.ignore();
        int n;
        std::cin>>n;
        std::vector<Job> jobs;
        for (int i = 1; i <= n; i++) {
            double time;
            double fine;
            std::cin>>time>>fine;
            Job temp(i, time/fine);
            jobs.push_back(temp);
        }
        std::sort(jobs.begin(), jobs.end(), compareRatios);
        for (int i = 0; i < jobs.size(); i++) {
            std::cout<<jobs[i].jobId;
            if (i != jobs.size() - 1)
                std::cout<<" ";
        }
        std::cout<<std::endl;
        if (sets > 0)
            std::cout<<std::endl;
    }
    return 0;
}