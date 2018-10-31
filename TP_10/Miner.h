#pragma once
#include "FullService.h"
#include "Block.h"
#include "Transaction.h"

#include <stack>
#include <cstdint>

class Miner :
	public FullService
{
public:
	Miner();
	virtual ~Miner();

	// This is what you call when this node is given time to act. Non-blocking, just one cycle.
	virtual bool runCycle();

protected:
	//Process and validate recieved GridEvent from queue.
	virtual bool processEvent(GridEvent* gridEvent);
	// Tries to mine with one nounce the currentBlock.
	bool mine();

	// Block that is being mined right now.
	Block currentBlock;
	//bool to know when to refresh current mining block
	bool refreshCurrentBlock;
	
	// List of nounces already tried.
	stack<uint32_t> triedNounces;

	
};

