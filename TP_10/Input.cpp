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

string Input::inputToString()
{
	string inputString;
	CryptoPP::HexEncoder encoder;

	encoder.Attach(new CryptoPP::StringSink(inputString));
	encoder.Put(unlockingScript.data(), unlockingScript.size());
	encoder.MessageEnd();

	return inputString;
}
