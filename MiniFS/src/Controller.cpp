#include"Controller.h"
Controller::Controller()
{
	mountsuccess = false;
}
void Controller::Execute()
{
	Word tmp;
	tmp.setClr(4);
	if (cmdvec[0] == "create") {
		int temp = fileSystem.Create(cmdvec[1].c_str());
		if (temp) 
		{
			tmp.setClr(4);
			cout << "[Error:]�ļ��Ѵ��ڻ򴴽�ʧ�ܡ�"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]�����ɹ���" << endl;
			int end = clock();
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "mount") {
		int temp = fileSystem.Mount(cmdvec[1].c_str());
		if (temp) 
		{
			tmp.setClr(4);
			cout << "[Error:]װ��ʧ�ܡ�"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]װ�سɹ���"<<endl;
			mountsuccess = true;
			int end = clock();
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "fmt") {
		int temp = fileSystem.Format(cmdvec[1].c_str());
		if (temp) 
		{
			tmp.setClr(4);
			cout << "[Error:]��ʽ��ʧ�ܡ�"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]��ʽ���ɹ���"<<endl;
			int end = clock();
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "close") {
		tmp.setClr(2);
		cout << "[Success:]minifs�ռ��ѹرա�" << endl;
		exit(0);
	}
	else if (cmdvec[0] == "help") {
		//cout << cmdvec.size();
		if (cmdvec.size() == 2) {
			tmp.setClr(11);
			cout << "�й�ĳ���������ϸ��Ϣ������� HELP ������\n"
				<< "�����ռ䣺\n"
				<< "close��		�˳�mini - FS\n"
				<< "create:		����һ����mini - FS�ռ�\n"
				<< "fmt��		��ʼ����ǰ�Ŀռ�\n"
				<< "help��		��ʾ������Ϣ\n"
				<< "mount��		װ�ؿռ䡣\n"
				<< "\n"
				<< "����Ŀ¼���ļ���\n"
				<< "att��		��ʾ�ļ�����Ŀ¼����\n"
				<< "cd��		��Ŀ��Ŀ¼\n"
				<< "cp��		�����ļ�������Ŀ¼\n"
				<< "dl��		ɾ���ռ��е��ļ�������Ŀ¼\n"
				<< "dr��		��ʾ�ռ���ļ�Ŀ¼\n"
				<< "map��		��ʾָ���ļ��ڿռ���ռ�õ�ȫ����ġ���š�\n"
				<< "md��		������Ŀ¼\n"
				<< "opt��		�Ż������ռ䣬��ÿ���ļ��������������\n"
				<< "Import��	����Ӳ���ϵ��ļ�����ϵͳ��\n"
				<< "Export��	����ϵͳ�е��ļ��������ⲿӲ����\n"
				<< "tree��		�����ͷ�ʽ��ʾ�ļ�Ŀ¼���ļ�\n"
				<< "mv��		��ָ��·���µ��ļ��ƶ����µ�·��\n"
				<< "cls��		������Ļ\n";
		}
		else {
			help helpcmd;
			helpcmd.commandhelp(cmdvec[1]);
		}

	}
	else if (cmdvec[0] == "dr") {
		if (mountsuccess)
			fileSystem.Dir(cmdvec[1].c_str());
		else
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "md") {
		if (mountsuccess)
		{
			int temp = fileSystem.MakeDir(cmdvec[1].c_str());
			if (temp==-1)
			{
				cout << "[Error:]�Ѵ���ͬ���ļ��С�" << endl;
			}
			else if (temp == -2)
			{
				cout << "[Error:]·�������ڡ�" << endl;
			}
			else
			{
				tmp.setClr(2);
				cout << "[Success:]�ɹ������ļ��С�" << endl;;
			}
				
		}
		else {
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�" << endl;
		}
	}
	else if (cmdvec[0] == "cp") {
		tmp.setClr(4);
		if (mountsuccess)
		{
			int start = clock();
			int temp=fileSystem.Copy(cmdvec[1].c_str(), cmdvec[2].c_str());
			if (temp == -1)
				cout << "[Error:]δ�ҵ�Ŀ��Ŀ¼���ļ���" << endl;
			else if (temp == -2)
				cout << "[Error:]�޷����ļ��������ļ��¡�" << endl;
			else if (temp == -3)
				cout << "[Error:]�Ѵ���ͬ���ļ����ļ��С�" << endl;
			else if (temp == 0)
			{
				tmp.setClr(2);
				cout << "[Success:]�����ɹ���" << endl;
			}
			else if (temp == -4)
				cout << "[Error:]�ռ䲻��,����ʧ�ܣ�" << endl;
			int end = clock();
			tmp.setClr(13);
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "dl") {
		if (mountsuccess)
		{
			int temp = fileSystem.Delete(cmdvec[1].c_str());
			if (temp == -1) 
			{
				tmp.setClr(4);
				cout << "[Error:]δ�ҵ�Ŀ���ļ����ļ��С�"<<endl;
			}
			else 
			{
				tmp.setClr(2);
				cout << "[Success:]ɾ���ɹ���"<<endl;
			}
		}
		else
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "cd") 
	{
		if (mountsuccess)
		{
			if (fileSystem.CDDir(const_cast<char*>(cmdvec[1].c_str())) == -1)
			{
				tmp.setClr(4); ;
				cout << "[Error:]δ�ҵ�Ŀ���ļ���" << endl;
			}
		}
		if (!mountsuccess)
		{ 
			tmp.setClr(4); 
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "tp") 
	{
		if (mountsuccess) 
		{
			tmp.setClr(2);
			cout << "��ʾ�ı�"<<endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "att") 
	{
		if (mountsuccess)
		{
			fileSystem.Attrib(cmdvec[1].c_str());
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "more") 
	{
		if (mountsuccess) 
		{
			tmp.setClr(2);
			cout << "��ҳ��ʾ�ı���"<<endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl;
		}
	}
	else if (cmdvec[0] == "map") 
	{
		tmp.setClr(4);
		if (mountsuccess)
		{
			if (fileSystem.Map(cmdvec[1].c_str()) == -1)
				cout << "[Error:]δ�ҵ�Ŀ���ļ���" << endl;
		}
		else
		{
			cout << "[Error:]�ռ�δװ�ء�" << endl;
		}
	}
	else if (cmdvec[0] == "opt") {}
	else if (cmdvec[0] == "tree") 
	{
		if (mountsuccess)
		{
			fileSystem.Tree(cmdvec[1].c_str());
		}
		else
		{
			tmp.setClr(4);
			cout << "[Error:]�ռ�δװ�ء�"<<endl; 
		}
	}
	else if (cmdvec[0] == "import")
	{
		tmp.setClr(4);
		if (mountsuccess)
		{
			int start = clock();
			int temp = fileSystem.Import(cmdvec[1].c_str(), cmdvec[2].c_str());
			if (temp == 0)
			{
				tmp.setClr(2);
				cout << "[Success:]�ļ�����ɹ���" << endl;
			}
			else if (temp == -1)
			{
				tmp.setClr(4);
				cout << "[Error:]�Ѵ���ͬ���ļ���" << endl;
			}
			else if (temp == -2)
			{
				cout << "[Error:]·������" << endl;
			}
			else if (temp == 1)
			{
				tmp.setClr(4);
				cout << "[Error:]�ļ�����ʧ�ܡ�"<<endl;
			}
			else if (temp == 2)
			{
				cout << "[Error:]�ռ䲻�㣡" << endl;
			}
			int end = clock();
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}
		else
		{
			cout << "[Error:]�ռ�δװ�ء�" << endl;
		}
	}
	else if (cmdvec[0] == "export")
	{
		tmp.setClr(4);
		if (mountsuccess)
		{
			int start = clock();
			int temp = fileSystem.Export(cmdvec[1].c_str(), cmdvec[2].c_str());
			if (temp==0) 
			{
				tmp.setClr(2);
				cout << "[Success:]�ļ������ɹ���"<<endl;
			}
			else if (temp == -1)
			{
				cout << "[Error:]δ�ҵ�Ŀ���ļ���"<<endl;
			}
			else 
			{
				tmp.setClr(4);
				cout << "[Error]�ļ�����ʧ�ܡ�"<<endl;
			}
			int end = clock();
			tmp.setClr(13);
			cout << "����ʱ�䣺" << end - start << "ms" << endl;
		}
		else
		{
			cout << "[Error:]�ռ�δװ�ء�" << endl;
		}
	}
	else if (cmdvec[0] == "mv")
	{
		tmp.setClr(4);
	if (mountsuccess)
	{
		int temp = fileSystem.Move(cmdvec[1].c_str(), cmdvec[2].c_str());
		if (temp == -2)
		{
			cout << "[Error:]δ�ҵ�Ŀ���ļ���" << endl;
		}
		else if (temp == -1)
		{
			cout << "[Error:]�޷��ƶ����ļ��¡�" << endl;
		}
		else
		{
			tmp.setClr(2);
			cout << "[Success:]�ļ��ƶ��ɹ���" << endl;
		}
	}
	else
	{
		cout << "[Error:]�ռ�δװ�ء�" << endl;
	}
	}
	else if (cmdvec[0] == "cls")
	{
		system("cls");
	}
}
void Controller::GetInput()
{
	cmdstr = cmdInput.UserInput();
}
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
void Controller::CmdClear()
{
	cmdvec.clear();
	cmdstr.clear();
}
void Controller::ShowPath()
{
	cout << fileSystem.GetPath()+">";
}