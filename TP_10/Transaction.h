#pragma once
#include <vector>

#include "Output.h"
#include "Input.h"

#include "sha3.h"

class Transaction
{
public:
	Transaction();
	Transaction(vector<Input*> inputs_, vector<Output*> outputs_);
	~Transaction();

	SHA256 getHash();
	vector<Output*> getOutputs();

	void setInputs(vector<Input*> inputs_);
	void setOutputs(vector<Output*> outputs_);

private:
	// Hash of the transaction;
	SHA256 hash;
	// Inputs of the transaction.
	vector<Input*> inputs;
	// Input counter.
	uint16_t inputsCount;
	// Outputs of the transaction.
	vector<Output*> outputs;
	// Output counter.
	uint16_t outputsCount;
	// Total amount of coins available for transaction.
	uint32_t totalCoins;
};

