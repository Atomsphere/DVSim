#include<iostream>
#include<fstream>
#include"Node.cpp"
using namespace std;

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cout << "Error: incorrect command line arguments found.";
		return 1;
	}

	int rounds = atoi(argv[1]);
	ifstream input(argv[0]);
	vector<int> tempNodes;
	Node * network;
	int * changeTracker;
	int node1, node2, distance, index, netSize = 0;
	vector<Packet> dvPacket;
	vector<int> neighbors;

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
	changeTracker = new int[netSize + 1];
	input.clear();
	input.seekg(0, input.beg);
	//end preprocess

	//initialize network
	while (input >> node1) {
		input >> node2 >> distance;
		network[node1].addNeighbor(node2, distance);
		network[node2].addNeighbor(node1, distance);
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
				network[neighbors[k]].receiveDV(dvPacket, j);
			}
		}
	}

}

