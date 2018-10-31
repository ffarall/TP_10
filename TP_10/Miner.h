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
	bool needNewBlock;
	//used to create new currentBlock
	bool refreshCurrentBlock();
	// List of nounces already tried.
	vector<uint32_t> triedNounces;
	//  returns true if a number is already in triedNounces
	bool wasTried(uint32_t number);
	// check if hash satisfies the challenge
	bool challengeHash(std::string hash);

	
};

