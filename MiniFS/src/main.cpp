#include "Controller.h"
//#include "color.h"
int main()
{
	Controller controller;
	Word tmp;
	while (1)
	{
		tmp.setClr(6);
		controller.ShowPath();//�˴�Ӧ��õ�ǰ·������ӡ
		tmp.setClr(15);
		controller.GetInput();
		if (!controller.Analyse())
			continue;//������Ϣ��chkFail ����
					 //controller.Analyse();
		controller.Execute();
		controller.CmdClear();
	}

	return 0;
}