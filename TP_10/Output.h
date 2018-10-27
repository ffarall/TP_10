#pragma once
#include "Trader.h"

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"

using namespace CryptoPP;

// Contains a name and an amount of coins. Serves as input or output of a Transaction.
class Output
{
public:
	Output();
	~Output();

private:
	// Public Key of the owner of the amount of coins.
	ECDSA<ECP, SHA256>::PublicKey lockingScript;
	// Amount of coins attributed to the owner.
	uint32_t coins;
};

