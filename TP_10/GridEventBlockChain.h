#pragma once
#include "GridEvent.h"
class GridEventBlockChain :
	public GridEvent
{
public:
	GridEventBlockChain();
	virtual ~GridEventBlockChain();
	BlockChain* getNewBlockChain();
	void setNewBlockChain(BlockChain * newBlockChain_);

protected:
	// Event content if it is GET_BLOCKCHAIN.
	BlockChain newBlockChain;
};

