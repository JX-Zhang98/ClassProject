#include "Directory.h"
#include "color.h"
Directory::Directory()
{
	
}

Directory::~Directory()
{

}

FileInfo Directory::Root()
{
	FileInfo root;
	memset(&root, 0, sizeof(FileInfo));
	root.state = 3;
	root.size = 1;
	root.date = Time::date();
	root.time = Time::time();
	return root;
}

void Directory::printSpace(int depth)
{
	for (int i = 0; i < 3; i++)
		putchar(' ');
}

bool Directory::namecompare(const char *str1, const char *str2, int style)
{
	if (style == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
			if (str1[i] == '\0'&&str2[i] == '\0')
				break;
		}
		return true;
	}
	else if (style == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
			if (str1[i] == '\0'&&str2[i] == '\0')
				break;
		}
		return true;
	}
}

void Directory::showWholeName(int now)
{
	for (int i = 0; i < 8; i++)
	{
		if (File[now].name[i] == '\0')
			break;
		else
			putchar(File[now].name[i]);
	}
	if (File[now].state == 1)
	{
		putchar('.');
		for (int i = 0; i < 3; i++)
		{
			if (File[now].extension[i] == '\0')
				break;
			else
				putchar(File[now].extension[i]);
		}
	}
}

void Directory::BuildTree()
{
	for (int i = 0; i < FileNumber; i++)
	{
		Tree.push_back(Node());
	}
	for (int i = 0; i < FileNumber; i++)
	{
		Tree[i].state = File[i].state;
		Tree[i].parent = File[i].parent;
		if (File[i].state == 1 || File[i].state == 2)
		{
			Tree[File[i].parent].child.push_back(i);
		}
	}
}

void Directory::Push(int number)
{
	int size = Tree.size();
	if (size < number + 1)
	{
		Tree.push_back(Node());
		FileNumber++;
		File[0].size++;
	}
	Tree[number].state = File[number].state;
	Tree[number].parent = File[number].parent;
	Tree[File[number].parent].child.push_back(number);

}

void Directory::Change(int number, FileInfo now)
{
	File[number].state = now.state;
	for (int i = 0; i < 8; i++)
	{
		File[number].name[i] = now.name[i];
	}
	for (int i = 0; i < 3; i++)
	{
		File[number].extension[i] = now.extension[i];
	}
	File[number].location = now.location;
	File[number].size = now.size;
	File[number].parent = now.parent;
	File[number].date = Time::date();
	File[number].time = Time::time();
}

int Directory::FindEmpty()
{
	for (int i = 0; i < BLOCKNUMBER; i++)
	{
		if (File[i].state == 0) return i;
	}
	return -1;
}

int Directory::Search(char * name, char *extension, int number)
{
	for (list<int>::iterator it = Tree[number].child.begin(); it != Tree[number].child.end(); it++)
	{
		if (File[*it].state == 0)
			continue;
		if (namecompare(name, File[*it].name, 1) && namecompare(extension, File[*it].extension, 2))
			return *it;
	}
	return -1;
}

int Directory::Add(FileInfo now)
{
	int emptydirectory = FindEmpty();
	Change(emptydirectory, now);
	Push(emptydirectory);
	return 0;
}

void Directory::Move(int now, int tar)
{
	Tree[Tree[now].parent].child.remove(now);
	Tree[now].parent = tar;
	File[now].parent = tar;
	Tree[tar].child.push_back(now);
}

//void Directory::recursionDelete(int number)
//{
//	if (File[number].state == 1)
//	{
//		File[number].state = 0;
//		Tree[number].state = 0;
//	}
//	else if (File[number].state == 2)
//	{
//		File[number].state = 0;
//		Tree[number].state = 0;
//		for (list<int>::iterator it = Tree[number].child.begin(); it != Tree[number].child.end();)
//		{
//			recursionDelete(*it);
//			Tree[number].child.erase(it);
//		}
//	}
//}
void Directory::Delete(int number)
{
	File[number].state = 0;
	Tree[number].state = 0;
}

int Directory::CountUnderDir(int number)
{
	if (File[number].state == 0)
		return 0;
	if (File[number].state == 1)
		return 1;
	int cnt = 1;
	if (File[number].state == 3)
		cnt = 0;
	for (list<int>::iterator it = Tree[number].child.begin(); it != Tree[number].child.end(); it++)
	{
		cnt += CountUnderDir(*it);
	}
	return cnt;
}

