// By: Gonçalo Leão
// Updated by DA 24/25 Team

#include <limits.h>

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int n_poss=0;
    for (unsigned int i = 0; i < n; i++) {
        n_poss += Stock[i];
    }
    bool find=false;
    unsigned int bestmask=0;
    unsigned int n_coins=UINT_MAX;
    for (unsigned int i = 1; i < (1<<n_poss); i++) {
        unsigned int sum = 0;
        unsigned int mask=i;
        int count=0;
        for (unsigned int j = 0; j < n; j++) {
            for (unsigned int k = 0; k < Stock[j]; k++) {
                if ((mask & 1) == 1) {
                    sum+=C[j];
                    count++;
                }
                mask >>= 1;
            }
        }
        if (sum==T && count<n_coins) {
            bestmask = i;
            n_coins = count;
            find=true;
        }
    }
    if (find) {
        for (unsigned int j = 0; j < n; j++) {
            int sum=0;
            for (unsigned int k = 0; k < Stock[j]; k++) {
                if ((bestmask & 1) == 1) {
                    sum++;
                }
                bestmask >>= 1;
            }
            usedCoins[j] = sum;
        }
    }
    return find;
}

bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int sum=0;
    bool find=false;
    for (int i=n-1; i>=0; i--) {
        int count=Stock[i];
        while (count>=0) {
            if (sum+count*C[i] == T) {
                usedCoins[i] = count;
                sum+=count*C[i];
                find=true;
                break;
            }else if (sum+count*C[i] < T) {
                usedCoins[i] = count;
                sum+=count*C[i];
                break;
            }
            count--;
        }
        if (find) {
            break;
        }
    }
    return find;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}


TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}