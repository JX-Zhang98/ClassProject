#pragma once
#include<string>
#include<vector>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include <time.h>
#include "CommandAnalyse.h"
#include "CommandInput.h"
#include "FileSystem.h"
#include "Help.h"


using namespace std;

class Controller {
public:
	Controller();
	void Execute();
	void GetInput();
	bool Analyse();
	void CmdClear();
	void ShowPath();
private:
	CommandInput cmdInput;
	CommandAnalyse cmdAnalyse;
	FileSystem fileSystem;

	vector<string> cmdvec;
	string cmdstr;
	bool mountsuccess;

};