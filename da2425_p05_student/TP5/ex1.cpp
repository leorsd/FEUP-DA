

#include "exercises.h"
#include <iostream>


bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(T + 1, -1));
    std::vector<std::vector<int>> used(n + 1, std::vector<int>(T + 1, 0));
    for (unsigned int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int t = 0; t <= T; t++) {
            dp[i][t] = dp[i - 1][t];
            used[i][t] = 0;

            if (t >= C[i - 1]) {
                for (unsigned int k = 1; k <= Stock[i - 1] && k * C[i - 1] <= t; k++) {
                    if (dp[i - 1][t - k * C[i - 1]] != -1) {
                        int new_count = dp[i - 1][t - k * C[i - 1]] + k;
                        if (dp[i][t] == -1 || new_count < dp[i][t]) {
                            dp[i][t] = new_count;
                            used[i][t] = k;
                        }
                    }
                }
            }
        }
    }

    if (dp[n][T] == -1) return false;

    unsigned int t = T;
    for (int i = n; i > 0; i--) {
        usedCoins[i - 1] = used[i][t];
        t -= used[i][t] * C[i - 1];
    }

    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex1, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];
    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP5_Ex1, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP5_Ex1, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}