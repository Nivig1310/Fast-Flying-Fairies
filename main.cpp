#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
int main() {
	cout << "Hello! welcome to Fast Flying Faries, we are a service to help you find the fastest destination to where ever you want to go!" << endl;
	bool x = true;
	int choice;
	string origin;
	string destination;
	while (x == true) {
		cout << "what do you need help with?";
		cout << "1. List of all airports" << endl;
		cout << "2. Find airport route" << endl;
		cout << "3. find distnace" << endl;
		cout << "4. end the program" << endl;
		cin >> choice;
		if (choice == 1) {
			//list all airports 
		}
		else if (choice == 2) {
			cout << "nice! enter your origin location" << endl;
			cin >> origin;
			cout << "now enter your destination" << endl;
			cin >> destination;
			//complete the graph algorithm to find the shortest route to destination
		}
		else if (choice == 3) {
			cout << "nice! enter your origin location" << endl;
			cin >> origin;
			cout << "now enter your destination" << endl;
			cin >> destination;
			//complete path algorithm to find the distance 
		}
		else if (choice == 4) {
			cout << "thanks for using us!" <<endl;
			x = false;
		}
		else {
			cout << "sorry! not a choice";
		}
		
	}

	return 0;
}
