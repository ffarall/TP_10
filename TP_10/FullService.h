#pragma once
#include "Trader.h"
#include "BlockChain.h"
#include<list>

using namespace std;

class FullService :
	public Trader
{
public:
	FullService();
	virtual ~FullService();
	virtual bool runCycle();

protected:
	//Process and validate recieved GridEvent from queue.
	virtual bool processEvent(GridEvent* gridEvent);
	// A FullService can responde this.
	bool respondBalanceConsulted();
	// Checks if a transaction is well formed.
	bool validateTransaction();
	// Checks if a block is well formed.
	bool validateBlock();
	// Buffer for transactions to be mined after.
	list<Transaction> transactionsBuffer;

	virtual bool consultBalance();

	// Internal BlockChain saved by every FullService.
	BlockChain* blockChain;
};

