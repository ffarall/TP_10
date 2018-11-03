#include "FullService.h"



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

bool FullService::validateTransaction()
{
	return false;
}

bool FullService::validateBlock()
{
	return false;
}

bool FullService::consultBalance()
{
	return false;
}
