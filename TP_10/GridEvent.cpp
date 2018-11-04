#include "GridEvent.h"



GridEvent::GridEvent()
{
}


GridEvent::GridEvent(const GridEvent & event_)
{
	//copiar todo re loco
}

GridEvent::~GridEvent()
{
}

void GridEvent::setType(GridEventType type_)
{
	type = type_;
}

void GridEvent::setEmisor(Node * emisor_)
{
	emisor = emisor_;
}

GridEventType GridEvent::getType()
{
	return type;
}

Node * GridEvent::getEmisor()
{
	return emisor;
}
