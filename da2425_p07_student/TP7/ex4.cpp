#include "exercises.h"

bool Labyrinth::findGoal(int x, int y) {
    visited[x][y] = true;
    if (labyrinth[x][y] == 2) {
        return true;
    }
    if (labyrinth[x+1][y] != 0 && !visited[x+1][y]) {
        if ( findGoal(x+1, y) == true ){return true;}
    }
    if (labyrinth[x-1][y] != 0 && !visited[x-1][y]) {
        if ( findGoal(x-1, y) == true ){return true;}
    }
    if (labyrinth[x][y-1] != 0 && !visited[x][y-1]) {
        if ( findGoal(x, y-1) == true ){return true;}
    }
    if (labyrinth[x][y+1] != 0 && !visited[x][y+1]) {
        if (  findGoal(x, y+1) ==  true ){return true;}
    }
    return false;
}


/// TESTS ///
#include <gtest/gtest.h>

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            labyrinth[i][j] = values[i][j];
    initializeVisited();
}

void Labyrinth::initializeVisited() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            visited[i][j] = false;
}

TEST(TP7_Ex4, testLabyrinthPossible) {
    // This test assumes that the mazes only have a possible path to the exit
    int lab1[10][10] ={
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,1,1,0,1,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,1,1,1,1,0},
        {0,1,1,1,0,0,1,0,1,0},
        {0,1,0,0,0,0,1,0,1,0},
        {0,1,1,1,0,0,1,2,0,0},
        {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),true);
}

TEST(TP7_Ex4, testLabyrinthImpossible) {
    int lab1[10][10] ={
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}};

    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1),false);
}
