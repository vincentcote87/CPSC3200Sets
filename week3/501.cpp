// 2 Priority queues
// left has max on top, right has min on top

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
};

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

    int i = 0;
    std::priority_queue<int> maxQ;
    Min_priority_queue minQ;
    for (int j = 0; j < u.size(); j++) {
      int size = maxQ.size() + minQ.size();
      if (u[j] > size) {
        
      }
    }
  }




  // std::priority_queue<int> maxQ;
  // Min_priority_queue minQ;
  // int arr[11] = {33,55,23,87,45,7,12,-12,-44,64,2};
  // for (int i = 0; i < 11; i++) {
  //   maxQ.push(arr[i]);
  //   minQ.push(arr[i]);
  // }

  // std::cout<<maxQ.top()<<std::endl;
  // std::cout<<minQ.top()<<std::endl;
  // std::cout<<minQ.size()<<std::endl;
  return 0;
}