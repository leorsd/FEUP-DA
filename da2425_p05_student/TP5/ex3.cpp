#include "exercises.h"

#include <iostream>
#include <fstream>
#include <sstream>

int editDistance(std::string pattern, std::string text) {
    int m = pattern.size();
    int n = text.size();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (pattern[i - 1] == text[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + std::min({dp[i - 1][j],dp[i][j - 1],dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}

float numApproximateStringMatching(std::string filename, std::string toSearch) {
    std::ifstream file(filename);
    std::string word;
    int totalDistance = 0, wordCount = 0;
    while (file >> word) {
        totalDistance += editDistance(word, toSearch);
        wordCount++;
    }
    file.close();

    return totalDistance / (wordCount*1.0);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex3, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}



#define REL_PATH std::string("../TP5/testsEx3/") // relative path to the tests

TEST(TP5_Ex3, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}

