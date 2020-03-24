// Problem 11367 - Full Tank?
// Vincent Cote - CPSC 3200
// Approach - Building the graph as discusted in class where the weight of the edges
// are added when filling up without changin cities. Then complete the graph by adding
// edges with 0 weight. After the graph is complete run provided Dijstra_sparse
// to get the shortest path from s to e. If the city is reachable, we can assume the
// cheapest way to get to e the car will arrive there with 0 gas left, therefore
// we look at node e that has fule level equal to 0.

/*
 * Dijkstra's Algorithm for sparse graphs
 *
 * Author: Howard Cheng
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (-1 if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 * This version works well if the graph is not dense.  The complexity
 * is O((n + m) log (n + m)) where n is the number of vertices and
 * m is the number of edges.
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;


struct Edge {
  int to;
  int weight;       // can be double or other numeric type
  Edge(int t, int w)
    : to(t), weight(w) { }
};
  
typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new vector<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight)
  {
    nbr[u].push_back(Edge(v, weight));
  }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P, int c)
{
  typedef pair<int,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
			if (v % 101 > c) continue;
      int weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	P[v] = u;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int get_path(int v, const vector<int> &P, vector<int> &path)
{
  path.clear();
  path.push_back(v);
  while (P[v] != -1) {
    v = P[v];
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return path.size();
}

int main(void) {
	int n, m;
	std::cin>>n>>m;
	int p[1000];
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin>>tmp;
		p[i] = tmp;
	}
	int numOfNodes = n * 101;
	Graph G(numOfNodes);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 100; j++) {
			int n1 = (i * 101) + j;
			int n2 = (i * 101) + (j + 1);
			G.add_edge(n1,n2,p[i]);
		}
	}

	for (int i = 0; i < m; i++) {
		int u, v, d;
		std::cin>>u>>v>>d;
		int k = 0;
		for (int j = d; j < 100; j++) {
			int n1 = (u * 101) + j;
			int n2 = (v * 101) + k;
			G.add_edge(n1,n2,0);
			n1 = (v * 101) + j;
			n2 = (u * 101) + k;
			G.add_edge(n1,n2,0);
			k++;
		}
	}

	int q;
	std::cin>>q;
	while (q--) {
		int c, s, e;
		std::cin>>c>>s>>e;
		vector<int> D, P, path;
		s = s * 101;
		dijkstra(G, s, D, P, c);
		e = (e * 101);
		get_path(e, P, path);
		if (D[e] != -1)
			std::cout<<D[e]<<std::endl;
		else
			std::cout<<"impossible"<<std::endl;
	}
  return 0;
}