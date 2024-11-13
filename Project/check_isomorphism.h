#ifndef CHECK_ISOMORPHISM_H
#define CHECK_ISOMORPHISM_H

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS,property<vertex_index_t, int>,property<edge_index_t, int>> Graph;
typedef graph_traits<Graph>::vertex_descriptor vertex_desc;
typedef graph_traits<Graph>::edge_descriptor edge_desc;

// Function declarations
int nonIsoConnectedComponents(int vertices, const vector<pair<int, int>>& edges);

#endif
