#include "CommandAnalyse.h"
#include "color.h"
void CommandAnalyse::split(string cmd, const string div)
{
	//vector<string>arg;
	arg.clear();
	string::size_type n1, n2;
	n2 = cmd.find(div);
	n1 = 0;
	while (string::npos != n2)
	{
		if (n1 == n2)
		{
			n1 = n2 + div.size();
			n2 = cmd.find(div, n1);
			continue;
		}
		arg.push_back(cmd.substr(n1, n2 - n1));
		n1 = n2 + div.size();
		n2 = cmd.find(div, n1);
	}
	if (n1 != cmd.length())
	{
		arg.push_back(cmd.substr(n1));
	}
	arg.push_back("");
	//return arg;
}

vector<string> CommandAnalyse::getArg()
{
	return arg;
}

int CommandAnalyse::checkCmd()
{
	//�޲�����
	if (arg[0] == "close" || arg[0] == "opt" || arg[0] == "cls")
	{
		if (arg.size() > 2)
		{
			errorStr = arg[1];
			return 2;
		}
		return 0;
	}
	//��������
	else if (arg[0] == "create" || arg[0] == "mount" || arg[0] == "fmt"
		|| arg[0] == "dl" || arg[0] == "cd"
		|| arg[0] == "tp" || arg[0] == "more"
		|| arg[0] == "md"||arg[0]=="map")
	{
		if (arg.size() != 3)
		{
			return 3;
		}
		return 0;
	}
	//˫������
	else if (arg[0] == "cp" || arg[0] == "mv" || arg[0] == "import" || arg[0] == "export")
	{//����һ��Ҫ���ܷ��ҵ��ļ��ļ��
		if (arg.size() != 4)
		{
			return 4;
		}
		return 0;
	}
	//�����ָ��
	else if (arg[0] == "help" || arg[0] == "tree" || arg[0] == "dr" || arg[0] == "att" )
	{
		if (arg.size() > 3)
		{
			errorStr = arg[2];
			return 5;
		}
		return 0;
	}

	/*else if (arg[0] == "")
	{
		if (arg.size() > 4)
		{
			return 6;
		}
		return 0;
	}*/
	errorStr = arg[0];
	return 1;
}

void CommandAnalyse::chkFail(int n)
{
	Word tmp;
	switch (n)
	{
	case 1://�������
		tmp.setClr(4);
		cout << "Error: ";
		tmp.setClr(12);
		cout << errorStr << endl;
		tmp.setClr(4);
		cout << "command not found!" << endl;
		break;
	case 2://����Ҫ����
		tmp.setClr(4);
		cout << "Parameter error: ";
		tmp.setClr(12);
		cout << errorStr << endl;
		tmp.setClr(4);
		cout << "No parameter is requested!" << endl;
		cout << "Please enter 'help' for details" << endl;
		break;
	case 3://only one arg
		tmp.setClr(4);
		cout << "Parameter error!" << endl;
		tmp.setClr(4);
		cout << "One parameter is requested!" << endl;
		break;
	case 4:// 2 argv
		tmp.setClr(4);
		cout << "Parameter error!" << endl;
		tmp.setClr(4);
		cout << "Two parameters are requested!" << endl;
		break;
	case 5:
		tmp.setClr(4);
		cout << "Parameter error: ";
		tmp.setClr(12);
		cout << errorStr << endl;
		tmp.setClr(4);
		cout << "At most two parameters are needed." << endl;
	default:
		break;
	}
}

/*****************����Ϊ�����ļ��д�����޸����*****************
main:
while (1)
{
cout << "root:~/Desktop $";//�˴�Ӧ��õ�ǰ·������ӡ
controller.GetInput();
if(!controller.Analyse())
continue;//������Ϣ��chkFail ����
//controller.Analyse();
controller.Execute();
controller.CmdClear();
}
---------------
bool Controller::Analyse()
{
//cmdvec = cmdAnalyse.split(cmdstr, " ");
cmdAnalyse.split(cmdstr, " ");
int errorCode = cmdAnalyse.checkCmd();
if (!errorCode)//0��ʾ�޴���
{
cmdvec = cmdAnalyse.getArg();
return true;
}
cmdAnalyse.chkFail(errorCode);
return false;
}
---------------
�޸�Controllerͷ�ļ��ж�Analyse���壬�䷵������Ϊbool

****************************************************************/
