
#include "exercises.h"
#include <algorithm>


bool subsetSumRecursion(unsigned int A[], unsigned int n, unsigned int T, unsigned int currentIndex, unsigned int subset[], unsigned int subsetSize,unsigned int currentSum, unsigned int maxSubset[], unsigned int &maxSubsetSize) {
    if (currentSum == T) {
        std::copy(subset, subset + subsetSize, maxSubset);
        maxSubsetSize = subsetSize;
        return true;
    }
    if (currentIndex == n) {
        return false;
    }

    if (currentSum >= T) {
        return false;
    }
    if (subsetSumRecursion(A,n,T,currentIndex+1,subset,subsetSize,currentSum,maxSubset,maxSubsetSize) == true){return true;}
    subset[subsetSize] = A[currentIndex];
    if ( subsetSumRecursion(A,n,T,currentIndex+1,subset,subsetSize+1, currentSum+A[currentIndex], maxSubset, maxSubsetSize) == true) {return true;}
    return false;
}

bool subsetSumBT(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    unsigned int auxSubset[n];
    return subsetSumRecursion(A,n,T,0,auxSubset,0,0,subset,subsetSize);
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP7_Ex5, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;

    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBT(A,6,T,subset,subsetSize), false);
}
