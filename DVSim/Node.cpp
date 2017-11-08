#include <vector>
using namespace std;

struct Packet {
	int cost;
	int destination;
};

class Node {
private:
	struct Route {
		int cost;
		int destination;
		int nextHop;
	};
	vector<int> neighbors;
	vector<Packet> dvPacket;
	vector<Route> routingTable;
	int convergence;

public:
	bool receiveDV(vector<Packet> dv, int id);
	vector<Packet> sendDV() { return dvPacket; }
	void createDV();
	Node() { }
	void addNeighbor(int, int);
	vector<int> getNeighbors() { return neighbors; }
};

void Node::createDV() {
	dvPacket.clear();
	for (int i = 0; i < routingTable.size(); ++i) {
		Packet temp;
		temp.cost = routingTable[i].cost;
		temp.destination = routingTable[i].destination;
		dvPacket.push_back(temp);
	}
}

bool Node::receiveDV(vector<Packet> dv, int id) {
	int cost;
	bool found, changed;
	Route route;

	changed = false;
	for (int i = 0; i < routingTable.size(); ++i) {
		if (routingTable[i].destination == id) {
			cost = routingTable[i].cost;
		}
	}

	for (int i = 0; i < dv.size(); ++i) {
		found = false;
		for (int j = 0; j < routingTable.size(); ++j) {
			if (routingTable[j].destination == dv[i].destination) {
				found = true;
				if (routingTable[j].cost > dv[i].cost + cost) {
					routingTable[j].cost = dv[i].cost + cost;
					routingTable[j].nextHop = id;
					changed = true;
				}
			}
		}
		if (!found) {
			route.cost = dv[i].cost;
			route.destination = dv[i].destination;
			route.nextHop = id;
			routingTable.push_back(route);
			changed = true;
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