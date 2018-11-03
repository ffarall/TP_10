#include "Output.h"
#include <vector>
#include <cstdint>

#define PUBLIC_KEY_CHARS 40

Output::Output(uint32_t coins_, ECDSA<ECP, SHA256>::PublicKey lockingScript_)
{
	setCoins(coins_);
	setLockingScript(lockingScript_);
}

Output::Output()
{
}


Output::~Output()
{
}

uint32_t Output::getCoins()
{
	return coins;
}

ECDSA<ECP, SHA256>::PublicKey Output::getLockingScript()
{
	return lockingScript;
}

void Output::setCoins(uint32_t coins_)
{
	coins = coins_;
}

void Output::setLockingScript(ECDSA<ECP, SHA256>::PublicKey lockingScript_)
{
	lockingScript = lockingScript_;
}

string Output::outputToString()
{
	string outputString;
	CryptoPP::HexEncoder encoder;
	vector<byte> lockingScriptArray(PUBLIC_KEY_CHARS);

	vector<byte> aux(PUBLIC_KEY_CHARS / 2);
	const ECP::Point &point = lockingScript.GetPublicElement();
	point.x.Encode(aux.data(), point.x.ByteCount());
	lockingScriptArray.clear();
	lockingScriptArray.insert(lockingScriptArray.end(), aux.begin(), aux.end());
	point.y.Encode(aux.data(), point.y.ByteCount());
	lockingScriptArray.insert(lockingScriptArray.end(), aux.begin(), aux.end());

	encoder.Attach(new CryptoPP::StringSink(outputString));
	encoder.Put(lockingScriptArray.data(), lockingScriptArray.size());
	encoder.MessageEnd();

	return outputString;
}
