#include <climits>

#include "exercises.h"
#include "cmath"

int maxCrossingSum(int A[], int left, int mid, int right, int &crossStart, int &crossEnd) {
    int leftSum = INT_MIN, rightSum = INT_MIN;
    int sum = 0, tempStart = mid;

    // Left part
    for (int i = mid; i >= left; i--) {
        sum += A[i];
        if (sum > leftSum) {
            leftSum = sum;
            tempStart = i;
        }
    }

    sum = 0;
    int tempEnd = mid + 1;
    // Right part
    for (int i = mid + 1; i <= right; i++) {
        sum += A[i];
        if (sum > rightSum) {
            rightSum = sum;
            tempEnd = i;
        }
    }

    crossStart = tempStart;
    crossEnd = tempEnd;
    return leftSum + rightSum;
}

// Divide and conquer approach to find max subarray
int maxSubsequenceRecurence(int A[], int left, int right, int &start, int &end) {
    if (left == right) {
        start = end = left;
        return A[left];
    }

    int mid = left + (right - left) / 2;
    int leftStart, leftEnd;
    int rightStart, rightEnd;
    int crossStart, crossEnd;

    int leftMax = maxSubsequenceRecurence(A, left, mid, leftStart, leftEnd);
    int rightMax = maxSubsequenceRecurence(A, mid + 1, right, rightStart, rightEnd);

    int crossMax = maxCrossingSum(A, left, mid, right, crossStart, crossEnd);

    if (leftMax >= rightMax && leftMax >= crossMax) {
        start = leftStart;
        end = leftEnd;
        return leftMax;
    }else if (rightMax >= leftMax && rightMax >= crossMax) {
        start = rightStart;
        end = rightEnd;
        return rightMax;
    }else {
        start = crossStart;
        end = crossEnd;
        return crossMax;
    }
}

// Main function to call the divide and conquer approach
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    return maxSubsequenceRecurence(A, 0, n - 1, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}