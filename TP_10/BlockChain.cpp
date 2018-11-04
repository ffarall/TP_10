#include "BlockChain.h"



BlockChain::BlockChain()
{
}


BlockChain::~BlockChain()
{
}

void BlockChain::addBlock(Block* newBlock_)
{
	blockChain.push_back(newBlock_);
}

Block BlockChain::peekBlock(int position)
{
	return *blockChain[blockChain.size() - position];
}

Block BlockChain::peekBlock(string hash)
{
	for (auto block : blockChain)
	{
		if (block->getHash() == hash)
		{
			return *block;
		}
	}
}

size_t BlockChain::getBlockChainSize()
{
	return blockChainSize;
}
