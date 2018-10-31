#include "Miner.h"



Miner::Miner()
{
	isMiner = true; //es minero
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
	return false;//alco coherente con lo que haya qeu devolver
}

bool Miner::mine()
{
	return false;
}
