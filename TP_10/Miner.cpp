#include "Miner.h"
#include<random>
#include"GridEventBlock.h"
#include"GridEventBlockChain.h"
#include"GridEventTransaction.h"

#define MAX_32 4294967296
#define ZERO_IN_HASH 4
Miner::Miner()
{
	isItMiner = true; //es minero
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	needNewBlock = true;
}


Miner::~Miner()
{
}

bool Miner::runCycle()
{
	
	while (!infoPackages.empty())
	{
		if (!processEvent(&infoPackages.front()))
		{
			return false;//si hubo un error procesando el evento, salgo y aviso
		}
		infoPackages.pop();
	}
	if (needNewBlock)
	{
		refreshCurrentBlock();
		clearTriedNounces();//vaciar la lista de tried nounces!
		
	}
	mine();
	return true;//si llego hasta aca estuvo todo bien
}

uint32_t Miner::consultBalance()
{
	uint32_t balance = 0;

	balance += consultBalanceInBuffer();
	balance += consultBalanceInBlockChain();
	balance += consultBalanceInCurrentBlock();

	return balance;
}

bool Miner::processEvent(GridEvent * gridEvent)
{
	switch (gridEvent->getType())
	{
	case GridEventType::NEW_BLOCK_MINED:
		GridEventBlock *minedBlockEvent = (GridEventBlock*)gridEvent;
		if (isInCurrentBlock())//buscar en current block
		{
			removeFromCurrentBlock();
			needNewBlock = true;
		}
		else if (isInTransactionBuffer())//buscar en trasaction buffer
		{
			removeFromTransactionBuffer();
		}
		else if ()//si no esta en ninguno -> inputs vacio? -si-> output suma 20? -si-> valido! agrego a blockchain
		{					//								no->	invalido!	<-no
		}
		else
		{
			return false;
		}
		
		
		
		//setear el bool de refresh si es necesario
		break;
	case GridEventType::NEW_TRANSACTION:
		GridEventTransaction* transactionEvent = (GridEventTransaction*)gridEvent;
		if (validateTransaction((transactionEvent)))//si es valida agrego en transaction buffer
		{

		}
		else
		{
			return false;//si no es valida -> error
		}

		
		break;
	case GridEventType::GET_BLOCKCHAIN:
		//copiar blockchain recibida a la mia
		break;
	case GridEventType::ASK_FOR_BLOCKCHAIN:
		GridEventBlockChain* toSend = new GridEventBlockChain();//crear un grid event y mandarselo al nodo que me lo pide
		Trader* receiver = (Trader*)gridEvent->getEmisor();
		break;
	default:
		return false;//error
		break;
	}
	return true ;//si llego hasta aca esta todo bien
}

bool Miner::mine()
{
	uint32_t max = MAX_32;
	uniform_int_distribution<uint32_t> randomNumber(0,MAX_32); 
	uint32_t obtainedNumber;
	do
	{
		obtainedNumber = randomNumber(max);  //mientras que siga sacando numeros que ya haya probado sigo sacando
	} while (wasTried(obtainedNumber));
	currentBlock.setNounce(obtainedNumber);
	std::string hash = currentBlock.hashBlock(); //hasheo el bloque y obtengo el hash OJO!!!!! VER QUE PASA CON LOS ERRORES ACA
	if (challengeHash(hash))//comparar el hash con el challenge 
	{
		//guardar en blockchain
		//emitir el evento de bloque minado
	}
	return false;
}

uint32_t Miner::consultBalanceInCurrentBlock()
{
	uint32_t balanceInCurrentBlock = 0;

	for (auto transaction : currentBlock.getTransactionsList())								// For every transaction in currentBlock.
	{
		for (auto output : transaction->getOutputs())										// For every output in the transaction.
		{
			ECDSA<ECP, SHA256>::PublicKey outputPublicKey = output->getLockingScript();
			if (outputPublicKey == publicKey)												// If the public key of the output is this trader's public key...
			{
				balanceInCurrentBlock += output->getCoins();								// Adds to the balance.
			}
		}
	}

	return balanceInCurrentBlock;
}

void Miner::refreshCurrentBlock()
{
	string previousHash = blockChain->peekBlock(0).getHash();				// Retrieving hash from last block in blockChain.
	currentBlock.setPreviousHash(previousHash);

	currentBlock.updateTime();

	currentBlock.setTransactionList(transactionsBuffer);
	transactionsBuffer.clear();

	currentBlock.updateTransactionsCount();
}

bool Miner::wasTried(uint32_t number)
{
	bool error = false;
	for (vector<uint32_t>::iterator it = triedNounces.begin(); it != triedNounces.end() && !error; it++)
	{
		if (*it == number)
		{
			error = true;
		}
	}
	return error;
}

bool Miner::challengeHash(std::string hash) // el challenge es obtener 0 en las primeras posiciones del hash, definido por la constante ZERO_IN_HASH
{
	bool error = false;
	for (int i = 0; i < ZERO_IN_HASH && !error;i++)
	{
		if (hash[i] != '0')
		{
			error = true;
		}
	}
	return error ? false : true;
}

void Miner::clearTriedNounces()
{
	triedNounces.clear();
}
