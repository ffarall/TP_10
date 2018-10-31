#include "Miner.h"
#include<random>

#define MAX_32 4294967296

Miner::Miner()
{
	isMiner = true; //es minero
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
}


Miner::~Miner()
{
}

bool Miner::runCycle()
{
	while (!infoPackages.empty())
	{
		processEvent(&infoPackages.front());
		infoPackages.pop();
	}
	if (needNewBlock)
	{
		if (refreshCurrentBlock())
		{
			//genesis again
			//vaciar la lista de tried nounces!
		}
	}
	mine();
	
}

bool Miner::processEvent(GridEvent * gridEvent)
{
	switch (gridEvent->getType())
	{
	case GridEventType::NEW_BLOCK_MINED:
		//buscar en current block
		//buscar en trasaction buffer
		//si no esta en ninguno -> inputs vacio? -si-> output suma 20? -si-> valido! agrego a blockchain
		//								no->	invalido!	<-no
		//setear el bool de refresh si es necesario
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

bool Miner::challengeHash(std::string hash) // el challenge es obtener 0 en las primeras posiciones del hash, definido por la constante ZERO_IN_HASH
{
	for(int i = 0, i<ZERO_IN_HASH)
	return false;
}
