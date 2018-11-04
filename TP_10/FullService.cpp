#include "FullService.h"

#include "osrng.h"
#include "eccrypto.h"
#include "oids.h"
#include "hex.h"
#include "sha3.h"

using namespace CryptoPP;

FullService::FullService()
{
	isItMiner = false;//como no es minero entonces es full service
	blockChain = new BlockChain();
}


FullService::~FullService()
{
	delete blockChain;
}

bool FullService::runCycle()
{
	while (!infoPackages.empty())
	{
		if (!processEvent(&infoPackages.front()))
		{
			return false;//si hubo un error procesando el evento, salgo y aviso
		}
		infoPackages.pop();
		return true;//si llego hasta aca estuvo todo bien
	}
}

bool FullService::processEvent(GridEvent * gridEvent)
{
	switch (gridEvent->getType())
	{
	case GridEventType::NEW_BLOCK_MINED:
		//buscar en trasaction buffer
		//si no esta en ninguno -> inputs vacio? -si-> output suma 20? -si-> valido! agrego a blockchain
		//								no->	invalido!	<-no
		
		break;
	case GridEventType::NEW_TRANSACTION:
		//si es valida agrego en transaction buffer
		//si no es valida -> error
		break;
	case GridEventType::GET_BLOCKCHAIN:
		//crear un grid event y mandarselo al nodo que me lo pide
		break;
	default:
		//error?
		break;
	}
	return false;//algo coherente con lo que haya qeu devolver
	
}

bool FullService::respondBalanceConsulted()
{
	return false;
}

bool FullService::validateTransaction(Transaction * transactionToValidate)
{
	for (auto input : transactionToValidate->getInputs())												// Every input in the transaction has to be validated.
	{																									// Every input refers to a transaction by its hash, where there's an UTXO.
		for (int i = 0; i < blockChain->getBlockChainSize(); i++)										// Looking for the transaction in the blockhain block by block.
		{
			Block blockToSearch = blockChain->peekBlock(i);
			Transaction * searchedTransaction = blockToSearch.getTransaction(input->getOutputTransactionHash());
			if (searchedTransaction != nullptr)															// Checking if the transaction that the input refers to is in this block.
			{
				int outputIndex = input->getOutputIndex();
				vector<byte> signature = input->getUnlockingScript();
				
				if (!searchedTransaction->verifyInput(outputIndex, signature))							// If signature is not verified, validation returns false.
				{
					return false;
				}
			}
		}
	}

	return true;																						// If all inputs are verified, returns true.
}

bool FullService::validateBlock()
{
	return false;
}

uint32_t FullService::consultBalanceInBuffer()
{
	uint32_t balanceInBuffer = 0;

	for (auto transaction : transactionsBuffer)														// For every transaction in transactionBuffer 
	{
		for (auto output : transaction->getOutputs())												// For every output in the transaction.
		{
			ECDSA<ECP, SHA256>::PublicKey outputPublicKey = output->getLockingScript();
			if (outputPublicKey == publicKey)														// If the public key of the output is this trader's public key...
			{
				balanceInBuffer += output->getCoins();												// Adds to the balance.
			}
		}
	}

	return balanceInBuffer;
}

uint32_t FullService::consultBalanceInBlockChain()
{
	uint32_t balanceInBlockChain = 0;

	for (int i = 0; i < blockChain->getBlockChainSize(); i++)										// For every block in the blockChain.
	{
		Block blockToConsult = blockChain->peekBlock(i);
		for (auto transaction : blockToConsult.getTransactionsList())								// For every transaction in the block.
		{
			for (auto output : transaction->getOutputs())											// For every output in the transaction.
			{
				ECDSA<ECP, SHA256>::PublicKey outputPublicKey = output->getLockingScript();
				if (outputPublicKey == publicKey)													// If the public key of the output is this trader's public key...
				{
					balanceInBlockChain += output->getCoins();										// Adds to the balance.
				}
			}
		}
	}

	return balanceInBlockChain;
}

uint32_t FullService::consultBalance()
{
	uint32_t balance = 0;

	balance += consultBalanceInBuffer();
	balance += consultBalanceInBlockChain();

	return balance;
}
