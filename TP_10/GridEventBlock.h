#pragma once
#include "GridEvent.h"

class GridEventBlock :
	public GridEvent
{
public:
	GridEventBlock();
	virtual ~GridEventBlock();
	Block* getNewBlock();
	void setNewBlock(Block * newBlock_);

protected:
	// Event content if it is NEW_BLOCK_MINED.
	Block newBlock;
};

