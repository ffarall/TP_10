#pragma once
#include <vector>
#include <ctime>

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
	// Creates a string from all the data in the transaction (a string to hash).
	string getTransactionString();

	void setInputs(vector<Input*> inputs_);
	void addInput(Input* input_);
	void setOutputs(vector<Output*> outputs_);
	void addOutput(Output* output_);
	void updateData();

	// To be used by nodes when validating a transaction. Verifies a given input.
	bool verifyInput(int outputIndex, vector<byte>& signature);

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
	// Timestamp to make the transaction unique.
	time_t timestamp;
};

