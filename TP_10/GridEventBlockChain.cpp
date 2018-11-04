#include "GridEventBlockChain.h"



GridEventBlockChain::GridEventBlockChain()
{
}


GridEventBlockChain::~GridEventBlockChain()
{
}

BlockChain * GridEventBlockChain::getNewBlockChain()
{
	return &newBlockChain;
}

void GridEventBlockChain::setNewBlockChain(BlockChain * newBlockChain_)
{
	newBlockChain = *newBlockChain_;
}
