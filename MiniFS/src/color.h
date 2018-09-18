#pragma once
#include <windows.h>
/*
对应的颜色码表：
1. 0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       10 = 淡绿色
3 = 浅绿色     11 = 淡浅绿色
4 = 红色       12 = 淡红色
5 = 紫色       13 = 淡紫色
6 = 黄色       14 = 淡黄色
7 = 白色       15 = 亮白色
*/

//第一个参数是字体颜色，第二个参数是背景颜色
class Word
{
public:
	void setClr(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0);
};
