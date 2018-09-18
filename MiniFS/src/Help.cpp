#include"Help.h"
#include "color.h"
void help::commandhelp(string  cmdvec) {
	//printf("%s12\n", cmdvec.c_str());
	Word tmp;
	tmp.setClr(11);
	if (cmdvec == "create") {
		cout << "在程序当前目录下创建1G mini-FS空间。 \n";
		cout << "\nCREATE  [drive:]\n\n";

	}
	else if (cmdvec == "mount") {
		cout << "装载mini-FS空间。 \n";
		cout << "\nMOUNT  [drive:]\n\n";
	}
	else if (cmdvec == "fmt") {
		cout << "格式化mini-FS空间。\n ";
		cout << "\nFMT  [drive:]\n\n";
	}
	else if (cmdvec == "close") {
		cout << "关闭mini-FS空间。\n ";
		cout << "\nCLOSE  [drive:]\n\n";
	}

	else if (cmdvec == "dr") {
		cout << "显示目录中的文件和子目录列表。\n ";
		cout << "\nDR  [drive:][path][filename]\n";
		cout << "指定要列出的驱动器、目录和/或文件。\n\n";
	}
	else if (cmdvec == "md") {
		cout << "创建目录。\n";
		cout << "\nMD [drive:]path\n\n";
	}

	else if (cmdvec == "cp") {
		cout << "将一份文件复制到另一个位置。\n";
		cout << "\n";
		cout << "CP source [+source][destination]\n\n";
	}
	else if (cmdvec == "dl") {
		cout << "删除一个文件。\n";
		cout << "\n";
		cout << "DEL names\n\n";
	}
	else if (cmdvec == "cd") {
		cout << "显示当前目录名或改变当前目录。\n";
		cout << "\n";
		cout << "CD [drive:][path]\n";
		cout << "CD [..]\n";

		cout << "\n .. 代表改变父目录\n\n";
	}
	else if (cmdvec == "tp") {
		cout << "显示文本文件的内容。\n";
		cout << "\n";
		cout << "TYPE [drive:][path]filename\n\n";
	}
	else if (cmdvec == "att") {
		cout << "显示文件属性。\n";
		cout << "\nATT [drive:][path][filename]\n";
		cout << "\n[drive:][path][filename]\n      指定属性要处理的文件。\n\n";
	}
	else if (cmdvec == "more") {
		cout << "指定要逐屏显示的文件。\n";
		cout << "\nMORE  [drive:][path]filename  \n";
		cout << "\n[drive:][path]filename  指定要逐屏显示的文件。\n\n";
	}
	else if (cmdvec == "map") {
		cout << "显示指定文件在空间中所用文件块块号。\n";
		cout << "\nMAP  [drive:][path]filename\n";
		cout << "\n[drive:][path]filename\n      指定属性要处理的文件。\n\n";
	}
	else if (cmdvec == "opt") {
		cout << "优化文件储存空间使其尽可能连续。\n";
		cout << "\n";
		cout << "OPT [dirve:]\n\n";
	}
	else if (cmdvec == "tree") {
		cout << "以树形状显示路径的文件夹结构。\n";
		cout << "\n";
		cout << "TREE [drive:][path]\n\n";
	}
	else if (cmdvec == "mv") {
		cout << "移动文件或文件夹。\n";
		cout << "\n";
		cout << "MOVE [drive:][path]filename1[,...] destination\n\n";
	}
	else if (cmdvec == "import") {
		cout << "将Windows中的文件导入minifs。\n ";
		cout << "\nINPORT  [drive:][path][filename]\n\n";

	}
	else if (cmdvec == "export") {
		cout << "将minifs中的文件导入windows。\n ";
		cout << "\nEXPORT  [drive:][path][filename]\n\n";

	}
	else if (cmdvec == "cls")
	{
		cout << "将控制台窗口清空" << endl;
	}
	else {
		cout << "帮助工具不支持此命令。\n\n";
	}
}