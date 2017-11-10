//************************************************
//Mark Maupin
//CS 4310
//Project 1
//11-10-17
//DV Packet simulator
//************************************************
#include<fstream>
#include<iostream>
#include<cstdlib>
#include"Node.h"
using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 5) {
		cout << "Error: incorrect command line arguments found.";
		return 1;
	}

	int rounds = atoi(argv[2]);
	int next = atoi(argv[3]);
	int data = atoi(argv[4]);

	ifstream input(argv[1]);
	if (!input) {
		cout << "Input file not found.\n";
		return 2;
	}
	vector<int> tempNodes;
	Node * network;
	int * changeTracker;
	int node1, node2, distance, index, temp, netSize = 0;
	vector<Packet> dvPacket;
	vector<int> neighbors;
	bool changed;

	//preprocess file for number of nodes
	while (input >> node1) {
		input >> node2 >> distance;
		tempNodes.push_back(node1);
		tempNodes.push_back(node2);
	}
	for (int i = 0; i < tempNodes.size(); ++i) {
		if (netSize < tempNodes[i])
			netSize = tempNodes[i];
	}
	network = new Node [netSize + 1];
	changeTracker = new int[netSize + 1]{ 0 };
	input.clear();
	input.seekg(0, input.beg);
	//end preprocess

	//initialize network
	while (input >> node1) {
		input >> node2 >> distance;
		network[node1].addNeighbor(node2, distance);
		network[node2].addNeighbor(node1, distance);
	}
	for (int i = 0; i <= netSize; ++i) {
		network[i].setID(i);
	}

	//primary loop
	for (int i = 0; i < rounds; ++i) {
		for (int j = 0; j <= netSize; ++j) {
			network[j].createDV();
		}
		for (int j = 0; j <= netSize; ++j) {
			dvPacket = network[j].sendDV();
			neighbors = network[j].getNeighbors();
			for (int k = 0; k < neighbors.size(); ++k) {
				changed = network[neighbors[k]].receiveDV(dvPacket, j);
				if (changed)
					changeTracker[neighbors[k]] = i;
			}
		}
	}

	for (int i = 0; i <= netSize; ++i) {
		network[i].printRT(i);
	}

	temp = 0;
	for (int i = 0; i <= netSize; ++i) {
		if (changeTracker[i] > temp) {
			temp = changeTracker[i];
		}
	}

	cout << "\nThe following nodes finished last after " << temp + 1 << " rounds:\n";
	for (int i = 0; i <= netSize; ++i) {
		if (changeTracker[i] == temp) {
			cout << i << endl;
		}
	}
	
	int total = 0;
	for (int i = 0; i <= netSize; ++i) {
		total += network[i].getNeighborCount();
	}

	cout << "\n" << total*(temp+1) << " DV packets were sent before convergence.\n";

	cout << "\nPacket sent from " << next << " to " << data
		<< " routes as follows:\n" << next;
		
	while (next != data) {
		cout << " -> ";
		next = network[next].routePacket(data);
		cout << next;
	}
	cout << endl;
	
	delete[] network;
	delete[] changeTracker;
	return 0;
}