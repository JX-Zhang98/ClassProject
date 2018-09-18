#include "FileInfo.h"

FileInfo::FileInfo()
{
	state = 0;
	name[0] = '\0';
	extension[0] = '\0';
}
FileInfo::FileInfo(char m_state, const char *m_name, const char *m_extension, int m_location, int m_size, int m_parent)
{
	state = m_state;
	for (int i = 0; i < 8; i++)
	{
		if (m_name[i] == '\0')
		{
			name[i] = '\0';
			break;
		}
		name[i] = m_name[i];
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_extension[i] == '\0')
		{
			extension[i] = '\0';
			break;
		}
		else
			extension[i] = m_extension[i];
	}
	location = m_location;
	size = m_size;
	parent = m_parent;
	time = Time::time();
	date = Time::date();
}
void FileInfo::ShowName()
{
	for (int i = 0; i < 8;i++)
	{
		if (name[i] == '\0')
		{
			break;
		}
		else
			putchar(name[i]);
	}
}
void FileInfo::ShowExtension()
{
	for (int i = 0; i < 3; i++)
	{
		if (extension[i] == '\0')
		{
			break;
		}
		else
			putchar(extension[i]);
	}
}


FileInfo::~FileInfo()
{

}

