// Problem 501 - Black Box
// Vincent Cote - CPSC 3200
// Approach - Using two priority queues to maintain the index position of i in the black box. One priority queue keeps the max
// while the other keeps the min with all values in the min queue greater then the values in the max queue. Keeping track of
// the size of the max priority queue is used to maintained the index position requested from the black box. For min queue I made a simple
// struct to negate the push and top.
#include <iostream>
#include <vector>
#include <queue>

struct Min_priority_queue {
  std::priority_queue<int> minQ;
  void push(int x) {
    minQ.push(x * -1);
  }
  int top() {
    return minQ.top() * -1;
  }
  size_t size() {
    return minQ.size();
  }
  void pop() {
    minQ.pop();
  }
};

void pushToMinQueue(std::priority_queue<int> &from, Min_priority_queue &to) {
  to.push(from.top());
  from.pop();
}

void pushToMaxQueue(Min_priority_queue &from, std::priority_queue<int> &to) {
  to.push(from.top());
  from.pop();
}

int main(void) {
  int sets;
  std::cin>>sets;
  std::cin.ignore();
  while(sets--) {
    int M, N;
    std::vector<int> A;
    std::vector<int> u;
    std::cin>>M>>N;
    for (int i = 0; i < M; i++) {
      int x;
      std::cin>>x;
      A.push_back(x);
    }
    for (int i = 0; i < N; i++) {
      int x;
      std::cin>>x;
      u.push_back(x);
    }

    int i = 1;
    std::priority_queue<int> maxQ;
    Min_priority_queue minQ;
    for (int j = 0; j < u.size(); j++) {
      while (int totalSize = maxQ.size() + minQ.size() < u[j]) {
        int temp = A[0];
        A.erase(A.begin());
        if (maxQ.empty()) {
          maxQ.push(temp);
        } else {
          if (temp > maxQ.top())
            minQ.push(temp);
          else
            maxQ.push(temp);
        }
      }
      while (maxQ.size() != i) {
        if (maxQ.size() > i)
          pushToMinQueue(maxQ, minQ);
        else if (maxQ.size() < i)
          pushToMaxQueue(minQ, maxQ);
      }
      i++;
      std::cout<<maxQ.top()<<std::endl;
    }
    if (sets != 0)
      std::cout<<std::endl;
  }
  return 0;
}