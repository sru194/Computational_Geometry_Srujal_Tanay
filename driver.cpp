#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <sstream>

using namespace std;

bool edge_input(int vertices,string fileName,vector<pair<int,int>>& edges){
    ifstream file(fileName);

    set<pair<int,int>> distinct_edges;

    if(!file.is_open()){
        cerr<<"Error: Could not open file"<<endl;
        return 0;
    }

    string line;
    int lineNumber = 0;

    while(getline(file,line)){
        lineNumber++;
        istringstream stream(line);
        int a,b;

        if (!(stream >> a >> b) || !(stream.eof())) {
            cerr<<"Error: Invalid format on line "<<lineNumber<<". Expected two integers."<<endl;
            return 0;
        }

        if(a < 0 || a > vertices || b < 0 || b > vertices){
            cerr<<"Error: Vertices on line "<<lineNumber<<" are out of range."<<endl;
            return 0;
        }

        if(a == b) continue;
        if(a > b) swap(a,b);
        pair<int,int> new_edge = {a,b};

        if(distinct_edges.find(new_edge) == distinct_edges.end()){
            edges.push_back(new_edge);
            distinct_edges.insert(new_edge);
        }
    }

    return 1;
}


int main(){
    int vertices;
    cout<<"Enter the number of vertices."<<endl;
    cin>>vertices;

    if(vertices <= 0){
        cerr<<"Error: Enter positive number of vertices."<<endl;
        return -1;
    }

    //for now, we expect edges in (a,b) format.

    cout<<"Enter filename for edges."<<endl;

    string fileName;
    cin>>fileName;

    vector<pair<int,int>> edges;

    if(!edge_input(vertices,fileName,edges)) return -1;

    //Planarity check in O(n). Found a C# implementation that has worst case O(n^2) implementation.
    //-------//

    //if No, print not possible and end early.

    //vector of non-isomorphic connected components of G using Hopcroft-Wong (O(n)). No implementations found, might have to do it on our own.
    //------//



    return 0;
}