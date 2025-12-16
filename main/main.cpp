// Copyright 2024 Marina Usova



#include <iostream>
#include "DSU.h"
#include <vector>

int countIslands(std::vector<std::vector<int>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int rows = grid.size();
    int cols = grid[0].size();

    DSU dsu(rows * cols);

    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                int currentIndex = i * cols + j;

                for (int k = 0; k < 4; k++) {
                    int newRow = i + directions[k][0];
                    int newCol = j + directions[k][1];

                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 1) {
                        int neighborIndex = newRow * cols + newCol;
                        dsu.unite(currentIndex, neighborIndex);
                    }
                }
            }
        }
    }

    int totalCells = rows * cols;
    bool* seen = new bool[totalCells];
    for (int i = 0; i < totalCells; i++) {
        seen[i] = false;
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                int index = i * cols + j;
                int root = dsu.find(index);
                if (root != -1 && !seen[root]) {
                    seen[root] = true;
                    count++;
                }
            }
        }
    }

    delete[] seen;
    return count;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 0, 0, 1},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1}
    };

    int islandsCount = countIslands(grid);
    std::cout << "Number of islands: " << islandsCount << std::endl;

    return 0;
}
