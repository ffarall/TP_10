#pragma once

// There can be 4 types of GridEvents, when a block was mined, when a transaction is made, 
// when information is asked for (consulting BlockChain), and when information is responded.
class GridEvent
{
public:
	GridEvent();
	~GridEvent();
};

