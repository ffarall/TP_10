#pragma once
#include <vector>

#include "Receipt.h"

#include "sha3.h"

class Transaction
{
public:
	Transaction();
	~Transaction();

private:
	// Hash of the transaction;
	SHA256 hash;
	// Inputs of the transaction.
	vector<Receipt*> inputs;
	// Input counter.
	uint16_t inputsCount;
	// Outputs of the transaction.
	vector<Receipt*> outputs;
	// Output counter.
	uint16_t outputsCount;
	// Total amount of coins available for transaction.
	uint32_t totalCoins;
};

