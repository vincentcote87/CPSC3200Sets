#include <iostream>

int main(void) {
	int n, m;
	std::cin>>n>>m;
	int p[1000];
	for (int i = 0; i < n; i++) {
		int tmp;
		std::cin>>tmp;
		p[i] = tmp;
	}
	for (int i = 0; i < m; i++) {
		int u, v, d;
		std::cin>>u>>v>>d;
	}
}