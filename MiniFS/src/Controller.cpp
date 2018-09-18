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
			cout << "[Error:]文件已存在或创建失败。"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]创建成功。" << endl;
			int end = clock();
			cout << "消耗时间：" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "mount") {
		int temp = fileSystem.Mount(cmdvec[1].c_str());
		if (temp) 
		{
			tmp.setClr(4);
			cout << "[Error:]装载失败。"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]装载成功。"<<endl;
			mountsuccess = true;
			int end = clock();
			cout << "消耗时间：" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "fmt") {
		int temp = fileSystem.Format(cmdvec[1].c_str());
		if (temp) 
		{
			tmp.setClr(4);
			cout << "[Error:]格式化失败。"<<endl;
		}
		else 
		{
			int start = clock();
			tmp.setClr(2);
			cout << "[Success:]格式化成功。"<<endl;
			int end = clock();
			cout << "消耗时间：" << end - start << "ms" << endl;
		}

	}
	else if (cmdvec[0] == "close") {
		tmp.setClr(2);
		cout << "[Success:]minifs空间已关闭。" << endl;
		exit(0);
	}
	else if (cmdvec[0] == "help") {
		//cout << cmdvec.size();
		if (cmdvec.size() == 2) {
			tmp.setClr(11);
			cout << "有关某个命令的详细信息，请键入 HELP 命令名\n"
				<< "操作空间：\n"
				<< "close：		退出mini - FS\n"
				<< "create:		建立一个新mini - FS空间\n"
				<< "fmt：		初始化当前的空间\n"
				<< "help：		显示帮助信息\n"
				<< "mount：		装载空间。\n"
				<< "\n"
				<< "操作目录及文件：\n"
				<< "att：		显示文件或者目录属性\n"
				<< "cd：		打开目标目录\n"
				<< "cp：		复制文件或者子目录\n"
				<< "dl：		删除空间中的文件或者子目录\n"
				<< "dr：		显示空间的文件目录\n"
				<< "map：		显示指定文件在空间所占用的全部块的“块号”\n"
				<< "md：		创建子目录\n"
				<< "opt：		优化整个空间，将每个文件尽可能连续存放\n"
				<< "Import：	导入硬盘上的文件到本系统中\n"
				<< "Export：	将本系统中的文件导出到外部硬盘中\n"
				<< "tree：		以树型方式显示文件目录和文件\n"
				<< "mv：		将指定路径下的文件移动到新的路径\n"
				<< "cls：		清理屏幕\n";
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
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "md") {
		if (mountsuccess)
		{
			int temp = fileSystem.MakeDir(cmdvec[1].c_str());
			if (temp==-1)
			{
				cout << "[Error:]已存在同名文件夹。" << endl;
			}
			else if (temp == -2)
			{
				cout << "[Error:]路径不存在。" << endl;
			}
			else
			{
				tmp.setClr(2);
				cout << "[Success:]成功建立文件夹。" << endl;;
			}
				
		}
		else {
			tmp.setClr(4);
			cout << "[Error:]空间未装载。" << endl;
		}
	}
	else if (cmdvec[0] == "cp") {
		tmp.setClr(4);
		if (mountsuccess)
		{
			int start = clock();
			int temp=fileSystem.Copy(cmdvec[1].c_str(), cmdvec[2].c_str());
			if (temp == -1)
				cout << "[Error:]未找到目标目录或文件。" << endl;
			else if (temp == -2)
				cout << "[Error:]无法将文件拷贝至文件下。" << endl;
			else if (temp == -3)
				cout << "[Error:]已存在同名文件或文件夹。" << endl;
			else if (temp == 0)
			{
				tmp.setClr(2);
				cout << "[Success:]拷贝成功。" << endl;
			}
			else if (temp == -4)
				cout << "[Error:]空间不足,拷贝失败！" << endl;
			int end = clock();
			tmp.setClr(13);
			cout << "消耗时间：" << end - start << "ms" << endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "dl") {
		if (mountsuccess)
		{
			int temp = fileSystem.Delete(cmdvec[1].c_str());
			if (temp == -1) 
			{
				tmp.setClr(4);
				cout << "[Error:]未找到目标文件或文件夹。"<<endl;
			}
			else 
			{
				tmp.setClr(2);
				cout << "[Success:]删除成功。"<<endl;
			}
		}
		else
		{
			tmp.setClr(4);
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "cd") 
	{
		if (mountsuccess)
		{
			if (fileSystem.CDDir(const_cast<char*>(cmdvec[1].c_str())) == -1)
			{
				tmp.setClr(4); ;
				cout << "[Error:]未找到目标文件。" << endl;
			}
		}
		if (!mountsuccess)
		{ 
			tmp.setClr(4); 
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "tp") 
	{
		if (mountsuccess) 
		{
			tmp.setClr(2);
			cout << "显示文本"<<endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]空间未装载。"<<endl;
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
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "more") 
	{
		if (mountsuccess) 
		{
			tmp.setClr(2);
			cout << "分页显示文本。"<<endl;
		}
		else 
		{
			tmp.setClr(4);
			cout << "[Error:]空间未装载。"<<endl;
		}
	}
	else if (cmdvec[0] == "map") 
	{
		tmp.setClr(4);
		if (mountsuccess)
		{
			if (fileSystem.Map(cmdvec[1].c_str()) == -1)
				cout << "[Error:]未找到目标文件。" << endl;
		}
		else
		{
			cout << "[Error:]空间未装载。" << endl;
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
			cout << "[Error:]空间未装载。"<<endl; 
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
				cout << "[Success:]文件导入成功。" << endl;
			}
			else if (temp == -1)
			{
				tmp.setClr(4);
				cout << "[Error:]已存在同名文件。" << endl;
			}
			else if (temp == -2)
			{
				cout << "[Error:]路径错误！" << endl;
			}
			else if (temp == 1)
			{
				tmp.setClr(4);
				cout << "[Error:]文件导入失败。"<<endl;
			}
			else if (temp == 2)
			{
				cout << "[Error:]空间不足！" << endl;
			}
			int end = clock();
			cout << "消耗时间：" << end - start << "ms" << endl;
		}
		else
		{
			cout << "[Error:]空间未装载。" << endl;
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
				cout << "[Success:]文件导出成功。"<<endl;
			}
			else if (temp == -1)
			{
				cout << "[Error:]未找到目标文件。"<<endl;
			}
			else 
			{
				tmp.setClr(4);
				cout << "[Error]文件导出失败。"<<endl;
			}
			int end = clock();
			tmp.setClr(13);
			cout << "消耗时间：" << end - start << "ms" << endl;
		}
		else
		{
			cout << "[Error:]空间未装载。" << endl;
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
			cout << "[Error:]未找到目标文件。" << endl;
		}
		else if (temp == -1)
		{
			cout << "[Error:]无法移动至文件下。" << endl;
		}
		else
		{
			tmp.setClr(2);
			cout << "[Success:]文件移动成功。" << endl;
		}
	}
	else
	{
		cout << "[Error:]空间未装载。" << endl;
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
	if (!errorCode)//0表示无错误
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