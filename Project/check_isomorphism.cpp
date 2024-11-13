#include "check_isomorphism.h"

// Convert edge list to Boost graph
void edge_list_to_boost_graph(const vector<pair<int, int>>& edge, Graph &g) {
    for (const auto& e : edge) {
        add_edge(e.first, e.second, g);
    }
}

// Function to check isomorphism between two graphs
bool are_isomorphic(const Graph& g1, const Graph& g2) {
    vector<vertex_desc> f(num_vertices(g2));
    return isomorphism(g1, g2, isomorphism_map(make_iterator_property_map(f.begin(), get(vertex_index, g1), f[0])));
}

// Custom function to write graph in DOT format
void custom_write_graphviz(const string& filename, const Graph& g, const std::unordered_map<vertex_desc, int>& original_ids) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    file << "graph G {\n";
    cout << "Component: ";
    
    for (auto vp = vertices(g); vp.first != vp.second; ++vp.first) {
        int original_id = original_ids.at(*vp.first); // Use the original ID from the map
        file << "    " << original_id << ";\n";
        cout << original_id << " ";
    }

    cout << "\nEdges: ";
    for (auto ep = edges(g); ep.first != ep.second; ++ep.first) {
        int source_id = original_ids.at(source(*ep.first, g));
        int target_id = original_ids.at(target(*ep.first, g));
        file << "    " << source_id << " -- " << target_id << ";\n";
        cout << "(" << source_id << "," << target_id << ") ";
    }

    file << "}\n";
    file.close();
    cout<<"\n\n\n";
}

// Function to find non-isomorphic connected components
int nonIsoConnectedComponents(int vertices, const vector<pair<int, int>>& edge) {
    Graph g(vertices);
    edge_list_to_boost_graph(edge, g);

    vector<int> component(num_vertices(g));
    int num_components = connected_components(g, &component[0]);

    vector<Graph> non_isomorphic_components;
    vector<Graph> all_components;
    vector<std::unordered_map<vertex_desc, int>> original_id_maps; // Store original IDs for each subgraph

    for (int i = 0; i < num_components; ++i) {
        Graph subgraph;
        std::unordered_map<vertex_desc, int> original_ids; // Map to store original IDs for this component
        std::unordered_map<int, vertex_desc> vertex_map;

        for (int j = 0; j < num_vertices(g); ++j) {
            if (component[j] == i) {
                vertex_desc v = add_vertex(subgraph);
                original_ids[v] = j; // Store the original ID in the map
                vertex_map[j] = v;
            }
        }

        for (auto e : make_iterator_range(edges(g))) {
            int u = get(vertex_index, g, source(e, g));
            int v = get(vertex_index, g, target(e, g));
            if (component[u] == i && component[v] == i) {
                add_edge(vertex_map[u], vertex_map[v], subgraph);
            }
        }

        bool is_isomorphic = false;
        for (const auto& existing_component : all_components) {
            if (are_isomorphic(subgraph, existing_component)) {
                is_isomorphic = true;
                break;
            }
        }

        if (!is_isomorphic) {
            non_isomorphic_components.push_back(subgraph);
            all_components.push_back(subgraph);
            original_id_maps.push_back(original_ids); // Store the original ID map for this subgraph
        }
    }

    cout << "\nFound " << non_isomorphic_components.size() << " non-isomorphic components:" << endl;
    for (int i = 0; i < non_isomorphic_components.size(); ++i) {
        string filename = "graph" + to_string(i + 1) + ".dot";
        custom_write_graphviz(filename, non_isomorphic_components[i], original_id_maps[i]); // Pass the correct ID map
    }
    return non_isomorphic_components.size();
}
