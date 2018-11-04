#pragma once

#include "BlockChain.h"
#include "Block.h"
#include "Transaction.h"
#include "Node.h"



enum class GridEventType { NEW_BLOCK_MINED, NEW_TRANSACTION, GET_BLOCKCHAIN, ASK_FOR_BLOCKCHAIN };

// There can be 4 types of GridEvents, when a block was mined, when a transaction is made, 
// when information is asked for (consulting BlockChain), and when information is responded.
class GridEvent
{
public:
	GridEvent();
	//copy constructor
	GridEvent(const GridEvent& event_);
	virtual ~GridEvent();

	void setType(GridEventType type_);
	void setEmisor(Node * emisor_);
	void setNewBlock(Block& block_);
	void setNewTransaction(Transaction& transaction_);
	void setNewBlockChain(BlockChain& blockChain);

	GridEventType getType();
	Node* getEmisor();

protected:
	// Type of the event.
	GridEventType type;
	// Pointer to emitting node.
	Node * emisor;
};

