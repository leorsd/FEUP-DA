// By: Gonçalo Leão

#ifndef DA_TP7_CLASSES_EXERCISES_H
#define DA_TP7_CLASSES_EXERCISES_H

#include <vector>

// Ex 4
#define MAZE_WALL 0
#define MAZE_PATH 1
#define MAZE_EXIT 2

class Labyrinth {
public:
    Labyrinth(int values[10][10]);
    void print() const;
    bool findGoal(int x, int y);
private:
    int labyrinth[10][10];
    bool visited[10][10];
    void initializeVisited();
    bool findGoalRec(int x, int y);
};



// Ex 5
bool subsetSumBT(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize);

// Ex 6
bool changeMakingBT(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 7
class Activity {
public:
    unsigned int start;
    unsigned int finish;
    Activity(unsigned int s, unsigned int f): start(s), finish(f){};
    bool operator==(const Activity &a2) const;
    bool overlaps(const Activity &a2) const;
};
std::vector<Activity> activitySelectionBT(std::vector<Activity> A);

// Ex 1
unsigned int knapsackBT(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

// Ex 8
unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]);

#endif //DA_TP7_CLASSES_EXERCISES_H
