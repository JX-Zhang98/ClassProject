#pragma once
#include"Define.h"
class Index
{
public:
	Index();
	~Index();

	int Array[BLOCKNUMBER];
	int FreeBlockNumber;
	int NowBlockLocation;

	int *ModificationIndexList;//修改列表
	int ModificationIndexNumber;//修改列表个数

	int FindEmptyBlock();
	void CountFreeBlockNumber();
};
