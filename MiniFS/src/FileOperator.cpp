#include "FileOperator.h"

FileOperator::FileOperator()
{

}


FileOperator::~FileOperator()
{

}

//����Minifs
void FileOperator::Create(const char *filename)
{
	minifs = fopen(filename, "wb");
	MinifsPointLocation = 0;
}

//��minifs���ɹ�Ϊ0��ʧ��Ϊ1
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

//�ر��ļ�ָ��
void FileOperator::Close()
{
	fclose(minifs);
}

//�ƶ��ļ�ָ�뵽���λ��
void FileOperator::MoveBlock(int blocknumber)
{
	MovePoint(BLOCKLOCATION + (blocknumber - 1) * BLOCK);
}

//�ƶ��ļ�ָ��
void FileOperator::MovePoint(int pointlocation)
{
	if (pointlocation >= SYSTEM || pointlocation < 0) return;
	fseek(minifs, pointlocation - MinifsPointLocation, SEEK_CUR);
	MinifsPointLocation = pointlocation;
}

//��ȡ����
void FileOperator::Read(void *buffer, int size)
{
	if (size <= 0 || MinifsPointLocation + size > SYSTEM) return;
	fread(buffer, 1, size, minifs);
	MinifsPointLocation += size;
}

//д������
void FileOperator::Write(void *buffer, int size)
{
	if (size <= 0 || MinifsPointLocation + size > SYSTEM) return;
	fwrite(buffer, 1, size, minifs);
	MinifsPointLocation += size;
}

//�����ļ�
void FileOperator::CreatFile(const char *filename)
{
	file = fopen(filename, "wb");
	FilePointLocation = 0;
}

//����1����ʧ�ܣ�����0���򿪳ɹ�
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

//�ر��ļ�
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


