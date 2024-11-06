#include "check_planar.h"

bool check_planarity(int vertices, const vector<pair<int, int>>& graph) {
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

    // Check for planarity
    kuratowski_edges_t kuratowski_edges;
    if (boyer_myrvold_planarity_test(
            boyer_myrvold_params::graph = g,
            boyer_myrvold_params::kuratowski_subgraph = back_inserter(kuratowski_edges))) {
        cout << "Input graph is planar" << endl;

        ofstream file("graph.dot");
        write_graphviz(file, g);
        cout << "Planar embedding written to graph.dot." << endl;

        return true;
    } 
    else {
        cout << "Input graph is not planar" << endl;
        cout << "Edges in the Kuratowski subgraph: ";
        for (auto edge : kuratowski_edges) {
            cout << "(" << source(edge, g) << ", " << target(edge, g) << ") ";
        }
        cout << endl;

        ofstream file("graph.dot");
        write_graphviz(file, g);
        cout << "Graph written to graph.dot." << endl;
        return false;
    }
}
