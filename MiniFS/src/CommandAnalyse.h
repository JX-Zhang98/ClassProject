#pragma once
#include <string>
#include <vector>
#include <iostream>
//#include "color.h"
using namespace std;

/**********************更新说明*************************

vector<string> arg 作为类属性，每次split之初将其clear，以保证不会出现命令累加
变更split为void，只将切割结果保存在属性中，需要vector是使用getArg()获取
添加void chkFail(int n)函数，根据错误代码n打印错误信息。
添加int checkCmd()函数，对命令进行初步解析判断格式是否合法
	-返回值0表示无错误，
	-返回值1,2...为错误代码，调用void chkFail(int n)打印错误信息
添加vector<string> getArg()返回命令切割结果，即arg vector
********************************************************/
class CommandAnalyse
{
public:
	//CommandAnalyse(string input);
	//切割空格，将命令和各参数分离开来
	void split(string cmd, const string div = " ");
	//解析命令，检查命令格式、参数等是否合法
	int checkCmd();
	//显示报错，n为错误代码
	void chkFail(int n);
	vector<string> getArg();
private:
	vector<string> arg;
	string errorStr;//第一个遇到错误的串
};