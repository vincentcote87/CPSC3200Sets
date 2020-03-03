// Problem 10047 - The Monocycle
// Vincent Cote - CPSC 3200
// Approach - As discussed in class, do bfs on all possible direction while keeping track
// of colour and current position on the graph.
#include <iostream>
#include <queue>

char graph[25][25];
int distance[25][25][4][5];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// dir: 0 = North, 1 = East, 2 = South, 3 = West
struct state {
	int r, c, dir, color;
	state(int rr = 0, int cc = 0, int ddir = 0, int ccolor = 0) {
		r = rr;
		c = cc;
		dir = ddir;
		color = ccolor;
	}
};

void resetGraph() {
    for (int i = 0; i < 25; i++)
			for (int j = 0; j < 25; j++)
				graph[i][j] = '#';
}

void resetDistance() {
    for (int i = 0; i < 25; i++)
			for (int j = 0; j < 25; j++)
			  for (int k = 0; k < 4; k++)
					for (int l = 0; l < 5; l++)
						distance[i][j][k][l] = -1;
}

int main(void) {
	int caseNum = 0;
	while (true) {
		int m, n;
		std::cin>>m>>n;
		if (m == 0 && n == 0)
			return 0;
		if (caseNum != 0)
			std::cout<<std::endl;
		resetGraph();
		resetDistance();
		int sRow, sCol, tRow, tCol;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				char tmp;
				std::cin>>tmp;
				graph[i][j] = tmp;
				if (tmp == 'S') {
					sRow = i;
					sCol = j;
				}
				if (tmp == 'T') {
					tRow = i;
					tCol = j;
				}
			}
		}
		state src(sRow, sCol, 0, 0);

		std::queue<state> q;
		q.push(src);
		distance[src.r][src.c][src.dir][src.color] = 0;
		int resultDist = -1;
		while (!q.empty()) {
			state cur = q.front();
			q.pop();
			if (cur.r == tRow && cur.c == tCol && cur.color == 0) {
				resultDist = distance[cur.r][cur.c][cur.dir][cur.color];
				break;
			}
			state next(cur.r + dr[cur.dir], cur.c + dc[cur.dir], cur.dir, cur.color);
			if (next.r >= 0 && next.r < m && next.c >= 0 && next.c < n) {
				next.color = (next.color + 1) % 5;
				if (distance[next.r][next.c][next.dir][next.color] == -1 && graph[next.r][next.c] != '#') {
					distance[next.r][next.c][next.dir][next.color] = distance[cur.r][cur.c][cur.dir][cur.color] + 1;
					q.push(next);
				}
			}
			next.r = cur.r;
			next.c = cur.c;
			next.dir = (cur.dir + 1) % 4;
			next.color = cur.color;
			if (graph[next.r][next.c] != '#' && distance[next.r][next.c][next.dir][next.color] == -1) {
					distance[next.r][next.c][next.dir][next.color] = distance[cur.r][cur.c][cur.dir][cur.color] + 1;
					q.push(next);
			}
			next.r = cur.r;
			next.c = cur.c;
			next.dir = (cur.dir + 4 - 1) % 4;
			next.color = cur.color;
			if (graph[next.r][next.c] != '#' && distance[next.r][next.c][next.dir][next.color] == -1) {
					distance[next.r][next.c][next.dir][next.color] = distance[cur.r][cur.c][cur.dir][cur.color] + 1;
					q.push(next);
			}
		}

		std::cout<<"Case #"<<++caseNum<<std::endl;
		if (resultDist >= 0) {
			std::cout<<"minimum time = "<<resultDist<<" sec"<<std::endl;
		} else {
			std::cout<<"destination not reachable"<<std::endl;
		}
	}
}