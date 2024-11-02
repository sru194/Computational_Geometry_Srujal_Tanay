#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/is_kuratowski_subgraph.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, 
                       property<vertex_index_t, int>, 
                       property<edge_index_t, int>> Graph;
typedef vector<graph_traits<Graph>::edge_descriptor> kuratowski_edges_t;

void graph_input(vector<vector<int>> &graph) {
    int vertices, edges;
    cout << "Enter the number of vertices and edges:" << endl;
    cin >> vertices >> edges;
    graph.resize(vertices);

    cout << "Enter each edge pair (a, b):" << endl;
    for (int i = 0; i < edges; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }
}

void boost_representation(const vector<vector<int>> &graph, Graph &g) {
    for (int u = 0; u < graph.size(); ++u) {
        for (int v : graph[u]) {
            if (u < v) {
                add_edge(u, v, g);
            }
        }
    }
}

int main() {
    vector<vector<int>> graph;
    graph_input(graph);

    Graph g(graph.size());
    boost_representation(graph, g);

    // Initialize edge indices
    property_map<Graph, edge_index_t>::type e_index = get(edge_index, g);
    int edge_count = 0;
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(e_index, *ei, edge_count++);
    }

    kuratowski_edges_t kuratowski_edges;
    if (boyer_myrvold_planarity_test(
            boyer_myrvold_params::graph = g,
            boyer_myrvold_params::kuratowski_subgraph = back_inserter(kuratowski_edges))) {
        cout << "Input graph is planar" << endl;
    } 
    else {
        cout << "Input graph is not planar" << endl;
        cout << "Edges in the Kuratowski subgraph: ";
        for (auto edge : kuratowski_edges) {
            cout << "(" << source(edge, g) << ", " << target(edge, g) << ") ";
        }
        cout << endl;

        cout << "Is it a Kuratowski subgraph? ";
        if (is_kuratowski_subgraph(g, kuratowski_edges.begin(), kuratowski_edges.end())) {
            cout << "Yes." << endl;
        } else {
            cout << "No." << endl;
        }
    }
    return 0;
}