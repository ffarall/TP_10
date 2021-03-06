#pragma once
#include "Node.h"
#include "Transaction.h"
#include "GridEvent.h"
#include "Output.h"

#include "cryptlib.h"
#include "osrng.h"
#include "eccrypto.h"

#include <vector>

using namespace std;
using namespace CryptoPP;

class Trader :
	public Node
{
public:
	Trader();
	virtual ~Trader();
	virtual uint32_t consultBalance() = 0;
	// This is what you call when this node is given time to act. Non-blocking, just one cycle.
	virtual bool runCycle() = 0;
	// Consult trader's balance.
	virtual uint32_t consultBlance() = 0;
	// Sends a Transaction type GridEvent.
	void emitTransaction(Trader* fromNode, vector<Trader*> toNodes, vector<uint32_t> amountsTransfered);
	// Returns the UTXOs of this Trader.
	vector<Output*> getUTXOs();
	// Returns publicKey.
	ECDSA<ECP, SHA256>::PublicKey getPublicKey();

	// Returns true if this is a miner.
	bool isMiner();

protected:
	//Process and validate received GridEvent from queue. Miner,Full Service and Partial service must do their own implementation
	virtual bool processEvent(GridEvent* gridEvent) = 0;
	// A simple Trader will return that he couldn't get that information, because it's not a FullService.
	bool respondBalanceConsulted();
	// Gets a list of UTXOs that sum the same or more of the needed amount to transfer. Returns the sum.
	virtual uint32_t getNeededUTXOs(vector<Input*> * neededUTXOs, uint32_t neededAmount) = 0;

	// Trader's Public Key.
	ECDSA<ECP, SHA256>::PublicKey publicKey;
	// Trader's Private Key.
	ECDSA<ECP, SHA256>::PrivateKey privateKey;
	// Trader's signature.
	vector<byte> signature;
	// It's the all of the UTXOs referred to this Trader.
	vector<Output*> UTXOs;
	// True if this is a miner, false otherwise.
	bool isItMiner;
};

