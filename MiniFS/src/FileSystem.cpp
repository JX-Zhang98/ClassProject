#include "FileSystem.h"

FileSystem::FileSystem()
{
	state = 0;
	fileOperator = new FileOperator;
	nowDirNum = 0;
	nowPath = "MiniFS:\\";
}
string FileSystem::GetPath()
{
	return nowPath;
}
FileSystem::~FileSystem()
{

}
int FileSystem::GetDirNum(const char * filename)
{
	if (filename[0] == '\0')
		return nowDirNum;
	char *path;
	path = const_cast<char*>(filename);
	strcpy(path, filename);
	int numbernow;
	path = strtok(path, "\\");
	const char root[8] = "MiniFS:";
	const char thisDir[5] = ".";
	const char fatherDir[5] = "..";
	if (strcmp(path, root) == 0)
		numbernow = 0;
	else if (strcmp(path, thisDir) == 0)
	{
		numbernow = nowDirNum;
	}
	else if (strcmp(path, fatherDir) == 0)
	{
		numbernow = directory->Tree[nowDirNum].parent;
	}
	else
	{
		numbernow = nowDirNum;
		char name[8] = { 0 };
		char extension[3] = { 0 };
		int temp = splitName(name, extension, path);
		if (temp == -1)
			return -1;
		numbernow = directory->Search(name, extension, numbernow);
		if (numbernow == -1)
			return -1;
	}

	while (path != NULL)
	{
		path = strtok(NULL, "\\");
		if (path == NULL)
			break;

		if (strcmp(path, thisDir) == 0)
		{
			continue;
		}
		else if (strcmp(path, fatherDir) == 0)
		{
			numbernow = directory->Tree[numbernow].parent;
			continue;
		}
		char name[8] = { 0 };
		char extension[3] = { 0 };

		int temp = splitName(name, extension, path);
		if (temp == -1)
			return -1;
		numbernow = directory->Search(name, extension, numbernow);
		if (numbernow == -1)
			return -1;
	}
	return numbernow;
}

int FileSystem::getParentNumber(char* path)
{
	int parentnumber;
	if (*path == '\0')
		parentnumber =nowDirNum;
	else
	{
		parentnumber = GetDirNum(path);
		if (parentnumber == -1)
			return -1;
		if (directory->File[parentnumber].state != 2 && directory->File[parentnumber].state != 3)
			return -1;
	}
	return parentnumber;
}
void FileSystem::splitSlash(char*wholename,char*path)
{
	int len = strlen(path);
	int slashpos = -1, p = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (path[i] == '\\')
		{
			slashpos = i;
			break;
		}
	}
	for (int i = slashpos + 1; i < len; i++)
	{
		wholename[p++] = path[i];
	}
	wholename[p] = '\0';
	if (slashpos == -1)
		path[0] = '\0';
	else
		path[slashpos] = '\0';
}
int FileSystem::splitName(char *name, char * extension, char *wholename)
{
	int pos;
	for (pos = 0; wholename[pos] != '\0'; pos++)
	{
		if (wholename[pos] == '.')
		{
			if (pos != 7)
				name[pos] = '\0';
			break;
		}
		if (pos >= 8)
			return -1;
		name[pos] = wholename[pos];
	}
	if (pos != 8)
		name[pos] = '\0';
	if (wholename[pos] == '.')
	{
		int p = 0;
		for (int i = pos + 1; wholename[i] != '\0'; i++, p++)
		{
			if (i - pos > 3)
				return -1;
			extension[i - pos - 1] = wholename[i];
		}
		if (p != 3)
			extension[p] = '\0';
	}
	return 1;
}
void FileSystem::setNowPath(int now)
{
	vector<string>path;
	string wholename;
	for (int i = 0; i < 8; i++)
	{
		if (directory->File[now].name[i] == '\0')
		{
			wholename.push_back('\0');
			break;
		}
		else
			wholename.push_back(directory->File[now].name[i]);
	}
	path.push_back(wholename);
	while (directory->File[now].parent != 0)
	{
		now = directory->File[now].parent;
		string wholename;
		for (int i = 0; i < 8; i++)
		{
			if (directory->File[now].name[i] == '\0')
			{
				wholename.push_back('\0');
				break;
			}
			else
				wholename.push_back(directory->File[now].name[i]);
		}
		path.push_back(wholename);
	}
	
	string temppath="MiniFS:";
	vector<string>::iterator it;
	for (it = path.end() - 1; it >= path.begin(); it--)
	{
		temppath+="\\";
		temppath += *it;
		if (it == path.begin())
			break;
	}
	nowPath = temppath;
}

