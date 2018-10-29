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
	Node* emisor = info.getEmisor(); //guardo el emisor original
	info.setEmisor(this);
	for (Node* neighbour : neighbours)
	{
		if (neighbour != emisor) //para todos los vecinos, menos el que envia el mensaje, envio el evento
		{
			neighbour->receiveNewInformation(info);
		}
	}
}


bool Node::receiveNewInformation(GridEvent & info)
{
	return false;
}

GridEvent * Node::getNewInformation()
{
	GridEvent* temp = infoPackages.front();
	infoPackages.pop();  //no estoy seguro de que esto sea necesario!!
	return temp;
}
