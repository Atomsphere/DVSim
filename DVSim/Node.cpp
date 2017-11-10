#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

void Node::createDV() {
	dvPacket.clear();
	for (int i = 0; i < routingTable.size(); ++i) {
		Packet temp;
		temp.cost = routingTable[i].cost;
		temp.destination = routingTable[i].destination;
		dvPacket.push_back(temp);
	}
}

bool Node::receiveDV(vector<Packet> dv, int sender) {
	int costToSender;
	bool found, changed;
	Route route;
	changed = false;
	for (int i = 0; i < routingTable.size(); ++i) {
		if (routingTable[i].destination == sender) {
			costToSender = routingTable[i].cost;
		}
	}

	for (int i = 0; i < dv.size(); ++i) {
		found = false;
		if (dv[i].destination != id) {
			for (int j = 0; j < routingTable.size(); ++j) {
				if (routingTable[j].destination == dv[i].destination) {
					found = true;
					if (routingTable[j].cost > dv[i].cost + costToSender) {
						routingTable[j].cost = dv[i].cost + costToSender;
						routingTable[j].nextHop = sender;
						changed = true;
					}
				}
			}
			if (!found) {
				route.cost = dv[i].cost + costToSender;
				route.destination = dv[i].destination;
				route.nextHop = sender;
				routingTable.push_back(route);
				changed = true;
			}
		}
	}
	return changed;
}

//************
//addNeighbor- takes the destination and the cost
//records them as neighbors and initializes them in the
//routing table
//***********
void Node::addNeighbor(int node, int dist) {
	Route temp;
	temp.cost = dist;
	temp.destination = node;
	temp.nextHop = node;
	neighbors.push_back(node);
	routingTable.push_back(temp);
}

void Node::printRT(int id) {
	cout << "\nThe routing table for " << id << endl;
	for (int i = 0; i < routingTable.size(); ++i) {
		cout << "destination: " << routingTable[i].destination << "\tcost: "
			<< routingTable[i].cost << "\tNexthop: " << routingTable[i].nextHop << endl; 
	}
}

int Node::routePacket(int data)
{
	int index = 0;
	for (int i = 0; i < routingTable.size(); ++i) {
		if (routingTable[i].destination == data) {
			index = i;
		}
	}
	
	return routingTable[index].nextHop;
}