//返回1：文件已存在；返回0，创建成功
int FileSystem::Create(const char *filename)
{
	if (!fileOperator->Open(filename)) return 1;
	fileOperator->Create(filename);
	int start = 1;
	fileOperator->MovePoint(INDEXLOCATION);
	fileOperator->Write(&start, 4);
	FileInfo root = Directory::Root();
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(&root, DIRECTORY);
	char end = 0;
	fileOperator->MovePoint(SYSTEM - 1);
	fileOperator->Write(&end, 1);
	fileOperator->Close();
	return 0;
}
int FileSystem::Format(const char *filename)
{
	if (fileOperator->Open(filename)) return 1;
	fileOperator->Create(filename);
	int start = 1;
	fileOperator->MovePoint(INDEXLOCATION);
	fileOperator->Write(&start, 4);
	FileInfo root = Directory::Root();
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(&root, DIRECTORY);
	char end = 0;
	fileOperator->MovePoint(SYSTEM - 1);
	fileOperator->Write(&end, 1);
	fileOperator->Close();
	return 0;
}
//返回1：打开失败；返回0：打开成功
int FileSystem::Mount(const char *filename)
{
	if (fileOperator->Open(filename)) return 1;
	state = 1;
	index = new Index;
	fileOperator->MovePoint(INDEXLOCATION);
	fileOperator->Read(index->Array, BLOCKNUMBER * INDEX);
	index->CountFreeBlockNumber();
	directory = new Directory;
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Read(directory->File, DIRECTORY);
	int filenumber = directory->File[0].size;
	directory->FileNumber = filenumber;
	fileOperator->Read(directory->File + 1, (filenumber - 1) * DIRECTORY);
	directory->BuildTree();
	return 0;
}
int FileSystem::Import(const char *filename,const char*path)
{
	if (fileOperator->OpenFile(filename)) return 1;

	char wholenametemp[15];
	splitSlash(wholenametemp, const_cast<char*>(path));
	char nametemp[8] = { 0 }, extensiontemp[3] = { 0 };
	splitName(nametemp, extensiontemp, wholenametemp);
	int parentnumber = getParentNumber(const_cast<char*>(path));
	if (parentnumber == -1)
		return -2;
	int flag = directory->Search(nametemp, extensiontemp, parentnumber);
	if (flag != -1)
		return -1;
	int size = fileOperator->FileSize();
	int blocknumber = (size + BLOCK - 1) / BLOCK;
	if (blocknumber > index->FreeBlockNumber) return 2;//空间不足
	index->FreeBlockNumber -= blocknumber;
	index->ModificationIndexList = (int *)malloc(blocknumber * INDEX);
	index->ModificationIndexNumber = 0;
	char *buffer = (char *)malloc(size < (MAXBUFFERSIZE) ? size : (MAXBUFFERSIZE));
	int firstlocation = index->FindEmptyBlock();
	int location = firstlocation;
	for (int i = 0; i < (size + (MAXBUFFERSIZE) - 1) / (MAXBUFFERSIZE); i++)
	{
		if (i != (size - 1) / (MAXBUFFERSIZE))
		{
			fileOperator->ReadFile(buffer, (MAXBUFFERSIZE));
			location = WriteData(buffer, (MAXBUFFERSIZE), location, 0);
		}
		else
		{
			fileOperator->ReadFile(buffer, (size - 1) % (MAXBUFFERSIZE) + 1);
			WriteData(buffer, (size - 1) % (MAXBUFFERSIZE) + 1, location, -1);
		}
	}
	//修改目录和索引
	FileInfo info(1, nametemp, extensiontemp, firstlocation, size, parentnumber);
	directory->Add(info);
	WriteIndex();
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(directory->File, directory->FileNumber * DIRECTORY);
	free(buffer);
	free(index->ModificationIndexList);
	index->ModificationIndexNumber = 0;
	fileOperator->Flush();
	fileOperator->CloseFile();
	return 0;
}
void FileSystem::WriteIndex()
{
	sort(index->ModificationIndexList, index->ModificationIndexList + index->ModificationIndexNumber);
	int startindex = index->ModificationIndexList[0];
	int size = INDEX;
	for (int i = 0; i < index->ModificationIndexNumber; i++)
	{
		if (i == index->ModificationIndexNumber - 1)
		{
			fileOperator->MovePoint(INDEXLOCATION + startindex * INDEX);
			fileOperator->Write(index->Array + startindex, size);
		}
		else if (index->ModificationIndexList[i + 1] - index->ModificationIndexList[i] <= BLOCK / INDEX)
		{
			size += (index->ModificationIndexList[i + 1] - index->ModificationIndexList[i]) * INDEX;
		}
		else
		{
			fileOperator->MovePoint(INDEXLOCATION + startindex * INDEX);
			fileOperator->Write(index->Array + startindex, size);
			startindex = index->ModificationIndexList[i + 1];
			size = INDEX;
		}
	}
}
//location为当前操作首地址，mode正常时为0，读写到末尾为-1
int FileSystem::WriteData(char *buffer, int size, int location, int mode)
{
	int blocknumber = (size + BLOCK - 1) / BLOCK;
	for (int i = 0; i < blocknumber; i++)
	{
		if (index->ModificationIndexNumber != -1)
		{
			index->ModificationIndexList[index->ModificationIndexNumber++] = location;
		}
		if (mode == 0 || i != blocknumber - 1)
		{
			fileOperator->MoveBlock(location);
			fileOperator->Write(buffer + i * BLOCK, BLOCK);
			index->Array[location] = -1;
			int nextlocation = index->FindEmptyBlock();
			index->Array[location] = nextlocation;
			location = nextlocation;
		}
		else
		{
			fileOperator->MoveBlock(location);
			fileOperator->Write(buffer + i * BLOCK, (size - 1) % BLOCK + 1);
			index->Array[location] = -1;
		}
	}
	return location;
}
int FileSystem::Export(const char *filename,const char*path)
{
	if (!fileOperator->OpenFile(path)) return 1;
	fileOperator->CreatFile(path);
	int dirnum = GetDirNum(filename);
	if (dirnum == -1)
		return -1;
	if (directory->File[dirnum].state != 1)
		return -1;
	int size = directory->File[dirnum].size;
	char *buffer = (char *)malloc(size < (MAXBUFFERSIZE) ? size : (MAXBUFFERSIZE));
	int location = directory->File[dirnum].location;
	for (int i = 0; i < (size + (MAXBUFFERSIZE) - 1) / (MAXBUFFERSIZE); i++)
	{
		if (i != (size - 1) / (MAXBUFFERSIZE))
		{
			location = ReadData(buffer, (MAXBUFFERSIZE), location, 0);
			fileOperator->WriteFile(buffer, (MAXBUFFERSIZE));
		}
		else
		{
			ReadData(buffer, (size - 1) % (MAXBUFFERSIZE) + 1, location, -1);
			fileOperator->WriteFile(buffer, (size - 1) % (MAXBUFFERSIZE) + 1);
		}
	}
	free(buffer);
	fileOperator->CloseFile();
	return 0;
}
int FileSystem::ReadData(char *buffer, int size, int location, int mode)
{
	int blocknumber = (size + BLOCK - 1) / BLOCK;
	for (int i = 0; i < blocknumber; i++)
	{
		if (mode == 0 || i != blocknumber - 1)
		{
			fileOperator->MoveBlock(location);
			fileOperator->Read(buffer + i * BLOCK, BLOCK);
			location = index->Array[location];
		}
		else
		{
			fileOperator->MoveBlock(location);
			fileOperator->Read(buffer + i * BLOCK, (size - 1) % BLOCK + 1);
			location = -1;
		}
	}
	return location;
}
int FileSystem::recursionCopy(int number, int aim)
{
	if (directory->Tree[number].state == 1)
	{
		return CopyFile(number, aim);
	}
	else if (directory->Tree[number].state == 2)
	{
		int newdir = CopyDir(number, aim);
		int temp;
		list<int>::iterator it = directory->Tree[number].child.begin();
		list<int>::iterator end = directory->Tree[number].child.end();
		while (it != end)
		{
			temp=recursionCopy(*it++, newdir);
			if (temp == -1)
				return -1;
		}
		return 0;
	}
	return 0;
}
int FileSystem::CopyDir(int number, int aim)
{
	int emptydirectory = directory->FindEmpty();
	FileInfo info(2, directory->File[number].name, directory->File[number].extension, 0, 0, aim);
	directory->Add(info);
	return emptydirectory;
}
int FileSystem::CopyFile(int number, int aim)
{
	int size = directory->File[number].size;
	int blocknumber = (size + BLOCK - 1) / BLOCK;
	if (blocknumber > index->FreeBlockNumber) return -1;//空间不足
	index->FreeBlockNumber -= blocknumber;
	index->ModificationIndexNumber = -1;
	char *buffer = (char *)malloc(size < (MAXBUFFERSIZE) ? size : (MAXBUFFERSIZE));
	int readlocation = directory->File[number].location;
	int firstsavelocation = index->FindEmptyBlock();
	int savelocation = firstsavelocation;
	for (int i = 0; i < (size + (MAXBUFFERSIZE)-1) / (MAXBUFFERSIZE); i++)
	{
		if (i != (size - 1) / (MAXBUFFERSIZE))
		{
			readlocation = ReadData(buffer, (MAXBUFFERSIZE), readlocation, 0);
			savelocation = WriteData(buffer, (MAXBUFFERSIZE), savelocation, 0);
		}
		else
		{
			readlocation = ReadData(buffer, (size - 1) % (MAXBUFFERSIZE)+1, readlocation, -1);
			savelocation = WriteData(buffer, (size - 1) % (MAXBUFFERSIZE)+1, savelocation, -1);
		}
	}
	int emptydirectory = directory->FindEmpty();
	FileInfo info(1, directory->File[number].name, directory->File[number].extension, firstsavelocation, size, aim);
	directory->Add(info);

	free(buffer);
	return 0;
}
int FileSystem::Copy(const char * original, const  char * aim)
{
	int numberfile = GetDirNum(original);
	if (numberfile == -1) return -1;
	int numberorder = GetDirNum(aim);
	if (numberorder == -1) return -1;
	if (directory->File[numberorder].state != 2 && directory->File[numberorder].state != 3)
		return -2;
	char wholename[13] = { 0 };
	splitSlash(wholename, const_cast<char*>(original));
	char name[8] = { 0 };
	char extension[3] = { 0 };
	splitName(name, extension, wholename);
	if (directory->Search(name, extension, numberorder) != -1)
		return -3;
	if (recursionCopy(numberfile, numberorder) == -1)
		return -4;
	fileOperator->MovePoint(INDEXLOCATION);
	fileOperator->Write(index->Array, BLOCKNUMBER * INDEX);
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(directory->File, directory->FileNumber * DIRECTORY);
	fileOperator->Flush();
	return 0;
}
int FileSystem::MakeDir(const char * dir)
{
	int emptydirectory = directory->FindEmpty();
	char name[10];
	splitSlash(name, const_cast<char*>(dir));
	int parentnumber = getParentNumber(const_cast<char*>(dir));
	if (parentnumber <0)
		return -2;
	char extension[3] = { 0 };
	if (directory->Search(name, extension, parentnumber) != -1)
		return -1;
	FileInfo info(2, name, extension, -1, 0, parentnumber);
	directory->Add(info);
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(directory->File, directory->FileNumber * DIRECTORY);
	fileOperator->Flush();
	return emptydirectory;
}
int FileSystem::Delete(const char * path)
{
	int nownumber = GetDirNum(path);
	if (nownumber == -1) return -1;
	directory->Tree[directory->Tree[nownumber].parent].child.remove(nownumber);
	recursionDelete(nownumber);
	fileOperator->MovePoint(INDEXLOCATION);
	fileOperator->Write(index->Array, BLOCKNUMBER * INDEX);
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(directory->File, directory->FileNumber * DIRECTORY);
	fileOperator->Flush();
	//Tree[Tree[number].parent].child.remove(number);
	/*char nametemp[8], extensiontemp[3];
	splitName(nametemp, extensiontemp, path);
	directory->Delete(directory->Search(nametemp, extensiontemp, 0));*/
	return 0;
}
int FileSystem::recursionDelete(int number)
{
	if (directory->Tree[number].state == 3)
		return -1;
	else if (directory->Tree[number].state == 0)
		return 0;
	else if (directory->Tree[number].state == 1)
	{
		int location = directory->File[number].location;
		index->NowBlockLocation = location;
		int temp;
		while (location >= 0)
		{
			temp = index->Array[location];
			index->Array[location] = 0;
			location = temp;
		}
		index->FreeBlockNumber -= (directory->File[number].size + BLOCK - 1) / BLOCK;
		index->Array[location] = 0;
		directory->Delete(number);
		return 1;
	}
	else
	{
		for (list<int>::iterator it = directory->Tree[number].child.begin(); it != directory->Tree[number].child.end();)
		{
			recursionDelete(*it);
			it = directory->Tree[number].child.erase(it);
		}
		directory->Delete(number);
	}
}
int FileSystem::Attrib(const char* path)
{
	if (*path == '\0')//const char*和""不相等，和NULL也不相等
		directory->ShowAtt(nowDirNum);
	else
		directory->ShowAtt(GetDirNum(path));
	return 0;
}
int FileSystem::Tree(const char* path)//可以添加对树排序的功能
{
	if (*path == '\0')//const char*和""不相等，和NULL也不相等
		directory->ShowTree(nowDirNum);
	else
		directory->ShowTree(GetDirNum(path));
	return 0;
}
int FileSystem::Dir(const char* path)
{
	if (*path == '\0')//const char*和""不相等，和NULL也不相等
		directory->ShowDir(nowDirNum);
	else
		directory->ShowDir(GetDirNum(path));
	return 0;
}
int FileSystem::CDDir(char * aim)
{
	int temp = GetDirNum(aim);
	if (temp == -1)
		return -1;
	nowDirNum = temp;
	setNowPath(nowDirNum);
	return 1;
}
int FileSystem::Map(const char * path)
{
	Word tmp;
	int number = GetDirNum(path);
	if (number == -1) return -1;
	int location = directory->File[number].location;
	int cnt = 0;
	while (location != -1)
	{
		cnt++;
		tmp.setClr(13);
		cout.width(8);
		cout << left<<location ;
		if (cnt % 10 == 0)
			cout << endl;
		location = index->Array[location];
	}
	cout << endl;
	return 1;
}
int FileSystem::Move(const char * path, const char * aim)
{
	int number = GetDirNum(path);
	if (number == -1) return -1;
	int aimnumber = GetDirNum(aim);
	if (aimnumber == -1) return -1;

	char wholename[13] = { 0 };
	splitSlash(wholename, const_cast<char*>(path));
	char name[8] = { 0 };
	char extension[3] = { 0 };
	splitName(name, extension, wholename);
	if (directory->Search(name, extension, aimnumber) != -1)
		return -2;

	directory->Move(number, aimnumber);
	fileOperator->MovePoint(DIRECTORYLOCTION);
	fileOperator->Write(directory->File, directory->FileNumber * DIRECTORY);
	return 1;
}
