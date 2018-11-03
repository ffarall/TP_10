#include "Input.h"



Input::Input()
{
}

Input::Input(string hash, size_t index, vector<byte> signature_)
{
	setOutputTransactionHash(hash);
	setOutputIndex(index);
	sign(signature_);
}


Input::~Input()
{
}

vector<byte> Input::getUnlockingScript()
{
	return unlockingScript;
}

string Input::getOutputTransactionHash()
{
	return outputTransactionHash;
}

size_t Input::getOutputIndex()
{
	return outputIndex;
}

void Input::sign(vector<byte> signature_)
{
	unlockingScript = signature_;
}

void Input::setOutputTransactionHash(string hash)
{
	outputTransactionHash = hash;
}

void Input::setOutputIndex(size_t index)
{
	outputIndex = index;
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
