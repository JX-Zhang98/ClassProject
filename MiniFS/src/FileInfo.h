#pragma once
#include "Time.h"
#include <cstdio>
class FileInfo
{
public:
	FileInfo();
	FileInfo(char state, const char *name, const char *extension, int location, int size, int parent);
	~FileInfo();
	void ShowName();
	void ShowExtension();

	char state;//文件状态
	char name[8];//文件名
	char extension[3];//扩展名

	int location;//索引编号
	int size;//文件大小
	int parent;//父亲节点编号

	int date;//修改日期
	int time;//修改时间
};

