
#include "exercises.h"

unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {

}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex2, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP5_Ex2, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}