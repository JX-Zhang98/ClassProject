#include"Help.h"
#include "color.h"
void help::commandhelp(string  cmdvec) {
	//printf("%s12\n", cmdvec.c_str());
	Word tmp;
	tmp.setClr(11);
	if (cmdvec == "create") {
		cout << "�ڳ���ǰĿ¼�´���1G mini-FS�ռ䡣 \n";
		cout << "\nCREATE  [drive:]\n\n";

	}
	else if (cmdvec == "mount") {
		cout << "װ��mini-FS�ռ䡣 \n";
		cout << "\nMOUNT  [drive:]\n\n";
	}
	else if (cmdvec == "fmt") {
		cout << "��ʽ��mini-FS�ռ䡣\n ";
		cout << "\nFMT  [drive:]\n\n";
	}
	else if (cmdvec == "close") {
		cout << "�ر�mini-FS�ռ䡣\n ";
		cout << "\nCLOSE  [drive:]\n\n";
	}

	else if (cmdvec == "dr") {
		cout << "��ʾĿ¼�е��ļ�����Ŀ¼�б�\n ";
		cout << "\nDR  [drive:][path][filename]\n";
		cout << "ָ��Ҫ�г�����������Ŀ¼��/���ļ���\n\n";
	}
	else if (cmdvec == "md") {
		cout << "����Ŀ¼��\n";
		cout << "\nMD [drive:]path\n\n";
	}

	else if (cmdvec == "cp") {
		cout << "��һ���ļ����Ƶ���һ��λ�á�\n";
		cout << "\n";
		cout << "CP source [+source][destination]\n\n";
	}
	else if (cmdvec == "dl") {
		cout << "ɾ��һ���ļ���\n";
		cout << "\n";
		cout << "DEL names\n\n";
	}
	else if (cmdvec == "cd") {
		cout << "��ʾ��ǰĿ¼����ı䵱ǰĿ¼��\n";
		cout << "\n";
		cout << "CD [drive:][path]\n";
		cout << "CD [..]\n";

		cout << "\n .. ����ı丸Ŀ¼\n\n";
	}
	else if (cmdvec == "tp") {
		cout << "��ʾ�ı��ļ������ݡ�\n";
		cout << "\n";
		cout << "TYPE [drive:][path]filename\n\n";
	}
	else if (cmdvec == "att") {
		cout << "��ʾ�ļ����ԡ�\n";
		cout << "\nATT [drive:][path][filename]\n";
		cout << "\n[drive:][path][filename]\n      ָ������Ҫ������ļ���\n\n";
	}
	else if (cmdvec == "more") {
		cout << "ָ��Ҫ������ʾ���ļ���\n";
		cout << "\nMORE  [drive:][path]filename  \n";
		cout << "\n[drive:][path]filename  ָ��Ҫ������ʾ���ļ���\n\n";
	}
	else if (cmdvec == "map") {
		cout << "��ʾָ���ļ��ڿռ��������ļ����š�\n";
		cout << "\nMAP  [drive:][path]filename\n";
		cout << "\n[drive:][path]filename\n      ָ������Ҫ������ļ���\n\n";
	}
	else if (cmdvec == "opt") {
		cout << "�Ż��ļ�����ռ�ʹ�価����������\n";
		cout << "\n";
		cout << "OPT [dirve:]\n\n";
	}
	else if (cmdvec == "tree") {
		cout << "������״��ʾ·�����ļ��нṹ��\n";
		cout << "\n";
		cout << "TREE [drive:][path]\n\n";
	}
	else if (cmdvec == "mv") {
		cout << "�ƶ��ļ����ļ��С�\n";
		cout << "\n";
		cout << "MOVE [drive:][path]filename1[,...] destination\n\n";
	}
	else if (cmdvec == "import") {
		cout << "��Windows�е��ļ�����minifs��\n ";
		cout << "\nINPORT  [drive:][path][filename]\n\n";

	}
	else if (cmdvec == "export") {
		cout << "��minifs�е��ļ�����windows��\n ";
		cout << "\nEXPORT  [drive:][path][filename]\n\n";

	}
	else if (cmdvec == "cls")
	{
		cout << "������̨�������" << endl;
	}
	else {
		cout << "�������߲�֧�ִ����\n\n";
	}
}