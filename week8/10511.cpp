/*
 * Network Flow
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  Note that the graph is modified.  If you wish to
 * recover the flow on an edge, it is in the "flow" field, as long as
 * is_real is set to true.
 *
 * Note: if you have an undirected network. simply call add_edge twice
 * with an edge in both directions (same capacity).  Note that 4 edges
 * will be added (2 real edges and 2 residual edges).  To discover the
 * actual flow between two vertices u and v, add up the flow of all
 * real edges from u to v and subtract all the flow of real edges from
 * v to u.  (In fact, for a residual edge the flow is always 0 in this
 * implementation.)
 *
 * This code can also be used for bipartite matching by setting up an
 * appropriate flow network.
 *
 * The code here assumes an adjacency list representation since most
 * problems requiring network flow have sparse graphs.
 *
 * This is the basic augmenting path algorithm and it is not the most
 * efficient.  But it should be good enough for most programming contest
 * problems.  The complexity is O(f m) where f is the size of the flow
 * and m is the number of edges.  This is good if you know that f
 * is small, but can be exponential if f is large.
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <sstream>
#include <map>

using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;
  
  Edge(int t, int c, bool real = true)
    : to(t), cap(c), flow(0), is_real(real)
  {};

  int residual() const
  {
    return cap - flow;
  }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new list<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap)
  {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow)
{
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
		    vector<bool> &visited, int step = 0)
{
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1) {
	return it->residual();
      } else if (flow > 0) {
	return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t)
{
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);
  
  return flow;
}

std::string getKey(map<std::string,int> m, int i) {
  map<std::string,int>::iterator it = m.begin();
  while (it != m.end()) {
    if (it -> second == i) {
      std::string str = it -> first;
      return str;
    }
    it++;
  }
  return NULL;
}

int main(void) {
	int t;
	std::cin>>t;
	std::cin.ignore();
	std::cin.ignore();
	while (t--) {
		map<std::string,int> nameMap;
		map<std::string,int> partyMap;
		map<std::string,int> clubMap;
    std::string people[1000][100];
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j < 100; j++) {
        people[i][j] = "";
      }
    }
    int peopleIndex = 0;
		while (true) {
      int clubIndex = 2;
			std::string str;
			std::getline(std::cin, str);
			if (str == "")
				break;
			std::istringstream iss(str);
			std::string name, party;
			iss>>name>>party;
      people[peopleIndex][0] = name;
      people[peopleIndex][1] = party;
			nameMap[name] = nameMap.size();
			if (partyMap.find(party) == partyMap.end()) {
        int n = partyMap.size();
				partyMap[party] = n;
			}
			std::string club;
			while (iss>>club) {
        people[peopleIndex][clubIndex] = club;
        clubIndex++;
				if (clubMap.find(club) == clubMap.end()) {
          int n = clubMap.size();
					clubMap[club] = n;
				}
			}
      peopleIndex++;
		}

    int nodeCount = 2 + nameMap.size() + partyMap.size() + clubMap.size();
    Graph G(nodeCount);
    int clubModifier = 2;
    int nameModifier = clubModifier + clubMap.size();
    int partyModifier = nameModifier + nameMap.size();
    for (int i = 0; i < clubMap.size(); i++) {
      G.add_edge(0, i + clubModifier, 1);
    }
    for (int i = 0; i < peopleIndex; i++) {
      G.add_edge(nameMap[people[i][0]] + nameModifier, partyMap[people[i][1]] + partyModifier, 1);
      for (int j = 2; j < 100; j++) {
        if (people[i][j] != "")
          G.add_edge(clubMap[people[i][j]] + clubModifier, nameMap[people[i][0]] + nameModifier, 1);
      }
    }
    int cap = (clubMap.size() - 1) / 2;
    for (int i = 0; i < partyMap.size(); i++) {
      G.add_edge(i + partyModifier, 1, cap);
    }

    int flow = network_flow(G,0,1);
    if (flow == clubMap.size()) {
      for (int u = 2; u < clubMap.size() + 2; u++) {
        for (auto e: G.nbr[u]) {
          if (e.flow > 0 && e.is_real) {
            std::cout<<getKey(nameMap,e.to - nameModifier)<<" ";
          }
      }
      std::cout<<getKey(clubMap, u - 2)<<std::endl;
      }
    } else {
      std::cout<<"Impossible."<<std::endl;
    }
		if (t > 0)
			std::cout<<std::endl;
	}
  return 0;
}