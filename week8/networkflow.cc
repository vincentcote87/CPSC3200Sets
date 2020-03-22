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

int main(void)
{
  Graph G(1000001);
  int s, t, u, v, cap, flow;

	s = 0;
	t = 100000;

	G.add_edge(0,2001,1);
	G.add_edge(0,2002,1);
	G.add_edge(0,2003,1);

	G.add_edge(2001, 1,1);
	G.add_edge(2002, 2,1);
	G.add_edge(2003, 3,1);

	G.add_edge(1,1001,1);
	G.add_edge(2,1002,1);
	G.add_edge(3,1003,1);

	G.add_edge(1001,100000,1);
	G.add_edge(1002,100000,1);
	G.add_edge(1003,100000,1);
//   cin >> s >> t;
//   while (cin >> u >> v >> cap) {
//     G.add_edge(u, v, cap);
//   }
  
  flow = network_flow(G, s, t);
  cout << "maximum flow = " << flow << endl;
  
  return 0;
}



/*
 * Network Flow (Relabel-to-front)
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  The flow is given in the flow array (look for
 * positive flow).
 *
 * The complexity of this algorithm is O(n^3), which is good if the
 * graph is small but the maximum flow can be large.  Since the
 * algorithm is O(n^3) we are going to use the adjacency matrix
 * representation.
 *
 */

#include <iostream>
#include <list>
#include <cassert>

using namespace std;

const int MAX_NODE = 102;

void clear_graph(int graph[MAX_NODE][MAX_NODE], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph[i][j] = 0;
    }
  }
}

void push(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
	  int e[], int u, int v)
{
  int cf = graph[u][v] - flow[u][v];
  int d = (e[u] < cf) ? e[u] : cf;
  flow[u][v] += d;
  flow[v][u] = -flow[u][v];
  e[u] -= d;
  e[v] += d;
}

void relabel(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
	     int n, int h[], int u)
{
  h[u] = -1;
  for (int v = 0; v < n; v++) {
    if (graph[u][v] - flow[u][v] > 0 &&
	(h[u] == -1 || 1 + h[v] < h[u])) {
      h[u] = 1 + h[v];
    }
  }
  assert(h[u] >= 0);
}

void discharge(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE],
	       int n, int e[], int h[], list<int>& NU, 
	       list<int>::iterator &current, int u)
{
  while (e[u] > 0) {
    if (current == NU.end()) {
      relabel(graph, flow, n, h, u);
      current = NU.begin();
    } else {
      int v = *current;
      if (graph[u][v] - flow[u][v] > 0 && h[u] == h[v] + 1) {
	push(graph, flow, e, u, v);
      } else {
	++current;
      }
    }
  }
}

int network_flow(int graph[MAX_NODE][MAX_NODE], int flow[MAX_NODE][MAX_NODE], 
		 int n, int s, int t)
{
  int e[MAX_NODE], h[MAX_NODE];
  int u, v, oh;
  list<int> N[MAX_NODE], L;
  list<int>::iterator current[MAX_NODE], p;

  for (u = 0; u < n; u++) {
    h[u] = e[u] = 0;
  }
  for (u = 0; u < n; u++) {
    for (v = 0; v < n; v++) {
      flow[u][v] = 0;
      if (graph[u][v] > 0 || graph[v][u] > 0) {
	N[u].push_front(v);
      }
    }
  }
  h[s] = n;
  for (u = 0; u < n; u++) {
    if (graph[s][u] > 0) {
      e[u] = flow[s][u] = graph[s][u];
      e[s] += flow[u][s] = -graph[s][u];
    }
    if (u != s && u != t) {
      L.push_front(u);
    }
    current[u] = N[u].begin();
  }

  p = L.begin();
  while (p != L.end()) {
    u = *p;
    oh = h[u];
    discharge(graph, flow, n, e, h, N[u], current[u], u);
    if (h[u] > oh) {
      L.erase(p);
      L.push_front(u);
      p = L.begin();
    }
    ++p;
  }
  
  int maxflow = 0;
  for (u = 0; u < n; u++) {
    if (flow[s][u] > 0) {
      maxflow += flow[s][u];
    }
  }
  return maxflow;
}

void print_flow(int flow[MAX_NODE][MAX_NODE], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (flow[i][j] > 0) {
	cout << i << " -> " << j << ": " << flow[i][j] << endl;
      }
    }
  }
}

int main(void)
{
  int graph[MAX_NODE][MAX_NODE];
  int s, t;
  int n, m, u, v, c;
  int flow[MAX_NODE][MAX_NODE];
  int maxflow;

  while (cin >> n && n > 0) {
    clear_graph(graph, n);
    cin >> m >> s >> t;
    while (m-- > 0) {
      cin >> u >> v >> c;
      graph[u][v] = c;
    }
    maxflow = network_flow(graph, flow, n, s, t);
    cout << "flow = " << maxflow << endl;
    print_flow(flow, n);
  }

  return 0;
}

