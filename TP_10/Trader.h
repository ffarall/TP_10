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

	// This is what you call when this node is given time to act. Non-blocking, just one cycle.
	virtual bool runCycle();
	// Sends a Transaction type GridEvent.
	bool emitTransaction(Node& fromNode, vector<Node&> toNodes, vector<double> amountsTransfered);
	// Returns the UTXOs of this Trader.
	vector<Output*> getUTXOs();

	// Returns true if this is a miner.
	bool isMiner();

protected:
	//Process and validate recieved GridEvent from queue. Miner,Full Service and Partial service must do their own implementation
	virtual bool processEvent(GridEvent* gridEvent) = 0;
	// Sends a GridEvent asking for information.
	virtual bool consultBalance();
	// A simple Trader will return that he couldn't get that information, because it's not a FullService.
	bool respondBalanceConsulted();

	// Trader's Public Key.
	ECDSA<ECP, SHA256>::PublicKey publicKey;
	// Trader's Private Key.
	ECDSA<ECP, SHA256>::PrivateKey privateKey;
	// Trader's signature.
	vector<byte> signature;
	// It's the all of the UTXOs referred to this Trader.
	vector<Output*> UTXOs;
	// True if this is a miner, false otherwise.
	bool isMiner;
};

