// Problem 10004 - Bicoloring
// Vincent Cote - CPSC 3200
// Approach - Start by building the graph using a matrix. Once graph is built, run through the graph starting at 0
// using breath first, get the neighbors of each vertex, if its colour is -1 then flip its colour to the oposite of
// the vertex. If the colour is ever the same as the neighbour then it is not 2 colourable.
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

std::vector<int> getNeighbors(const int m[200][200], int row) {
  std::vector<int> neighbors;
  for (int i = 0; i < 200; i++) {
    if (m[row][i] == 1)
      neighbors.push_back(i);
  }
  return neighbors;
}

std::string bfs(const int m[200][200], const int n) {
  int color[200];
  for (int i = 0; i < 200; i++) {
    color[i] = -1;
  }
  std::queue<int> q;
  q.push(0);
  color[0] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    std::vector<int> neighbors = getNeighbors(m, v);
    for (int w = 0; w < neighbors.size(); w++) {
      if (color[neighbors[w]] < 0) {
        q.push(neighbors[w]);
        color[neighbors[w]] = 1 - color[v];
      } else if (color[neighbors[w]] == color[v])
          return "NOT BICOLORABLE.";
    }
  }
  return "BICOLORABLE.";
}

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
    }
    std::cout<<bfs(graph, n)<<std::endl;
  }
}