#include <iostream>
#include <algorithm>

int main(void) {
  while(true) {
    int graph[200][200] = {};
    int vertices[200] = {};
    int n, l;
    std::cin>>n>>l;
    std::string result = "BICOLORABLE.";
    if (n == 0)
      break;
    while(l--) {
      int v1, v2;
      std::cin>>v1>>v2;
      graph[v1][v2] = graph[v2][v1] = 1;

      
      // if (vertices[v1] == vertices[v2]) {
      //   int c1 = vertices[v1]++;
      //   int c2 = vertices[v2]++;
      //   if (c1 >= 2 || c2 >= 2) {
      //     result = "NOT BICOLORABLE.";
      //     // break;
      //   }
      // }
    }
    std::cout<<result<<std::endl;



    // for (int i = 0; i < n; i++) {
    //   for (int j = 0; j < n; j++) {
    //     std::cout<<graph[i][j]<<" ";
    //   }
    //   std::cout<<std::endl;
    // }
    // std::cout<<std::endl;
  }
}