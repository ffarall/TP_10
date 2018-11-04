#pragma once
#include "Trader.h"

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"
#include "oids.h"
#include "hex.h"
#include "sha3.h"

using namespace CryptoPP;
using namespace std;

// Contains a name and an amount of coins. Serves as input or output of a Transaction.
class Output
{
public:
	Output(uint32_t coins_, ECDSA<ECP, SHA256>::PublicKey lockingScript_);
	Output();
	~Output();

	uint32_t getCoins();
	ECDSA<ECP, SHA256>::PublicKey getLockingScript();

	void setCoins(uint32_t coins_);
	void setLockingScript(ECDSA<ECP, SHA256>::PublicKey lockingScript_);
	void setIsUTXO(bool value);

	// Creates string of all the Input data.
	string outputToString();
	// Check if output is used.
	bool isUsed();

private:
	// Public Key of the owner of the amount of coins.
	ECDSA<ECP, SHA256>::PublicKey lockingScript;
	// Amount of coins attributed to the owner.
	uint32_t coins;
	// Determines if the output is already used or not.
	bool isUTXO;
};

