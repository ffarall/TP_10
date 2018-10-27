#pragma once
#include "Output.h"

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"

using namespace CryptoPP;

class Input
{
public:
	Input();
	~Input();

private:
	// Referenced Output.
	Output * UTXO;
	// To be applied to the security algorithm of signature and unlock the Output.
	ECDSA<ECP, SHA256>::PublicKey unlockingScript;
};

