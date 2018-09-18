#pragma once
#include<cstdio>
#include"Define.h"
class FileOperator
{
public:
	FileOperator();
	~FileOperator();

	void Create(const char *filename);
	int Open(const char * filename);
	void Close();

	void MoveBlock(int blocknumber);
	void MovePoint(int pointlocation);

	void Read(void *buffer, int size);
	void Write(void *buffer, int size);

	void CreatFile(const char * filename);
	int OpenFile(const char * filename);
	void CloseFile();

	void ReadFile(void *buffer, int size);
	void WriteFile(void *buffer, int size);

	int FileSize();

	void Flush();


	FILE *minifs;
	FILE *file;

	int MinifsPointLocation;//Minifs指针位置
	int FilePointLocation;//打开文件指针位置
};

