#include <iostream>     // std::cout
#include <algorithm>    // std::count
#include "exercises.h"

void hanoiHelper(unsigned int n, char src, char dest, char aux, std::string &moves) {
    if (n == 1) {
        moves += src;
        moves += "->";
        moves += dest;
        moves += ",";
        return;
    }

    hanoiHelper(n - 1, src, aux, dest, moves);

    hanoiHelper(1, src, dest, aux, moves);

    hanoiHelper(n - 1, aux, dest, src, moves);
}

// Main function to solve Tower of Hanoi
std::string hanoiDC(unsigned int n, char src, char dest) {
    std::string moves;
    char aux = 'A' + 'B' + 'C' - src - dest; // Find the auxiliary tower
    hanoiHelper(n, src, dest, aux, moves);
    if (!moves.empty()) moves.pop_back();
    return moves;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, testHanoi_height4) {
    std::string moves = hanoiDC(4, 'A', 'B');
    EXPECT_EQ(std::count(moves.begin(),moves.end(),','),14); // there are 15 moves
    EXPECT_EQ(moves,"A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}