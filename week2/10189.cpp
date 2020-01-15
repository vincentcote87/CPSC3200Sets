// Problem 10189 - Minesweeper
// Vincent Cote - CPSC 3200
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    char ch;
    std::vector<std::vector<char>> grid;
    std::cin>>n>>m;
    if (std::cin.eof())
        return 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; i++) {
            std::cin>>ch;
            std::cout<<ch;
            // if (n == 0 || m == 0) {
            //     grid[n][m] = '.';
            // } else {
            //     std::cin>>ch;
            //     grid[n][m] = ch;
            // }
        }
    }
}