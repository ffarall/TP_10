#include "FullService.h"



FullService::FullService()
{
	isMiner = false;//como no es minero entonces es full service
}


FullService::~FullService()
{
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
