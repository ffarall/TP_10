#pragma once
#include <cstdint>
#include <vector>
#include <ctime>

#include "Transaction.h"
#include "Block.h"

#include "sha3.h"

using namespace std;

class Block
{
public:
	Block(vector<Transaction*> transactionsList_, Block previousBlock);
	Block();
	~Block();

	// Hashes the block, modifies the thisHash field and returns the hash.
	SHA256 hashBlock();
	// Updates timestamp.
	void updateTime();
	// Changes nounce.
	void setNounce(uint32_t nounce_);

private:
	// Hash of this block.
	SHA256 thisHash;
	// Hash of previous block.
	SHA256 previousHash;
	// Time-stamp of the block up to seconds, since epoch.
	time_t timestamp;
	// This is what the miners change in order to mine;
	uint32_t nounce;
	// Amount of transactions in block.
	size_t transactionsAmount;
	// List of transactions in the block.
	vector<Transaction> transactionsList;
};

