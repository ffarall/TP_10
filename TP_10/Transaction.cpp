#include "Transaction.h"


/*************************  AUXILIARY FUNCTIONS  *****************************/
ECDSA<ECP, SHA256>::PrivateKey generatePrivKey()
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::PrivateKey privateKey;
	privateKey.Initialize(autoSeededRandomPool, ASN1::secp160r1());
	bool result = privateKey.Validate(autoSeededRandomPool, 3);
	if (!result)
		cout << "private key is not valid!";
	return privateKey;
}

vector<byte> getSignature(ECDSA<ECP, SHA256>::PrivateKey &privKey, string &data)
{
	AutoSeededRandomPool autoSeededRandomPool;
	ECDSA<ECP, SHA256>::Signer signer(privKey); //Creamos el signador
	bool result = signer.AccessKey().Validate(autoSeededRandomPool, 3);
	if (!result)
		cout << "failed to create signer" << result;
	size_t siglen = signer.MaxSignatureLength();
	vector<byte> signature(siglen, 0x00); //Aqui guardaremos la signature
	siglen = signer.SignMessage(autoSeededRandomPool, (const byte*)data.data(), data.size(), (byte*)signature.data());
	return signature;
}

bool verifySignature(ECDSA<ECP, SHA256>::PublicKey &pubKey, string &data, vector<byte> &signature)
{
	ECDSA<ECP, SHA256>::Verifier verifier(pubKey);
	return  verifier.VerifyMessage((const byte*)data.data(), data.size(), (const byte*)signature.data(), signature.size());
}

/******************************************************************************/

Transaction::Transaction() : inputs(), outputs()
{
	inputsCount = 0;
	outputsCount = 0;
	timestamp = time(NULL);								// Gets time in seconds since epoch.

	hashTransaction();
}

Transaction::Transaction(vector<Input*> inputs_, vector<Output*> outputs_) : inputs(inputs_), outputs(outputs_)
{
	inputsCount = inputs_.size();
	outputsCount = outputs_.size();
	timestamp = time(NULL);								// Gets time in seconds since epoch.

	hashTransaction();
}


Transaction::~Transaction()
{
}

string Transaction::getHash()
{
	return hash;
}

vector<Output*> Transaction::getOutputs()
{
	return outputs;
}

vector<Input*> Transaction::getInputs()
{
	return inputs;
}

string Transaction::getTransactionString()
{
	string transactionString;
	transactionString += to_string(inputsCount) + to_string(outputsCount);
	for (auto input : inputs)
	{
		transactionString += input->inputToString();
	}
	for (auto output : outputs)
	{
		transactionString += output->outputToString();
	}
	
	return transactionString;
}

void Transaction::setInputs(vector<Input*> inputs_)
{
	inputs = inputs_;
}

void Transaction::addInput(Input * input_)
{
	inputs.push_back(input_);
}

void Transaction::setOutputs(vector<Output*> outputs_)
{
	outputs = outputs_;
}

void Transaction::addOutput(Output * output_)
{
	outputs.push_back(output_);
}

void Transaction::updateData()
{
	timestamp = time(NULL);
	inputsCount = inputs.size();
	outputsCount = outputs.size();
	hashTransaction();
}

bool Transaction::verifyInput(int outputIndex, vector<byte>& signature)
{
	ECDSA<ECP, SHA256>::PublicKey pubKey = outputs[outputIndex]->getLockingScript();
	string data = outputs[outputIndex]->outputToString();
	return verifySignature(pubKey, data, signature);
}

void Transaction::hashTransaction()
{
	string toHash;
	toHash = getTransactionString();																							// Creating a string of all the data contained in the transaction to be hashed.

	SHA256 hasher;
	StringSource s(toHash, true, new HashFilter(hasher, new HexEncoder(new StringSink(hash))));		// Saves result in internal variable hash.
}

void Transaction::setOutputs(vector<Output*> outputs_)
{
	outputs = outputs_;
