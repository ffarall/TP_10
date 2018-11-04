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
	// Checks UTXO to this node's name in transactionBuffer, currentBlock and in blockChain.
	virtual uint32_t consultBalance();

protected:
	//Process and validate received GridEvent from queue.
	virtual bool processEvent(GridEvent* gridEvent);
	// Tries to mine with one nounce the currentBlock.
	bool mine();
	// Consults balance in currentBlock's transactions.
	uint32_t consultBalanceInCurrentBlock();

	// Block that is being mined right now.
	Block currentBlock;
	//bool to know when to refresh current mining block
	bool needNewBlock;
	//used to create new currentBlock
	void refreshCurrentBlock();
	// List of nounces already tried.
	vector<uint32_t> triedNounces;
	//  returns true if a number is already in triedNounces
	bool wasTried(uint32_t number);
	// check if hash satisfies the challenge
	bool challengeHash(std::string hash);
	//delete all tried nounces from vector
	void clearTriedNounces();
	
};

