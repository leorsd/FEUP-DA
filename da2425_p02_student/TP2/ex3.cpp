// By: Gonçalo Leão
// Updated by DA 24/25 Team

#include <vector>
#include <algorithm> // for sort

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int subsetSum=0;
    unsigned int subsetWeight=0;
    unsigned int maxSum=0;
    unsigned int mask=0;
    for (unsigned int i = 1; i < (1<<n); i++) {
        subsetSum=0;
        subsetWeight=0;
        for (unsigned int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subsetSum += values[j];
                subsetWeight += weights[j];
            }
        }
        if (subsetWeight<=maxWeight && subsetSum>maxSum) {
            mask=i;
            maxSum=subsetSum;
        }
    }
    for (unsigned int p = 0; p<n; p++) {
        if ((mask & 1) == 1) {
           usedItems[p]=true;
        }else {
            usedItems[p]=false;
        }
        mask >>= 1;
    }
    return maxSum;
}

// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyValue(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int peso=0;
    unsigned int maxSum=0;
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i]=false;
    }
    for (unsigned int k = 0; k < n; k++) {
        int max=0;
        int index=0;
        for (unsigned int i = 0; i < n; i++) {
            if (values[i] > max && usedItems[i]==false) {
                max=values[i];
                index=i;
            }
        }
        peso+=weights[index];
        if (peso>maxWeight) {
            break;
        }else{
            usedItems[index]=true;
            maxSum+=values[index];
        }
    }
    return maxSum;
}

// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyWeight(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int peso=0;
    unsigned int maxSum=0;
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i]=false;
    }
    for (unsigned int k = 0; k < n; k++) {
        int max=0;
        int index=0;
        for (unsigned int i = 0; i < n; i++) {
            if (weights[i] > max && usedItems[i]==false) {
                max=weights[i];
                index=i;
            }
        }
        peso+=max;
        if (peso>maxWeight) {
            break;
        }else {
            usedItems[index]=true;
            maxSum+=values[index];
        }
    }
    return maxSum;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

// this test is expected to fail
TEST(TP2_Ex3, testKnapsack_4items_greedy_fail) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackGreedyValue(values, weights, n, 5, usedItems), 28);
        weights[0]=1;
        weights[1]=1;
        weights[3]=3;
        EXPECT_EQ(knapsackGreedyWeight(values, weights, n, 5, usedItems), 36);

    }
}


TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}


TEST(TP2_Ex3, testKnapsack_40items) {
    const unsigned int n = 20;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4, 1,  2, 3, 8, 4,12, 20,
                                  1, 4, 4 ,3, 3, 6, 6, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 4,3, 2, 1, 4, 6,10, 10, 3, 1, 6,2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 24);

    }
}