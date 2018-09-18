#include "FileOperator.h"

FileOperator::FileOperator()
{

}


FileOperator::~FileOperator()
{

}

//创建Minifs
void FileOperator::Create(const char *filename)
{
	minifs = fopen(filename, "wb");
	MinifsPointLocation = 0;
}

//打开minifs，成功为0，失败为1
int FileOperator::Open(const char *filename)
{
	minifs = fopen(filename, "rb+");
	if (minifs == NULL) return 1;
	else
	{
		MinifsPointLocation = 0;
		return 0;
	}
}

//关闭文件指针
void FileOperator::Close()
{
	fclose(minifs);
}

//移动文件指针到块的位置
void FileOperator::MoveBlock(int blocknumber)
{
	MovePoint(BLOCKLOCATION + (blocknumber - 1) * BLOCK);
}

//移动文件指针
void FileOperator::MovePoint(int pointlocation)
{
	if (pointlocation >= SYSTEM || pointlocation < 0) return;
	fseek(minifs, pointlocation - MinifsPointLocation, SEEK_CUR);
	MinifsPointLocation = pointlocation;
}

//读取数据
void FileOperator::Read(void *buffer, int size)
{
	if (size <= 0 || MinifsPointLocation + size > SYSTEM) return;
	fread(buffer, 1, size, minifs);
	MinifsPointLocation += size;
}

//写入数据
void FileOperator::Write(void *buffer, int size)
{
	if (size <= 0 || MinifsPointLocation + size > SYSTEM) return;
	fwrite(buffer, 1, size, minifs);
	MinifsPointLocation += size;
}

//创建文件
void FileOperator::CreatFile(const char *filename)
{
	file = fopen(filename, "wb");
	FilePointLocation = 0;
}

//返回1：打开失败；返回0：打开成功
int FileOperator::OpenFile(const char *filename)
{
	file = fopen(filename, "rb");
	if (file == NULL) return 1;
	else
	{
		FilePointLocation = 0;
		return 0;
	}
}

//关闭文件
void FileOperator::CloseFile()
{
	fclose(file);
}

int FileOperator::FileSize()
{
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return size;
}

void FileOperator::ReadFile(void *buffer, int size)
{
	fread(buffer, 1, size, file);
}

void FileOperator::WriteFile(void *buffer, int size)
{
	fwrite(buffer, 1, size, file);
}
void FileOperator::Flush()
{
	fflush(minifs);
}


