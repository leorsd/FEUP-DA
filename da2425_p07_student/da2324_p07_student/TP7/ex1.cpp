#include "exercises.h"
#include <cstring>

void knapsackRecursion(unsigned int values[], unsigned int weights[],
    unsigned int n, unsigned int maxWeight, unsigned int* maxValue, unsigned int availableValue,
    unsigned int i, unsigned int currentWeight,
    unsigned int currentValue, bool currentUsed[],
    bool usedItems[]) {

    if (i == n) {
        if (currentValue > *maxValue) {
            *maxValue = currentValue;
            std::memcpy(usedItems, currentUsed, n * sizeof(bool));
        }
        return;
    }

    currentUsed[i] = false;
    knapsackRecursion(values, weights, n, maxWeight, maxValue, availableValue - values[i], i + 1, currentWeight, currentValue, currentUsed, usedItems);

    if (currentWeight+weights[i] <= maxWeight && currentValue + availableValue > *maxValue) {
        currentUsed[i] = true;
        knapsackRecursion(values, weights, n, maxWeight, maxValue, availableValue - values[i], i + 1, currentWeight + weights[i], currentValue+values[i], currentUsed, usedItems);
    }
}

unsigned int knapsackBT(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue =0;
    for (unsigned int i = 0; i < n; i++) {
        maxValue += values[i];
    }
    bool currentUsed[n] = {false};

    unsigned int res =0;

    knapsackRecursion(values,weights,n,maxWeight,&res, maxValue, 0, 0, 0, currentUsed, usedItems );

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex1, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP7_Ex1, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}
