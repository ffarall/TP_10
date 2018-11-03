#include "Trader.h"



Trader::Trader()
{
}


Trader::~Trader()
{
}

bool Trader::emitTransaction(Node & fromNode, vector<Node&> toNodes, vector<double> amountsTransfered)
{
	return false;
}

vector<Output*> Trader::getUTXOs()
{
	return UTXOs;
}

bool Trader::isMiner()
{
	return isItMiner;
}

bool Trader::consultBalance()
{
	return false;
}

bool Trader::respondBalanceConsulted()
{
	return false;
}
