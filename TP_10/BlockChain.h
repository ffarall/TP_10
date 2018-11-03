#pragma once
#include <vector>
#include "Block.h"

using namespace std;

class BlockChain
{
public:
	BlockChain();
	~BlockChain();

	// Adds a Block to the top of the blockChain.
	void addBlock(Block* newBlock_);
	// Returns the Block in the given position, relative to the top, where position = 0 is the block at the top.
	Block peekBlock(int position);
	// Returns the Block with that hash.
	Block peekBlock(string hash);

private:
	// Actual space in memory where the blockchain is saved.
	vector<Block*> blockChain;
	// Size of the blockchain in amount of blocks.
	size_t blockChainSize;
};

