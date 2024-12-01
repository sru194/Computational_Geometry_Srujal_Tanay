#include "generate_all_subgraphs.h"

// Function to generate all subgraphs
vector<pair<set<Vertex>, EdgeList>> generateAllSubgraphs(int k, int mcc) {
    vector<Vertex> vertices;
    vector<pair<Vertex, Vertex>> edges;
    vector<pair<set<Vertex>, EdgeList>> allSubgraphs;

    // Generate all vertices
    for (int i = 0; i < mcc; ++i) {
        for (int j = 0; j < k; ++j) {
            vertices.emplace_back(i, j);
        }
    }

    // Generate all edges according to grid graph definition
    for (int i = 0; i < mcc; ++i) {
        for (int j = 0; j < k; ++j) {
            if (i < mcc - 1) { // Add edge to the right
                edges.emplace_back(make_pair(make_pair(i, j), make_pair(i + 1, j)));
            }
            if (j < k - 1) { // Add edge below
                edges.emplace_back(make_pair(make_pair(i, j), make_pair(i, j + 1)));
            }
        }
    }

    // Generate all subsets of vertices
    int totalVertices = vertices.size();
    int subsetCount = 1<<totalVertices; // Total subsets: 2^n

    for (int mask = 1; mask < subsetCount; ++mask) { // Skip empty subset
        set<Vertex> vertexSubset;
        EdgeList subgraphEdges;

        for (int i = 0; i < totalVertices; ++i) {
            if (mask & (1 << i)) { // Check if i-th vertex is in subset
                vertexSubset.insert(vertices[i]);
            }
        }

        // Add edges that are valid within this subset
        for (const auto& edge : edges) {
            if (vertexSubset.count(edge.first) && vertexSubset.count(edge.second)) {
                subgraphEdges.push_back(edge);
            }
        }

        // Include subgraphs with no edges (isolated vertices)
        allSubgraphs.emplace_back(vertexSubset, subgraphEdges);
    }


    cout << "Total subgraphs: " << allSubgraphs.size() << endl;
    // Print subgraphs (optional)
    for (const auto& subgraph : allSubgraphs) {
        const auto& vertices = subgraph.first;
        const auto& edges = subgraph.second;

        cout << "Subgraph with " << vertices.size() << " vertices and " << edges.size() << " edges:" << endl;
        cout << "Vertices: ";
        for (const auto& vertex : vertices) {
            cout << "(" << vertex.first << "," << vertex.second << ") ";
        }
        cout << "\nEdges: ";
        for (const auto& edge : edges) {
            cout << "(" << edge.first.first << "," << edge.first.second << ") - "
                 << "(" << edge.second.first << "," << edge.second.second << ") ";
        }
        cout << "\n" << endl;
    }

    return allSubgraphs;
}
