#pragma once
#include <string>
#include <vector>
#include <iostream>
//#include "color.h"
using namespace std;

/**********************����˵��*************************

vector<string> arg ��Ϊ�����ԣ�ÿ��split֮������clear���Ա�֤������������ۼ�
���splitΪvoid��ֻ���и��������������У���Ҫvector��ʹ��getArg()��ȡ
���void chkFail(int n)���������ݴ������n��ӡ������Ϣ��
���int checkCmd()��������������г��������жϸ�ʽ�Ƿ�Ϸ�
	-����ֵ0��ʾ�޴���
	-����ֵ1,2...Ϊ������룬����void chkFail(int n)��ӡ������Ϣ
���vector<string> getArg()���������и�������arg vector
********************************************************/
class CommandAnalyse
{
public:
	//CommandAnalyse(string input);
	//�и�ո񣬽�����͸��������뿪��
	void split(string cmd, const string div = " ");
	//���������������ʽ���������Ƿ�Ϸ�
	int checkCmd();
	//��ʾ����nΪ�������
	void chkFail(int n);
	vector<string> getArg();
private:
	vector<string> arg;
	string errorStr;//��һ����������Ĵ�
};