#include "FullService.h"

#include "osrng.h"
#include "eccrypto.h"
#include "oids.h"
#include "hex.h"
#include "sha3.h"
#include"GridEventBlock.h"
#include"GridEventBlockChain.h"
#include"GridEventTransaction.h"


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
		GridEventBlock *minedBlockEvent = (GridEventBlock*)gridEvent;
		 if (isInTransactionBuffer(minedBlockEvent->getNewBlock()))//buscar en trasaction buffer
		{
			removeFromTransactionBuffer(minedBlockEvent->getNewBlock());
			saveInBlockchain(minedBlockEvent->getNewBlock());
		}
		else if (isGenesis(minedBlockEvent->getNewBlock()))//si no esta en ninguno -> inputs vacio? -si-> output suma 20? -si-> valido! agrego a blockchain
		{
			saveInBlockchain(minedBlockEvent->getNewBlock());
		}
		else
		{
			return false;//								no->	invalido!	<-no
		}

		break;
	case GridEventType::NEW_TRANSACTION:
		GridEventTransaction* transactionEvent = (GridEventTransaction*)gridEvent;
		if (validateTransaction((transactionEvent->getNewTransaction())))//si es valida agrego en transaction buffer
		{
			transactionsBuffer.push_back(transactionEvent->getNewTransaction());
		}
		else
		{
			return false;//si no es valida -> error
		}


		break;
	case GridEventType::GET_BLOCKCHAIN:
		GridEventBlockChain* newBlockchain = (GridEventBlockChain*)gridEvent;//copiar blockchain recibida a la mia
		blockChain = newBlockchain->getNewBlockChain();
		break;
	case GridEventType::ASK_FOR_BLOCKCHAIN:
		GridEventBlockChain* toSend = new GridEventBlockChain();//crear un grid event y mandarselo al nodo que me lo pide
		toSend->setNewBlockChain(blockChain);
		Trader* receiver = (Trader*)gridEvent->getEmisor();
		receiver->receiveNewInformation(*toSend);
		delete toSend;
		break;
	default:
		return false;//error
		break;
	}
	return true;//si llego hasta aca esta todo bien
	
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
