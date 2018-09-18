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


	bool state;//�ռ�״̬����ʼ��Ϊ1��δ��ʼ��Ϊ0
	FileOperator *fileOperator;//�ļ�����
	Index *index;//����
	Directory *directory;//Ŀ¼
	int emptyBlockNumber;//���п�ĸ���
private:
	int GetDirNum(const char * filename);
	int splitName(char *name, char * extension, char *filename);	//�ָ��ļ�������չ��
	void setNowPath(int now);
	void splitSlash(char*wholename,char*path);//�ָ�·������ȡ�����ļ���
	int getParentNumber(char * path);

	string nowPath;
	int nowDirNum;
};

