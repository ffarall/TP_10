#pragma once
#include "GridEvent.h"
class GridEventTransaction :
	public GridEvent
{
public:
	GridEventTransaction();
	virtual ~GridEventTransaction();
	Transaction* getNewTransaction();
	void setNewTransaction(Transaction * newTransaction_);

protected:
	// Event content if it is NEW_TRANSACTION.
	Transaction newTransaction;
};

