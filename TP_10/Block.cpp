#include "Block.h"
#include <ctime>
#include <string>
#include <sstream>



Block::Block(vector<Transaction*> transactionsList_, Block & previousBlock_): transactionsList(transactionsList_)
{
	setPreviousHash(previousBlock_);
	transactionsAmount = transactionsList_.size();

	timestamp = time(NULL);								// Gets time in seconds since epoch.
}

Block::Block(vector<Transaction*> transactionsList_, string previousBlockHash_): transactionsList(transactionsList_)
{
	setPreviousHash(previousBlockHash_);
	transactionsAmount = transactionsList_.size();

	timestamp = time(NULL);								// Gets time in seconds since epoch.
}

Block::Block()
{
}


Block::~Block()
{
}

string Block::hashBlock()
{
	string toHash;
	toHash = getBlockString();

	SHA256 hasher;
	StringSource s(toHash, true, new HashFilter(hasher, new HexEncoder(new StringSink(thisHash))));		// Saves result in internal variable thisHash.
}

void Block::updateTime()
{
	timestamp = time(NULL);
}

void Block::setNounce(uint32_t nounce_)
{
	nounce = nounce_;
}

void Block::addTransaction(Transaction * transaction_)
{
	transactionsList.push_back(transaction_);
}

void Block::setTransactionList(vector<Transaction*> transactionList_)
{
	transactionsList = transactionList_;
}

void Block::setPreviousHash(Block & previousBlock_)
{
	previousHash = previousBlock_.getPreviousHash();
}

void Block::setPreviousHash(string previousBlockHash_)
{
	previousHash = previousBlockHash_;
}

string Block::getPreviousHash()
{
	return previousHash;
}

string Block::getBlockString()
{
	string blockString = previousHash;				// previousHash already a string.

	stringstream timeParser;
	timeParser << timestamp;
	blockString += timeParser.str();				// Making a string out of time.

	blockString += to_string(nounce);				
	blockString += to_string(transactionsAmount);	// Adding nounce and transactionAmount as string.

	for (auto transaction : transactionsList)
	{
		blockString += transaction->getTransactionString();
	}

	return blockString;
}

string Block::getHash()
{
	return thisHash;
}
