#pragma once
#include <ctime>

class Time
{
public:
	static int date()
	{
		time_t timep;
		struct tm *p;
		std::time(&timep);
		p = localtime(&timep);
		return 10000 * (1900 + p->tm_year) + 100 * (1 + p->tm_mon) + p->tm_mday;
	}

	static int time()
	{
		time_t timep;
		struct tm *p;
		std::time(&timep);
		p = localtime(&timep);
		return 10000 * p->tm_hour + 100 * p->tm_min + p->tm_sec;
	}
};