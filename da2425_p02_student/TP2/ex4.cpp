// By: Gonçalo Leão
// Updated by DA 24/25 Team

#include <algorithm>
#include <vector>

double fractionalKnapsackGR(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    double m[n];
    for (unsigned int i = 0; i < n; i++) {
        m[i]=(values[i]*1.0)/weights[i];
        usedItems[i]=0;
    }
    double result = 0.0;
    double w=0.0;
    while (w < maxWeight) {
        double max=0;
        int index=0;
        for (unsigned int i = 0; i < n; i++) {
            if (m[i]>max && usedItems[i]==0) {
                max = m[i];
                index = i;
            }
        }
        if (max==0) {
            break;
        }
        if (w+weights[index] <= maxWeight) {
            usedItems[index] = 1;
            result+=values[index];
            w+=weights[index];
        }else {
            usedItems[index]=(maxWeight-w)/(weights[index]*1.0);
            result+=values[index]*usedItems[index];
            w=maxWeight;
        }
    }
    return result;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}