#include "GridEventBlock.h"



GridEventBlock::GridEventBlock()
{
}


GridEventBlock::~GridEventBlock()
{
}

Block * GridEventBlock::getNewBlock()
{
	return &newBlock;
}

void GridEventBlock::setNewBlock(Block * newBlock_)
{
	newBlock = *newBlock_;
}
