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

	int *ModificationIndexList;//�޸��б�
	int ModificationIndexNumber;//�޸��б����

	int FindEmptyBlock();
	void CountFreeBlockNumber();
};
