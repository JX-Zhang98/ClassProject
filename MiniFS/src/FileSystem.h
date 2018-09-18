#pragma once

#include "FileOperator.h"
#include "Index.h"
#include "Directory.h"
#include <cstring>
#include <algorithm>
//#include "color.h"
class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	string GetPath();

	int Create(const char *filename = DEFAULTNAME);
	int Mount(const char *filename = DEFAULTNAME);
	int Format(const char*filename = DEFAULTNAME);
	int Copy(const char * original,const char * aim);
	int Delete(const char*);
	int recursionDelete(int number);
	int MakeDir(const char*);
	int Dir(const char*);
	int Attrib(const char*);
	int Tree(const char*);
	int Import(const char *filename,const char*path);
	void WriteIndex();
	int WriteData(char *buffer, int size, int location, int mode);
	int Export(const char * filename,const char*path);
	int ReadData(char * buffer, int size, int location, int mode);
	int CopyFile(int number, int aim);
	int CopyDir(int number, int aim);
	int recursionCopy(int number, int aim);
	int CDDir(char* aim);
	int Map(const char * path);
	int Move(const char * path, const char * aim);


	bool state;//空间状态，初始化为1，未初始化为0
	FileOperator *fileOperator;//文件操作
	Index *index;//索引
	Directory *directory;//目录
	int emptyBlockNumber;//空闲块的个数
private:
	int GetDirNum(const char * filename);
	int splitName(char *name, char * extension, char *filename);	//分割文件名和扩展名
	void setNowPath(int now);
	void splitSlash(char*wholename,char*path);//分割路径，获取整个文件名
	int getParentNumber(char * path);

	string nowPath;
	int nowDirNum;
};

