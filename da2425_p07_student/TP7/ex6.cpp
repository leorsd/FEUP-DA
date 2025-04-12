#include "exercises.h"
#include <algorithm>

bool changeRecur(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T,unsigned int currentValue, unsigned int currentCoins[], unsigned int currentIndex, unsigned int usedCoins[]) {
    if (currentValue == T) {
        std::copy(currentCoins, currentCoins+n, usedCoins);
        return true;
    }
    if (currentIndex == n) {
        return false;
    }
    for (unsigned int i = 0; i <= Stock[currentIndex]; ++i) {
        currentCoins[currentIndex] = i;
        if (changeRecur(C, Stock, n, T, currentValue + i * C[currentIndex], currentCoins, currentIndex + 1, usedCoins)) {
            return true;
        }
    }
    currentCoins[currentIndex] = 0;
    return false;
}

bool changeMakingBT(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int currentCoins[n] = {0};

    return changeRecur(C,Stock, n, T, 0, currentCoins, 0, usedCoins);
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex6, hasBTChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBT(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBT(C, Stock3, n, 10, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP7_Ex6, hasBTChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 6, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBT(C, Stock, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBT(C, Stock2, n, 7, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBT(C, Stock2, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP7_Ex6, hasNoBTChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingBT(C, Stock, n, 1, usedCoins), false);
}
