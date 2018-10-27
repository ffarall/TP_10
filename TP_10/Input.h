#pragma once
#include "Output.h"

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"

using namespace std;
using namespace CryptoPP;

class Input
{
public:
	Input();
	Input(string hash, size_t index, vector<byte> signature_);
	~Input();

	vector<byte> getUnlockingScript();
	string getOutputTransactionHash();
	size_t getOutputIndex();

	// Sets unlockingScript.
	void sign(vector<byte> signature_);
	void setOutputTransactionHash(string hash);
	void setOutputIndex(size_t index);

private:
	// Hash of the transaction containing the UTXO referenced.
	string outputTransactionHash;
	// Index of the UTXO in the transaction list of outputs.
	size_t outputIndex;
	// To be applied to the security algorithm of signature and unlock the Output.
	vector<byte> unlockingScript;
};

