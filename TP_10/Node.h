#pragma once
#include "GridEvent.h"
#include <vector>
#include <queue>
#include <cryptlib.h>

using namespace std;

class Node
{
public:
	Node();
	virtual ~Node();

	void addNeighbour(Node&);

	vector<Node&> getNeighbours();

	bool sendInformation(GridEvent& info);
	bool isNewInformation();
	bool receiveNewInformation(GridEvent& info);
	GridEvent& getNewInformation();

protected:
	// List of neighbours.
	vector<Node&> neighbours;
	// Pile of information packages received.
	queue<GridEvent&> infoPackages;
};

