// Problem 11228 - Transportation System
// Vincent Cote - CPSC 3200
// Approach - start by bulding a list of edges between all the different city coordinates.
// Using the mst code from the code bank to get the minimum spanning tree
// of the cities. At each new point found in the mst compare it to r and add to either
// roads or railroads, also if it is railroads add +1 to states.

/*
 * Implementation of Kruskal's Minimum Spanning Tree Algorithm
 *
 * Author: Howard Cheng
 *
 * This is a routine to find the minimum spanning tree.  It takes as
 * input:
 *
 *      n: number of vertices
 *      m: number of edges
 *  elist: an array of edges (if (u,v) is in the list, there is no need
 *         for (v,u) to be in, but it wouldn't hurt, as long as the weights
 *         are the same).
 *
 * The following are returned:
 *
 *  index: an array of indices that shows which edges from elist are in
 *         the minimum spanning tree.  It is assumed that its size is at
 *         least n-1.
 *   size: the number of edges selected in "index".  If this is not
 *         n-1, the graph is not connected and we have a "minimum
 *         spanning forest."
 *
 * The weight of the MST is returned as the function return value.
 * 
 * The run time of the algorithm is O(m log m).
 *
 * Note: the elements of elist may be reordered.
 *
 * Modified by Rex Forsyth using C++  Aug 28, 2003
 * This version defines the unionfind and edge as classes and  provides
 * constructors. The edge class overloads the < operator. So the sort does
 * not use a  * cmp function. It uses dynamic arrays.
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

int states = 0;

struct minExp {
   double roads = 0.0;
   double rails = 0.0;
};

class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	    }
	    else {
	       uf[res1].p = res2;
	       if (uf[res1].rank == uf[res2].rank) {
		  uf[res2].rank++;
	       }
	    }
	    return true;
	 }
	 return false;
      }
      
   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {             // for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int i=-1, int j=-1, double weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      double w;            /* weight, can be double instead of int */
};


minExp mst(int n, int m, Edge elist[], int index[], int& size, int r)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  minExp w;
  size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      double dist = sqrt(elist[i].w);
      if (dist >= r) {
         w.rails += dist;
         states++;
      }
      else
         w.roads += dist;
      uf.merge(c1, c2);
    }
  }

  return w;
}

int main(void)
{
   int sets;
   int cases = 0;
	std::cin>>sets;
	int setNum = 1;
	while(sets--) {
    	states = 1;
			int n, r;
			std::cin>>n>>r;

      double* x = new double[n];
      double* y = new double[n];
      int* index = new int[n];

      for (int i = 0; i < n; i++)  cin >> x[i] >> y[i];

      Edge* elist = new Edge[n*n];
      int k = 0;
      for (int i = 0; i < n; i++)
         for (int j = i+1; j < n; j++) {
            double left = x[j] - x[i];
            double right = y[j] - y[i];
            double dist = (left*left) + (right*right);
            elist[k++] = Edge(i,j, dist);
         }

      int t;  // number of edges in the mst
      minExp result = mst(n, k, elist, index, t, r);
      cout<<"Case #"<<++cases<<": "<<states<<" "<<round(result.roads)<<" "<<round(result.rails)<<endl;
   }
   return 0;
}
