#pragma once
#include "Trader.h"
#include "BlockChain.h"
#include <vector>

using namespace std;

class FullService :
	public Trader
{
public:
	FullService();
	virtual ~FullService();
	// In a FullService only processes the events.
	virtual bool runCycle();
	// Checks UTXO to this node's name in transactionBuffer and in blockChain.
	virtual uint32_t consultBalance();

protected:
	//Process and validate recieved GridEvent from queue.
	virtual bool processEvent(GridEvent* gridEvent);
	// A FullService can responde this.
	bool respondBalanceConsulted();
	// Checks if a transaction is well formed, in which case returns true, otherwise false.
	bool validateTransaction(Transaction * transactionToValidate);
	// Checks if a block is well formed.
	bool validateBlock();
	// Consults balance in transactionBuffer's transactions.
	uint32_t consultBalanceInBuffer();
	// Consults balance in blockChain's transactions.
	uint32_t consultBalanceInBlockChain();

	// Buffer for transactions to be mined after.
	vector<Transaction*> transactionsBuffer;
	//check if transactions in block are in trans buffer
	bool isInTransactionBuffer(Block *block);
	void removeFromTransactionBuffer(Block* block);
	
	// Internal BlockChain saved by every FullService.
	BlockChain* blockChain;
	//saves new block in blovkvhain
	void saveInBlockchain(Block *block);
	bool isGenesis(Block *block);
};

