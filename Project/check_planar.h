#ifndef CHECK_PLANAR_H
#define CHECK_PLANAR_H

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/is_kuratowski_subgraph.hpp>
#include <boost/property_map/property_map.hpp>

#include <boost/graph/graphviz.hpp>
#include <fstream>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, 
                       property<vertex_index_t, int>, 
                       property<edge_index_t, int>> Graph;
typedef vector<graph_traits<Graph>::edge_descriptor> kuratowski_edges_t;

// Function declarations
int check_planarity(int vertices, const vector<pair<int, int>>& edges);

#endif 
