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

	char state;//�ļ�״̬
	char name[8];//�ļ���
	char extension[3];//��չ��

	int location;//�������
	int size;//�ļ���С
	int parent;//���׽ڵ���

	int date;//�޸�����
	int time;//�޸�ʱ��
};

