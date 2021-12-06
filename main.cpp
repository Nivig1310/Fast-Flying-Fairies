#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "edgeList.h"
#include "adjacencyList.h"
using namespace std;

int main() {
	cout << "Hello! welcome to Fast Flying Fairies, a COVID-19 conscious service to help you find the least crowded flight(s) to ceratin destinations in the U.S!" << endl;
	bool x = true;
	int choice;
	string origin;
	string destination;
    edgeList eList;
    Graph adjList;
    eList.readFile(); //data is put into the edge list
    adjList.readFile(); //data is put into the adjacency list

	while (x == true) {
		cout << "What do you need help with?";
		cout << "1. List of all airports available in our service" << endl;
		cout << "2. Find airport route version 1" << endl;
        cout << "3. Find airport route version 2" << endl;
		cout << "4. End the program" << endl;
		cin >> choice;
       
		if (choice == 1) { //prints out all the airports
			eList.printGraph(); 
		}

		else if (choice == 2) { //return the route & passenger to seat ratio with each edge, edge list
			cout << "Nice! enter your origin location" << endl;
			cin >> origin;
			cout << "Now enter your destination" << endl;
			cin >> destination;
			//complete the graph algorithm to find the shortest route to destination
		}

        else if (choice == 3) { //return the route & passenger to seat ratio with each edge, adjacency list
			cout << "Nice! enter your origin location" << endl;
			cin >> origin;
			cout << "Now enter your destination" << endl;
			cin >> destination;
			//complete the graph algorithm to find the shortest route to destination
		}

		else if (choice == 4) {
			cout << "Thanks for using us!" <<endl;
			x = false;
		}

		else {
			cout << "Sorry! not a choice, please try again";
		}
		
	}

	return 0;
}
