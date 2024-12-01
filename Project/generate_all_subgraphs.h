#ifndef GENERATE_ALL_SUBGRAPHS
#define GENERATE_ALL_SUBGRAPHS

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

typedef pair<int, int> Vertex;
typedef vector<pair<Vertex, Vertex>> EdgeList; // Stores edges as pairs of vertices

// Function declarations
vector<pair<set<Vertex>, EdgeList>> generateAllSubgraphs(int k, int mcc);

#endif 
