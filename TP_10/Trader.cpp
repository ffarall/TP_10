#include "Trader.h"
#include "GridEventTransaction.h"


Trader::Trader()
{
}


Trader::~Trader()
{
}

void Trader::emitTransaction(Trader * fromNode, vector<Trader*> toNodes, vector<uint32_t> amountsTransfered)
{
	GridEventTransaction newTransaction;
	newTransaction.setEmisor(this);
	newTransaction.setType(GridEventType::NEW_TRANSACTION);

	uint32_t totalAmount = 0;
	for (auto amount : amountsTransfered)
	{
		totalAmount += amount;
	}

	vector<Input*> neededUTXOs;
	uint32_t amountFromUTXOs = getNeededUTXOs(&neededUTXOs, totalAmount);
	newTransaction.getNewTransaction()->setInputs(neededUTXOs);

	for (int i = 0; i < toNodes.size(); i++)
	{
		Output output(amountsTransfered[i], toNodes[i]->getPublicKey());
		newTransaction.getNewTransaction()->addOutput(&output);
	}
	Output output(amountFromUTXOs - totalAmount, publicKey);
	newTransaction.getNewTransaction()->addOutput(&output);

	newTransaction.getNewTransaction()->updateData();

	sendInformation(newTransaction);
}

vector<Output*> Trader::getUTXOs()
{
	return UTXOs;
}

ECDSA<ECP, SHA256>::PublicKey Trader::getPublicKey()
{
	return publicKey;
}

bool Trader::isMiner()
{
	return isItMiner;
}

