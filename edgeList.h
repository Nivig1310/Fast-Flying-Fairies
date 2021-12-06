#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <set>
#include <unordered_map>
#include <stack>
using namespace std;

class edgeList{
    list<pair<pair<string, string>, double>> edges;
    set<string> vertices;
    string helperLowest(edgeList& graph, set<string>& visted, unordered_map<string, double>& density);
    void printRoute(unordered_map<string, string> parents, double avgDensity, string to);

    public:
        void insertEdge(string from, string to, double weight);
        bool isEdge(string from, string to);
        vector<double> getWeight(string from, string to);
        double getLowestWeight(string from, string to);
        vector<string> getAdjacent(string vertex);
        void printGraph();
        void readFile(); //inserts edges here
        void edgeListDijkstras(edgeList& graph, string src, string to);
};

void edgeList::insertEdge(string from, string to, double weight){
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

bool edgeList::isEdge(string from, string to){
    for(auto it = edges.begin(); it != edges.end(); ++it){
        if(it->first.first == from){ //access the origin
            if(it->first.second == to) //access the destination
                return true;
        }
    }

    return false;
}

vector<double> edgeList::getWeight(string from, string to){ //returns a vector with only -1 if the edge doesn't exist, helper function for getLowestWeight
    vector<double> weight = {-1};
    int count = 0;

    for(auto it = edges.begin(); it != edges.end(); ++it){
        if(it->first.first == from){ //access the origin
            if(it->first.second == to){ //access the destination
                if(count == 0){ //first weight
                    count++;
                    weight[0];
                }
                weight.push_back(it->second);
            }
        }
    }

    return weight;
}

double edgeList::getLowestWeight(string from, string to){ //returns -1 if edge doesn't exist
    vector<double> weights = getWeight(from, to);
    double minWeight = 1;

    for(int i = 0; i < weights.size(); i++){
        if(weights[i] < minWeight)
            minWeight = weights[i];
    }

    return minWeight;
}

vector<string> edgeList::getAdjacent(string vertex){
    vector<string> adjVertices;
    set<string> in; //to avoid repeats
    
    for(auto it = edges.begin(); it != edges.end(); ++it){
        if(it->first.first == vertex){
            if(in.count(it->first.second) == 0){ //if the vertex is already in the set/vector
                adjVertices.push_back(it->first.second);
                in.insert(it->first.second);
            }
        }
    }

    return adjVertices;
}

void edgeList::printGraph(){ 
    for(auto it = vertices.begin(); it != vertices.end(); ++it){
        cout << *it << " ";
    }
}

void edgeList::readFile(){
    ifstream file("Airports2.csv");
    string line = ""; 
    int i = 0;

    string from = "";
    string to = "";
    string passengers = "";
    string seats = "";
    string boof = "";
    double weight = 0;
    
    getline(file, line); //get first line of headings
    while(getline(file, line) && i < 100000){
        istringstream ss(line);
        getline(ss, from, ',');
        getline(ss, to, ',');
        from = from.substr(1, 3); //cut off the quotes
        to = to.substr(1, 3);

        for(int j = 0; j < 4; j++) //get all the unneeded stuff out of the way
            getline(ss, boof, ',');
        
        getline(ss, passengers, ',');
        getline(ss, seats, ',');
        weight = ((double)stoi(passengers))/((double)stoi(seats)); //convert both seats and passengers to int and then into double
    
        insertEdge(from, to, weight);
        i++;
    }
}

string edgeList::helperLowest(edgeList& graph, set<string>& visted, unordered_map<string, double>& density) {
    int min = INT_MAX;
    string index = "";
    for (auto it = density.begin(); it != density.end(); it++) {
        if (min > density[it->first] && visted.find(it->first) == visted.end()) {
            index = it->first;
            min = density[it->first];
        }
    }
    return index;
}

void edgeList::edgeListDijkstras(edgeList& graph, string src, string to) { //returns parent map
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

    printRoute(parent, density[to], to);
}

void edgeList::printRoute(unordered_map<string, string> parent, double avgDensity, string to){
    if(parent[to] == "") //if no connection exists between origin and destination
        cout << "No connection from the origin airport to the desired destination airport" << endl;
    
    else{ //if the connection exiss
        stack<string> airports; //take in the parents starting from the destination all the way to the source
        airports.push(to); //start from the destination
        string cur = to;

        while(cur != ""){ //cur is only "" if the source has been added into the stack already
            if(parent[cur] != "")
                airports.push(parent[cur]);
            
            cur = parent[cur];
        }

        avgDensity = avgDensity / airports.size(); //set the average density to the correct value
        
        cout << "Your route is: ";
        while(airports.size() > 0){
            if(airports.size() == 1) //if it's going to print out the destination airport
                cout << airports.top() << endl;
            else
                cout << airports.top() << "-->";
            
            airports.pop();
        }

        cout << "The average density (passenger to available seats ratio) of this route is: " << avgDensity << endl;
    }
}
