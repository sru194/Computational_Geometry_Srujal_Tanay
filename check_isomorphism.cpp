#include <iostream>     
#include <vector>       
#include <map>         
#include <set>         
#include <algorithm>   
using namespace std;

// Function to perform DFS and collect components
void DFS(int v, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    
    for(int u : adj[v]) {
        if(!visited[u]) {
            DFS(u, adj, visited, component);
        }
    }
}

// Function to get all connected components
vector<vector<int>> getConnectedComponents(vector<vector<int>>& adj, int V) {
    vector<bool> visited(V, false);
    vector<vector<int>> components;
    
    for(int v = 0; v < V; v++) {
        if(!visited[v]) {
            vector<int> component;
            DFS(v, adj, visited, component);
            components.push_back(component);
        }
    }
    return components;
}

// Function to get canonical labeling for a component
vector<int> getCanonicalLabeling(const vector<int>& component, vector<vector<int>>& adj) {
    int n = component.size();
    vector<int> label(n);
    vector<vector<bool>> subgraph(n, vector<bool>(n, false));
    
    // Create adjacency matrix for the component
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int v1 = component[i];
            int v2 = component[j];
            auto it = find(adj[v1].begin(), adj[v1].end(), v2);
            if(it != adj[v1].end()) {
                subgraph[i][j] = subgraph[j][i] = true;
            }
        }
    }
    
    // Initialize partition
    vector<int> partition(n, 0);
    
    // Refine partition until stable
    bool changed = true;
    while(changed) {
        changed = false;
        vector<int> new_partition = partition;
        
        for(int i = 0; i < n; i++) {
            vector<int> signature;
            for(int j = 0; j < n; j++) {
                if(subgraph[i][j]) {
                    signature.push_back(partition[j]);
                }
            }
            sort(signature.begin(), signature.end());
            
            int hash = 0;
            for(int s : signature) {
                hash = hash * 31 + s;
            }
            new_partition[i] = hash;
        }
        
        if(new_partition != partition) {
            changed = true;
            partition = new_partition;
        }
    }
    
    return partition;
}

// Function to find non-isomorphic components
vector<vector<int>> findNonIsomorphicComponents(vector<vector<int>>& adj, int V) {
    vector<vector<int>> components = getConnectedComponents(adj, V);
    vector<vector<int>> non_isomorphic;
    map<vector<int>, bool> seen;
    
    for(const auto& component : components) {
        vector<int> canonical = getCanonicalLabeling(component, adj);
        
        if(!seen[canonical]) {
            seen[canonical] = true;
            non_isomorphic.push_back(component);
        }
    }
    
    return non_isomorphic;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    
    // Initialize adjacency list
    vector<vector<int>> adj(V);
    
    cout << "Enter " << E << " edges (format: a b):" << endl;
    for(int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        // Add edge (assuming 0-based indexing)
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Find and print non-isomorphic components
    vector<vector<int>> result = findNonIsomorphicComponents(adj, V);
    
    cout << "\nFound " << result.size() << " non-isomorphic components:" << endl;
    for(const auto& component : result) {
        cout << "Component: ";
        for(int v : component) {
            cout << v << " ";
        }
        cout << "\nEdges: ";
        set<pair<int, int>> printed_edges; // To avoid printing duplicate edges
        for(int v : component) {
            for(int u : adj[v]) {
                if(find(component.begin(), component.end(), u) != component.end() && 
                   printed_edges.find({min(u,v), max(u,v)}) == printed_edges.end()) {
                    cout << "(" << v << "," << u << ") ";
                    printed_edges.insert({min(u,v), max(u,v)});
                }
            }
        }
        cout << "\n\n";
    }
    
    return 0;
}