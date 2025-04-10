#include "exercises.h"

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
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
