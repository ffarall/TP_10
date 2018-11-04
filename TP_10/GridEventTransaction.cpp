#include "GridEventTransaction.h"



GridEventTransaction::GridEventTransaction()
{
}


GridEventTransaction::~GridEventTransaction()
{
}

Transaction * GridEventTransaction::getNewTransaction()
{
	return &newTransaction;
}

void GridEventTransaction::setNewTransaction(Transaction * newTransaction_)
{
	newTransaction = *newTransaction_;
}
