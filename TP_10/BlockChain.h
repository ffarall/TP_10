#pragma once
#include <stack>
#include "Block.h"

using namespace std;

class BlockChain
{
public:
	BlockChain();
	~BlockChain();

	// Adds a Block to the top of the blockChain.
	bool addBlock();
	// Deletes all Blocks from top to position.
	bool deleteBlock(int position);
	// Returns the information of the Block in the given position, relative to the top.
	Block peekBlock(int position);

private:
	// Actual space in memory where the blockchain is saved.
	stack<Block> blockChain;
	// Size of the blockchain in amount of blocks.
	size_t blockChainSize;
};

