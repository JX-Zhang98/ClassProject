#include "Index.h"


Index::Index()
{
	NowBlockLocation = 0;
}

Index::~Index()
{

}

void Index::CountFreeBlockNumber()
{
	FreeBlockNumber = 0;
	for (int i = 1; i < BLOCKNUMBER; i++)
	{
		if (Array[i] == 0) FreeBlockNumber++;
	}
}

int Index::FindEmptyBlock()
{
	if (NowBlockLocation == BLOCKNUMBER)
	{
		for (int i = 1; i < BLOCKNUMBER; i++)
		{
			if (Array[i] == 0)
			{
				NowBlockLocation = i;
				return i;
			}
		}
		return -1;
	}
	else
	{
		for (int i = NowBlockLocation; i < BLOCKNUMBER; i++)
		{
			if (Array[i] == 0)
			{
				NowBlockLocation = i;
				return i;
			}
		}
		NowBlockLocation = BLOCKNUMBER;
		return FindEmptyBlock();
	}
}
