// By: Gonçalo Leão
// With contributions by Eduardo Almeida
// Updated by DA 24/25 Team

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max=0;
    int sum=0;
    for (int t=0;t<n;t++) {
        for (int k=t;k<n;k++) {
            sum+=A[k];
            if (sum>max) {
                max=sum;
                i=t;
                j=k;
            }
        }
        sum=0;
    }
    return max;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}