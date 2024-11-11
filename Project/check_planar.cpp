#include "check_planar.h"

int check_planarity(int vertices, const vector<pair<int, int>>& graph) {
    // Initialize the Boost graph with the given number of vertices
    Graph g(vertices);

    // Add edges to the graph
    for (const auto& edge : graph) {
        add_edge(edge.first, edge.second, g);
    }

    // Initialize edge indices
    property_map<Graph, edge_index_t>::type e_index = get(edge_index, g);
    int edge_count = 0;
    graph_traits<Graph>::edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(e_index, *ei, edge_count++);
    }

    //Graph drawing in graph.dot file
    ofstream file("graph.dot");
    write_graphviz(file, g);

    // Check for planarity
    kuratowski_edges_t kuratowski_edges;
    if (boyer_myrvold_planarity_test(
            boyer_myrvold_params::graph = g,
            boyer_myrvold_params::kuratowski_subgraph = back_inserter(kuratowski_edges))) {
        cout << "Input graph is planar" << endl;
        return -1;
    } 
    else {
        cout << "Input graph is not planar" << endl;
        cout << "Edges in the Kuratowski subgraph: ";
        int cnt = 0;
        for (auto edge : kuratowski_edges) {
            cout << "(" << source(edge, g) << ", " << target(edge, g) << ") ";
            cnt++;
        }
        return cnt;
        cout << endl;
    }
}
