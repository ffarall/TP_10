#pragma once
#include "GridEvent.h"
class GridEventBlockChain :
	public GridEvent
{
public:
	GridEventBlockChain();
	virtual ~GridEventBlockChain();

protected:
	// Event content if it is GET_BLOCKCHAIN.
	BlockChain newBlockChain;
};

