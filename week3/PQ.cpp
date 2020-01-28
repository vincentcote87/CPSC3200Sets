#include <iostream>
#include <queue>

struct pqList {
  std::priority_queue<int> maxQ;
  std::priority_queue<int> minQ;

  void add(int x) {
    if (maxQ.empty())
      maxQ.push(x);
    else if (x >= maxQ.top())
      minQ.push(x * -1);
    else
      maxQ.push(x);
    if (maxQ.size() > minQ.size()) {
      minQ.push(maxQ.top() * -1);
      maxQ.pop();
    }
  }

  void pushMin(int times) {
    while(times--) {
      minQ.push(maxQ.top() * -1);
      maxQ.pop();
    }
  }

  void pushMax(int times) {
    while (times--) {
      maxQ.push(minQ.top() * -1);
      minQ.pop();
    }

  }

  int get(int index) {

  }

  int size() {
    return maxQ.size() + minQ.size();
  }
};

int main(void) {
  pqList a;
  a.add(20);
  a.add(30);
  // a.add(1);
  // a.add(2);
  std::cout<<a.maxQ.size()<<std::endl;
  std::cout<<a.minQ.size()<<std::endl;
  std::cout<<a.maxQ.top()<<std::endl;
  std::cout<<(a.minQ.top() * -1)<<std::endl;
  // std::cout<<a.get(1)<<std::endl;
  // std::cout<<a.get(2)<<std::endl;
}