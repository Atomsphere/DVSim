#include<vector>
#include"Packet.h"
using namespace std;
class Node {
private:
	struct Route {
		int cost;
		int destination;
		int nextHop;
	};
	int id;
	vector<int> neighbors;
	vector<Packet> dvPacket;
	vector<Route> routingTable;
public:
	bool receiveDV(vector<Packet>, int);
	vector<Packet> sendDV() { return dvPacket; }
	void createDV();
	Node() { }
	void addNeighbor(int, int);
	vector<int> getNeighbors() { return neighbors; }
	void printRT(int);
	void setID(int a) { id = a; }
	int routePacket(int);
	int getNeighborCount() { return neighbors.size(); }
};

