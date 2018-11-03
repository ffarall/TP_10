#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Transaction.h"
#include "Block.h"

#include "sha3.h"


using namespace std;

class Block
{
public:
	Block(vector<Transaction*> transactionsList_, Block& previousBlock_);
	Block(vector<Transaction*> transactionsList_, string previousBlockHash_);
	Block();
	~Block();

	// Hashes the block, modifies the thisHash field and returns the hash.
	string hashBlock();
	// Updates timestamp.
	void updateTime();
	// Changes nounce.
	void setNounce(uint32_t nounce_);

	// Adds transaction to block.
	void addTransaction(Transaction* transaction_);
	// Sets transactionList.
	void setTransactionList(vector<Transaction*> transactionList_);
	// Sets previousHash.
	void setPreviousHash(Block& previousBlock_);
	// Sets previousHash.
	void setPreviousHash(string previousBlockHash_);
	// Returns previous block's hash.
	string getPreviousHash();
	// Creates a string from all the data in the block (a string to hash).
	string getBlockString();
	// Returns block's hash.
	string getHash();


private:
	// Hash of this block.
	string thisHash;
	// Hash of previous block.
	string previousHash;
	// Time-stamp of the block up to seconds, since epoch.
	time_t timestamp;
	// This is what the miners change in order to mine;
	uint32_t nounce;
	// Amount of transactions in block.
	size_t transactionsCount;
	// List of transactions in the block.
	vector<Transaction*> transactionsList;
};

