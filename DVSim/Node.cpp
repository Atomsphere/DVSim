#include <vector>
using namespace std;

class Node {
private:
	struct Route {
		int cost;
		int destination;
		int nextHop;
	};
	struct Packet {
		int cost;
		int destination;
	};

	int id;
	vector<Route> neighbors;
	vector<Packet> dvPacket;
	vector<Route> routingTable;

public:
	bool receiveDV(vector<Packet> dv, int id);
	void createDV();
	Node(int identity) { id = identity; }

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

}