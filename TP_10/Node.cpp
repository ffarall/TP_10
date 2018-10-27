#include "Node.h"



Node::Node()
{
}


Node::~Node()
{
}

void Node::addNeighbour(Node & newNeighbour)
{
	neighbours.push_back(&newNeighbour);
}

vector<Node*> Node::getNeighbours()
{
	return neighbours;
}

bool Node::sendInformation(GridEvent & info)
{
	return false;
}

GridEvent * Node::getNewInformation()
{
	GridEvent* temp = infoPackages.front();
	infoPackages.pop();  //no estoy seguro de que esto sea necesario!!
	return temp;
}
