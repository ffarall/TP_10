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



void Node::sendInformation(GridEvent & info)
{
	Node* emitter = info.getEmisor(); //guardo el emisor original
	GridEvent* localEvent = new GridEvent(info);//creo un nuevo evento para distribuir
	localEvent->setEmisor(this);//cambio el emisor al nodo actual
	for (Node* neighbour : neighbours)
	{
		if (neighbour != emitter) //para todos los vecinos, menos el que envia el mensaje, envio el evento
		{
			neighbour->receiveNewInformation(info);
		}
	}
	delete localEvent;
}


void Node::receiveNewInformation(GridEvent & info)
{
	if (isNewEvent())
	{
		infoPackages.push(info);
		if (!(info.getType() == GridEventType::ASK_FOR_BLOCKCHAIN || info.getType() == GridEventType::GET_BLOCKCHAIN))
		{
			sendInformation(info);
		}
	}
}

GridEvent  Node::getNewInformation()
{
	GridEvent temp = infoPackages.front();
	infoPackages.pop();  //no estoy seguro de que esto sea necesario!!
	return temp;
}