void Directory::ShowPath(int now)
{
	Word tmp;
	vector<string>output;
	while (File[now].parent != 0)
	{
		now = File[now].parent;
		string wholename;
		for (int i = 0; i < 8; i++)
		{
			if (File[now].name[i] == '\0')
			{
				wholename.push_back('\0');
				break;
			}
			else
				wholename.push_back(File[now].name[i]);
		}
		output.push_back(wholename);
	}
	tmp.setClr(13);
	cout << "MiniFS:";
	if (output.size() == 0)
		return;
	vector<string>::iterator it;
	for (it = output.end() - 1; it >= output.begin(); it--)
	{
		tmp.setClr(6);
		putchar('\\');
		cout << (*it);
		if (it == output.begin())
			break;
	}
}
void Directory::ShowDir(int now)
{
	Word tmp;
	list<int>::iterator itor;
	long long int sumsize = 0;
	int sumdoc = 0;
	itor = Tree[now].child.begin();
	while (itor != Tree[now].child.end())
	{
		int now = *itor;
		string date = "";
		string time = "";
		int year = File[now].date / 10000;
		int month = File[now].date % 10000 / 100;
		int day = File[now].date % 100;
		date += std::to_string(year) + "/";
		if (month < 10)
			date += "0";
		date += std::to_string(month) + "/";
		if (day < 10)
			date += "0";
		date += std::to_string(day);
		tmp.setClr(7);
		cout << date << "  ";
		int hour = File[now].time / 10000;
		int minute = File[now].time % 10000 / 100;
		int second = File[now].time % 100;
		if (hour < 10)
			time += "0";
		time += std::to_string(hour) + ":";
		if (minute < 10)
			time += "0";
		time += std::to_string(minute) + ":";
		if (second < 10)
			time += "0";
		time += std::to_string(second);
		cout << time << "    ";
		//cout << File[now].date << "  ";//2
		//cout << File[now].time << "    ";//4
		tmp.setClr(14);
		if (File[now].state == 1)
		{
			cout << "     ";
			cout.width(10);
			cout <<right<< File[now].size;
			sumsize += File[now].size;
			sumdoc++;
		}
		else
			cout << "<DIR>          ";//10
		cout << " ";
		showWholeName(now);
		putchar('\n');
		itor++;
	}
	cout.width(14);
	cout <<right<< sumdoc << "个文件";
	cout.width(20);
	cout <<right<< sumsize << " 字节" << endl;
}

void Directory::recursionSearch(int now, int depth)
{
	Word tmp;
	for (list<int>::iterator it = Tree[now].child.begin(); it != Tree[now].child.end(); it++)
	{
		list<int>::iterator last = Tree[now].child.end();
		last--;
		if (it == last)
		{
			for (int i = 0; i < depth; i++)
			{
				if (vislst[i] == 0)
				{
					cout << "│";
				}
				else
					putchar(' ');
				printSpace(i);
			}
			cout << "└ ";
			File[*it].ShowName();
			putchar('\n');
			vislst[depth] = 1;
		}
		else
		{
			for (int i = 0; i < depth; i++)
			{
				if (vislst[i] == 0)
				{
					cout << "│";
				}
				else
					putchar(' ');
				printSpace(i);
			}
			cout << "├ ";
			File[*it].ShowName();
			putchar('\n');
		}
		recursionSearch(*it, depth + 1);
	}
	vislst[depth] = 0;
}
void Directory::ShowTree(int now)
{
	Word tmp;
	tmp.setClr(15);
	cout << "MiniFS:." << endl;
	recursionSearch(now, 0);
	cout << endl;
}
void Directory::ShowAtt(int now)
{
	Word tmp;
	tmp.setClr(13);
	if (File[now].state == 1)
	{
		putchar('A');
		printSpace(1);
		ShowPath(now);
		putchar('\\');
		showWholeName(now);
		putchar('\n');
		return;
	}
	list<int>::iterator it;
	it = Tree[now].child.begin();
	while (it != Tree[now].child.end())
	{
		tmp.setClr(13);
		if (File[*it].state == 1)
		{
			putchar('A');
			printSpace(1);
			ShowPath(*it);
			putchar('\\');
			showWholeName(*it);
			putchar('\n');
		}
		it++;
	}
}

//│└├
