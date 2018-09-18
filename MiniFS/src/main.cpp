#include "Controller.h"
//#include "color.h"
int main()
{
	Controller controller;
	Word tmp;
	while (1)
	{
		tmp.setClr(6);
		controller.ShowPath();//此处应获得当前路径并打印
		tmp.setClr(15);
		controller.GetInput();
		if (!controller.Analyse())
			continue;//报错信息在chkFail 给出
					 //controller.Analyse();
		controller.Execute();
		controller.CmdClear();
	}

	return 0;
}