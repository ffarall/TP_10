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
}


FullService::~FullService()
{
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

bool FullService::validateTransaction(Transaction& transactionToValidate)
{
	for (auto input : transactionToValidate.getInputs())												// Every input in the transaction has to be validated.
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

uint32_t FullService::consultBalance()
{
	
}
