// Problem 11228 - Transportation System
// Vincent Cote - CPSC 3200
// Approach -
#include <iostream>
#include <cmath>

struct vertex {
	int x, y;
	vertex(int xCoord = 0, int yCoord = 0) {
		x = xCoord;
		y = yCoord;
	}
};

struct edge {
	int v1, v2, distSquare;
	edge(int vertex1 = 0, int vertex2 = 1, int d = 1) {
		v1 = vertex1;
		v2 = vertex2;
		distSquare = d;
	}
};

int main(void) {
	int sets;
	std::cin>>sets;
	int setNum = 1;
	while(sets--) {
		int n, r;
		std::cin>>n>>r;
		vertex allPoints[1000];
		edge allEdges[250000];
		for (int i = 0; i < n; i++) {
			int x, y;
			std::cin>>x>>y;
			allPoints[i].x = x;
			allPoints[i].y = y;
		}
		int graph[1000][1000];
		int states = 1;
		int edges = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int left = allPoints[j].x - allPoints[i].x;
				int right = allPoints[j].y - allPoints[i].y;
				graph[i][j] = graph[j][i] = left*left + right*right;
				edge tmp(i,j, left*left + right*right);
				allEdges[edges] = tmp;
				edges++;
				// if (sqrt(graph[i][j]) > r) {
				// 	std::cout<<"dist = "<<graph[i][j]<<" and sqr = "<<sqrt(graph[i][j])<<" and r = "<<r<<std::endl;
				// 	states++;
				// }
			}
		}

		for (int i = 0; i < (n*n)-1/2; i++) {
			std::cout<<"Edge between vertices "<<allEdges[i].v1<<" and "<<allEdges[i].v2<<" with dist = "<<allEdges[i].distSquare<<std::endl;
		}


		std::cout<<"Case #"<<setNum<<": "<<states<<std::endl;
		// dont forget to square


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout<<graph[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;

		//gen graph matrix
	}
  return 0;
}