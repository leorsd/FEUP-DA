// By: Gonçalo Leão

#ifndef DA_TP5_CLASSES_EXERCISES_H
#define DA_TP5_CLASSES_EXERCISES_H

#include <string>
#include <cmath>
#include <vector>

// Ex 1
// Recursive version
unsigned long factorialRecurs(unsigned long n);
// Version with dynamic programming
unsigned long factorialDP(unsigned long n);

// Ex 2
bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 3
bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 4
std::string calcSum(int sequence[], unsigned long n);
void testPerformanceCalcSum();

// Ex 5
unsigned long s_recursive(unsigned int n, unsigned int k);
unsigned long b_recursive(unsigned int n);
unsigned long s_dynamic(unsigned int n, unsigned int k);
unsigned long b_dynamic(unsigned int n);

// Ex 6
int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j);
int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j);
void testPerformanceMaxSubsequence();

// Ex 7
std::string hanoiDP(unsigned int n, char src, char dest);

// Ex 8
unsigned int knapsackDP(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]);

// Ex 9
int editDistance(std::string pattern, std::string text);
float numApproximateStringMatching(std::string filename, std::string toSearch);

#include "../data_structures/Graph.h"
template <class T>
class DPGraph: public Graph<T> {
public:
    // Ex 10
    void dijkstra(const T &origin);
    std::vector<T> getPath(const T &origin, const T &dest) const;

    // Ex 11
    void bellmanFord(const T &origin);

    // Ex 12
    void floydWarshall();
    std::vector<T> getFloydWarshallPath(const T &origin, const T &dest) const;

protected:
    /**
    * Analyzes an edge in single source shortest path algorithm.
    * Returns true if the target vertex was relaxed (dist, path).
    * Used by all single-source shortest path algorithms.
    */
    //bool DPGraph::relax(Edge *edge);
    bool relax(Edge<T> *edge);
};

#endif //DA_TP5_CLASSES_EXERCISES_H
