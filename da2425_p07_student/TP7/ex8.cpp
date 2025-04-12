#include "exercises.h"
#include <algorithm>
#include <vector>
#include <climits>

void tspBacktrack(const unsigned int** dists, unsigned int n, unsigned int currentCity,unsigned int visitedCount, unsigned int currentCost,std::vector<bool>& visited, std::vector<unsigned int>& currentPath,unsigned int& minCost, unsigned int* bestPath) {
    if (visitedCount == n) {
        unsigned int totalCost = currentCost + dists[currentCity][0];
        if (totalCost < minCost) {
            minCost = totalCost;
            std::copy(currentPath.begin(), currentPath.end(), bestPath);
        }
        return;
    }
    if (currentCost > minCost) {
        return;
    }

    for (unsigned int next = 1; next < n; next++) {
        if (!visited[next]) {
            visited[next] = true;
            currentPath[visitedCount] = next;
            tspBacktrack(dists, n, next, visitedCount + 1,currentCost + dists[currentCity][next], visited, currentPath, minCost, bestPath);
            visited[next] = false;
        }
    }
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    std::vector<bool> visited(n, false);
    std::vector<unsigned int> currentPath(n);
    visited[0] = true;
    currentPath[0] = 0;

    unsigned int minCost = UINT_MAX;
    tspBacktrack(dists, n, 0, 1, 0, visited, currentPath, minCost, path);

    return minCost;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex8, testTSP_4x4_symmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 80);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_4x4_assymmetric) {
    const unsigned int n = 4;
    const unsigned int dists[n][n] = {{0, 10, 15, 20}, {5, 0, 9, 10}, {6, 13, 0, 12}, {8, 8, 9,0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 35);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 1);
    EXPECT_EQ(path[2], 3);
    EXPECT_EQ(path[3], 2);
}

TEST(TP7_Ex8, testTSP_5x5_symmetric) {
    const unsigned int n = 5;
    const unsigned int dists[n][n] = {{0,12,10,19,8},{12,0,3,7,2},{10,3,0,6,20},{19,7,6,0,4},{8,2,20,4,0}};

    // Convert 2D array to double pointer
    auto **ptr = new const unsigned int*[n];
    for (unsigned int i = 0; i < n; i++)
        ptr[i] = dists[i];
    unsigned int path[n];

    EXPECT_EQ(tspBT(ptr, n, path), 32);
    EXPECT_EQ(path[0], 0);
    EXPECT_EQ(path[1], 2);
    EXPECT_EQ(path[2], 1);
    EXPECT_EQ(path[3], 3);
    EXPECT_EQ(path[4], 4);
}
