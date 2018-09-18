#pragma once

#include <vector>
#include <list>
#include <cstring>
#include <string>
#include <iostream>
#include "FileInfo.h"
#include "Define.h"
#include "Time.h"
#include "color.h"
using namespace std;

class Directory
{
public:
	Directory();
	~Directory();

	FileInfo File[BLOCKNUMBER];//Ŀ¼��Ϣ
	int FileNumber;//Ŀ¼����
	struct Node
	{
		char state;//״̬
		int parent;//���ڵ���
		list<int> child;//�ӽڵ�����
	};
	vector<Node> Tree;//Ŀ¼����Ϣ

	static FileInfo Root();
	void BuildTree();
	int FindEmpty();
	void Push(int number);
	void Change(int number, FileInfo);
	int Search(char*, char*, int);
	int Add(FileInfo);
	void Move(int, int);
	void Delete(int number);
	int CountUnderDir(int number);
	void ShowDir(int);
	void ShowTree(int);
	void ShowPath(int);
	void ShowAtt(int);
	
private:
	bool vislst[270000] = {0};

	bool namecompare(const char *str1, const char *str2, int style);
	void recursionSearch(int now, int depth);
	void printSpace(int depth);
	void showWholeName(int now);
	//void recursionDelete(int);

};

