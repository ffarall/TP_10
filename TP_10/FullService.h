#pragma once
#include "Trader.h"
#include "BlockChain.h"

using namespace std;

class FullService :
	public Trader
{
public:
	FullService();
	virtual ~FullService();

protected:
	// A FullService can responde this.
	bool respondBalanceConsulted();
	// Checks if a transaction is well formed.
	bool validateTransaction();
	// Checks if a block is well formed.
	bool validateBlock();
	// Buffer for transactions to be mined after.
	vector<Transaction> transactionsBuffer;

	virtual bool consultBalance();

	// Internal BlockChain saved by every FullService.
	BlockChain& blockChain;
};

