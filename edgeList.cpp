#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

class edgeList {
    list<pair<pair<string, string>, double>> edges;
    set<string> vertices;

public:
    void insertEdge(string from, string to, double weight); //might change weights to double instead of int
    bool isEdge(string from, string to);
    vector<double> getWeight(string from, string to); //maybe convert to vector<double> if multiple edges can exist between same airports
    vector<string> getAdjacent(string vertex);
    void printGraph(); //maybe change this to vector<string> so it returns all the vertices
    unordered_map<string, string> edgeListDijkstras(edgeList& graph, string src);
    double getLowestWeight(string from, string to);
    string helperLowest(edgeList& graph, set<string>& visted, unordered_map<string, double>& density );
    
};

void edgeList::insertEdge(string from, string to, double weight) {
    pair<string, string> temp;
    temp.first = from;
    temp.second = to;

    pair<pair<string, string>, double> temp2;
    temp2.first = temp;
    temp2.second = weight;

    edges.push_back(temp2);

    vertices.insert(from); //push into the set
    vertices.insert(to);
}

bool edgeList::isEdge(string from, string to) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->first.first == from) { //access the origin
            if (it->first.second == to) //access the destination
                return true;
        }
    }

    return false;
}

vector<double> edgeList::getWeight(string from, string to) { //returns a vector with only -1 if the edge doesn't exist
    vector<double> weight = { -1 };
    int count = 0;

    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->first.first == from) { //access the origin
            if (it->first.second == to) { //access the destination
                if (count == 0) { //first weight
                    count++;
                    weight[0];
                }
                weight.push_back(it->second);
            }
        }
    }

    return weight;
}

vector<string> edgeList::getAdjacent(string vertex) {
    vector<string> adjVertices;
    set<string> in; //to avoid repeats

    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->first.first == vertex) {
            if (in.count(it->first.second) == 0) { //if the vertex is already in the set/vector
                adjVertices.push_back(it->first.second);
                in.insert(it->first.second);
            }
        }
    }

    return adjVertices;
}

void edgeList::printGraph() {
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        cout << *it << endl;
    }
}

double edgeList::getLowestWeight(string from, string to) { //returns -1 if edge doesn't exist
    vector<double> weights = getWeight(from, to);
    double minWeight = 1;

    for (int i = 0; i < weights.size(); i++) {
        if (weights[i] < minWeight)
            minWeight = weights[i];
    }

    return minWeight;
}
string edgeList::helperLowest(edgeList& graph, set<string>& visted, unordered_map<string, double>& density) {
    int min = INT_MAX;
    string index = "";
    for (auto it = density.begin(); it != density.end(); it++) {
        if (min < density[it->first] && visted.find(it->first) == visted.end()) {
            index = it->first;
        }
    }
    return index;

}

unordered_map<string, string> edgeList::edgeListDijkstras(edgeList& graph, string src) {
    set<string> visted;
    set<string> needToProcess;
    unordered_map<string, double> density; //replaced d, previously vector<int> d
    unordered_map<string, string> parent;
    for (auto it = graph.vertices.begin(); it != graph.vertices.end(); it++) {
        needToProcess.insert(*it); //inserts string verticies 
        density[*it] = INT_MAX;
        parent[*it] = "";
    }
   
    density[src] = 0;
    parent[src] = "";
    
   
   

    visted.insert(src);
    needToProcess.erase(src); 
    


    for (auto it = graph.getAdjacent(src).begin(); it != graph.getAdjacent(src).end(); it++) { //gets adjacent vertexes of the src sring
        density[*it] = graph.getLowestWeight(src, *it);
        parent[*it] = src;

    }

    string current = src;

    while (needToProcess.empty() == false) {
        if (current == "") {
            break;
        }
        for (auto it = graph.getAdjacent(current).begin(); it != graph.getAdjacent(current).end(); it++) {
            if ((density[current] + graph.getLowestWeight(current, *it)) < density[*it]) {
                density[*it] = density[current] + graph.getLowestWeight(current, *it);
                parent[*it] = current;
            }
        }
        needToProcess.erase(current);
        visted.insert(current);
        current = helperLowest(graph, visted, density);

    }
    return parent; 
    
}