#pragma once
#include <vector>

#include "Output.h"
#include "Input.h"

using namespace std;
using namespace CryptoPP;

class Transaction
{
public:
	Transaction();
	Transaction(vector<Input*> inputs_, vector<Output*> outputs_);
	~Transaction();

	string getHash();
	vector<Output*> getOutputs();
	vector<Input*> getInputs();

	void setInputs(vector<Input*> inputs_);
	void setOutputs(vector<Output*> outputs_);

private:
	// Hashes the transaction.
	void hashTransaction();

	// Hash of the transaction;
	string hash;
	// Inputs of the transaction.
	vector<Input*> inputs;
	// Input counter.
	size_t inputsCount;
	// Outputs of the transaction.
	vector<Output*> outputs;
	// Output counter.
	size_t outputsCount;
};

