#pragma once
#include "GridEvent.h"
#include <vector>
#include <queue>
#include <chrono>
#include <cryptlib.h>

using namespace std;

class Node
{
public:
	Node();
	virtual ~Node();

	void addNeighbour(Node& newNeighbour);
	
	vector<Node*> getNeighbours();

	virtual bool isNewEvent() = 0;

	void sendInformation(GridEvent& info);
	//bool isNewInformation();
	void receiveNewInformation(GridEvent& info);
	GridEvent getNewInformation();

protected:
	// List of neighbours.
	vector<Node*> neighbours;
	// Pile of information packages received.
	queue<GridEvent> infoPackages;
	

};

