#pragma once
#include <windows.h>
/*
��Ӧ����ɫ���
1. 0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       10 = ����ɫ
3 = ǳ��ɫ     11 = ��ǳ��ɫ
4 = ��ɫ       12 = ����ɫ
5 = ��ɫ       13 = ����ɫ
6 = ��ɫ       14 = ����ɫ
7 = ��ɫ       15 = ����ɫ
*/

//��һ��������������ɫ���ڶ��������Ǳ�����ɫ
class Word
{
public:
	void setClr(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);
};
