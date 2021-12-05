#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<map>
#include<fstream>
#include <set>
using namespace std;



class Graph
{
public:
    map<string, vector<pair<string,double>>> graph;
    set<double> edges;
public:
    void insertEdge(string from, string to, double weight);
    bool isEdge(string from, string to);
    vector<double> getWeight(string from, string to);
    vector<string> getAdjacent(string vertex);
    void printGraph();
};

void Graph::insertEdge(string from, string to, double weight)
{

    graph[from].push_back(make_pair(to, weight));
    if(graph.find(to)==graph.end()){
        graph[to] = {};
    }
}

bool Graph::isEdge(string from, string to)
{

    for(auto it = graph[from].begin(); it != graph[from].end(); it++){
        if(it->first == to)
            return true;
    }
    return false;
}

vector<double> Graph::getWeight(string from, string to)
{
    vector<double> weights;
    for(auto it = graph[from].begin(); it != graph[from].end(); it++){
        if(it->first == to) {
            weights.push_back(it->second);
        }
    }
    return weights;
}

vector<string> Graph::getAdjacent(string vertex)
{
    vector<string> neighbors;
    for(auto it = graph[vertex].begin(); it != graph[vertex].end(); it++){
        neighbors.push_back(it->first);
    }
    sort(neighbors.begin(), neighbors.end());

    return neighbors;
}

void Graph::printGraph(){
    for(auto iter = graph.begin(); iter != graph.end(); iter++){
        cout << endl;
        cout << iter->first;
        for(int i = 0; i < graph[iter->first].size(); i++){
            cout << " " << graph[iter->first].at(i).first;
        }
        cout << endl;
    }
}


void readFile(Graph& graph){
    ifstream file("Airports2.csv");
    if (file.is_open()) {

        //step 0. dealing w first line of data
        string FirstLine;
        getline(file, FirstLine);
        cout << FirstLine;
        //
        int i = 0;
        while(getline(file, FirstLine) && i < 100000){
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
            getline(stream,destination_air, ',');
            getline(stream, origin_city, ',');
            getline(stream, dest_city, ',');
            getline(stream, bs, ',');
            getline(stream, bs2, ',');
            getline(stream, passengers, ',');
            getline(stream, seats, ',');
            result = ((double)stoi(passengers)/(double)stoi(seats));
            graph.insertEdge(origin_air,destination_air,result);
            //now each of these variables holds the values u need.
            i++;
        }
    }


};


int main(){
    Graph graph;
    readFile(graph); //now "graph" holds an adjacency list
    return 0;
}

