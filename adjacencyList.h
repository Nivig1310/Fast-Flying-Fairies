#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <fstream>
#include <set>
#include<unordered_map>
using namespace std;

class Graph
{
public:
    map<string, vector<pair<string, double>>> graph;
public:
    void insertEdge(string from, string to, double weight);
    bool isEdge(string from, string to);
    vector<double> getWeight(string from, string to);
    vector<string> getAdjacent(string vertex);
    void printGraph();
    void readFile();
    double getLowestWeight(string from, string to);
    void adjListDijkstras(Graph& Graph, string src, string to);
    string helperLowest(Graph& Graph, set<string>& visted, unordered_map<string, double>& density);
    void printRoute(unordered_map<string, string>& parent, double& avgDensity, string& to);






};

void Graph::insertEdge(string from, string to, double weight)
{

    graph[from].push_back(make_pair(to, weight));
    if (graph.find(to) == graph.end()) {
        graph[to] = {};
    }
}

bool Graph::isEdge(string from, string to)
{

    for (auto it = graph[from].begin(); it != graph[from].end(); it++) {
        if (it->first == to)
            return true;
    }
    return false;
}

vector<double> Graph::getWeight(string from, string to) //return -1 if no edge exists between from and to
{
    vector<double> weights;
    int count = 0;
    for (auto it = graph[from].begin(); it != graph[from].end(); it++) {
        if (it->first == to) {
            if (count == 0) { //first weight
                count++;
                weights[0];
            }
            weights.push_back(it->second);
        }
    }
    return weights;
}

vector<string> Graph::getAdjacent(string vertex)
{
    vector<string> neighbors;
    int x = graph[vertex].size();
    for (int i = 0; i < graph[vertex].size(); i++){ //m where m is the number of adjacents
        if(graph[vertex].at(i).first != vertex)
            neighbors.push_back(graph[vertex].at(i).first);
    }

    return neighbors;
}

double Graph::getLowestWeight(string from, string to) {
    vector<double> weights = getWeight(from, to);
    double min = 1.0;
    for (int i = 0; i < weights.size(); i++) {
        if (weights.at(i) < min)
            min = weights.at(i);
    }
    return min;
}

void Graph::printGraph() {
    for (auto iter = graph.begin(); iter != graph.end(); iter++) {
        cout << endl;
        cout << iter->first;
        for (int i = 0; i < graph[iter->first].size(); i++) {
            cout << " " << graph[iter->first].at(i).first;
        }
        cout << endl;
    }
}


void Graph::readFile() {
    ifstream file("Airports2.csv");
    if (file.is_open()) {

        //step 0. dealing w first line of data
        string FirstLine;
        getline(file, FirstLine);
        //
        int i = 0;
        while (getline(file, FirstLine) && i < 100000) {
            //create a stream from line of data
            istringstream stream(FirstLine);
            string origin_air;
            string destination_air;
            string origin_city;
            string dest_city;
            string bs;
            string bs2;
            string passengers;
            string seats;
            double result = 0.0;

            getline(stream, origin_air, ',');
            getline(stream, destination_air, ',');
            getline(stream, origin_city, ',');
            getline(stream, dest_city, ',');
            getline(stream, bs, ',');
            getline(stream, bs2, ',');
            getline(stream, passengers, ',');
            getline(stream, seats, ',');
            result = ((double)stoi(passengers) / (double)stoi(seats));
            origin_air = origin_air.substr(1, 3);
            destination_air = destination_air.substr(1, 3);
            insertEdge(origin_air, destination_air, result);
            //now each of these variables holds the values u need.
            i++;
        }
    }

}

string Graph::helperLowest(Graph& Graph, set<string>& visted, unordered_map<string, double>& density) { //
    int min = INT_MAX;
    string index = "";
    for (auto it = density.begin(); it != density.end(); it++) {
        if (min > density[it->first] && visted.find(it->first) == visted.end()){
            min = density[it->first];
            index = it->first;
        }
    }
    return index;
}



 void Graph::adjListDijkstras(Graph& Graph, string src, string to) {
    set<string> visited;
    set<string> needToProcess;
    unordered_map<string, double> density; //replaced d, previously vector<int> d
    unordered_map<string, string> parent;
    //puts all vertices in need to process
    for (auto it = Graph.graph.begin(); it != Graph.graph.end(); it++) { //O(v) where v is the number of vertices
        needToProcess.insert(it->first);
        density[it->first] = INT_MAX;
        parent[it->first] = "";
    }

    density[src] = 0;
    parent[src] = "";

    visited.insert(src);
    needToProcess.erase(src); //O(1)
    vector<string> neighbors = Graph.getAdjacent(src); //O(m)

    //loop through neighbors of src and set their lowest weights as their distances. Set parent
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) { //O(m)
        density[*it] = Graph.getLowestWeight(src, *it); //O(e)
        parent[*it] = src;
    }

    string current = src;

    while (needToProcess.empty() == false){ //while needtoprocess isnt empty //O(v)
        if (current == "") {
            break;
        }
        vector<string> x =  Graph.getAdjacent(current); //O(m)
        for (auto it = x.begin(); it != x.end(); it++) { //O(m)
            if ((density[current] + Graph.getLowestWeight(current, *it)) < density[*it]) { //relaxation
                density[*it] = density[current] + Graph.getLowestWeight(current, *it); //O(e)
                parent[*it] = current;
            }
        }
        needToProcess.erase(current);
        visited.insert(current);
        current = Graph.helperLowest(Graph, visited, density); //O(v)
    }
     printRoute(parent, density[to], to);
}



void Graph::printRoute(unordered_map<string, string>& parent, double& avgDensity, string& to){
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

        avgDensity = avgDensity / (airports.size()-1); //set the average density to the correct value

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
