#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

vector<byte> Input::getUnlockingScript()
{
	return unlockingScript;
}

void Input::sign(vector<byte> signature_)
{
	unlockingScript = signature_;
}
