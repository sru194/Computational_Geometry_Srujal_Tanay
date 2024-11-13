#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "check_planar.h"       //Include the header file for check_planarity
#include "check_isomorphism.h"  //Include the header for isomorphic components

using namespace std;

bool edge_input(int vertices, string fileName, vector<pair<int, int>>& edges) {
    ifstream file(fileName);
    set<pair<int, int>> distinct_edges;

    if (!file.is_open()) {
        cerr << "Error: Could not open file" << endl;
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        istringstream stream(line);
        int a, b;

        if (!(stream >> a >> b) || !(stream.eof())) {
            cerr << "Error: Invalid format on line " << lineNumber << ". Expected two integers." << endl;
            return false;
        }

        if (a < 0 || a >= vertices || b < 0 || b >= vertices) {
            cerr << "Error: Vertices on line " << lineNumber << " are out of range." << endl;
            return false;
        }

        if (a == b) continue;
        if (a > b) swap(a, b);
        pair<int, int> new_edge = {a, b};

        if (distinct_edges.find(new_edge) == distinct_edges.end()) {
            edges.push_back(new_edge);
            distinct_edges.insert(new_edge);
        }
    }

    return true;
}

int main() {
    cout << "Welcome to the program." << endl << "Enter the graph dimensions you want with a space between them: ";
    int k, r;
    cin >> k >> r;

    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    if (vertices <= 0) {
        cerr << "Error: Enter a positive number of vertices." << endl;
        return -1;
    }
    if (vertices > k * r) {
        cerr << "Error: Vertices greater than maximum k*r graph can include." << endl;
        return -1;
    }

    cout << "Enter filename for edges: ";
    string fileName;
    cin >> fileName;

    vector<pair<int, int>> edges;

    if (!edge_input(vertices, fileName, edges)) return -1;

    // Call the planarity check function
    int planar = check_planarity(vertices, edges);
    cout<<"The number of edges in the kuratowski subgraph is: "<<planar<<"\n\n";

    string command = "dot -Tpng graph.dot -o graph.png "
                     "-Gbgcolor=lightgray "
                     "-Nstyle=filled -Nfillcolor=lightblue -Nfontcolor=darkblue -Nshape=circle "
                     "-Ecolor=orange -Epenwidth=2 "
                     "-Glabel=\"Graph\" -Glabelloc=top -Gfontsize=20";
    if(system(command.c_str()) != 0){
        cerr << "Error: Failed to generate PNG for graph " << endl;
    } 
    else{
        cout << "Generated graph.png successfully." << endl;
    }

    if the graph isnt planar then simply exit from the program
    if(planar > 0){  //this means the graph isnt planar
        return 0;
    }

    //Call the isomorphism components function
    int comp = nonIsoConnectedComponents(vertices,edges);
    cout<<"the number of non-isomorphic connected components is: "<<comp<<"\n\n";

    for (int i = 1; i <= comp; ++i) {
        // Assume that each component generates a `.dot` file named `graph<i>.dot`
        string dotFileName = "graph" + to_string(i) + ".dot";
        string pngFileName = "graph" + to_string(i) + ".png";
        string command = "dot -Tpng " + dotFileName + " -o " + pngFileName + " "
                         "-Gbgcolor=lightgray "
                         "-Nstyle=filled -Nfillcolor=lightblue -Nfontcolor=darkblue -Nshape=circle "
                         "-Ecolor=orange -Epenwidth=2 "
                         "-Glabel=\"Component " + to_string(i) + "\" -Glabelloc=top -Gfontsize=20";
        int result = system(command.c_str());

        // Check if the command executed successfully
        if (result != 0) {
            cerr << "Error: Failed to generate PNG for component " << i << endl;
        } 
        else {
            cout << "Generated " << pngFileName << " successfully." << endl;
        }
    }
    return 0;
}
