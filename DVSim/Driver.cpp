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

	for (int i = 0; i < rounds; ++i) {

	}

}