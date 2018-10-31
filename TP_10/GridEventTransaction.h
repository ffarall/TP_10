#pragma once
#include "GridEvent.h"
class GridEventTransaction :
	public GridEvent
{
public:
	GridEventTransaction();
	virtual ~GridEventTransaction();

protected:
	// Event content if it is NEW_TRANSACTION.
	Transaction newTransaction;
};

