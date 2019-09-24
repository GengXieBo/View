#pragma once
#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <string>
#include <sstream>
using namespace std;
/*系统获取工具*/
class TimeShare
{
public:
	TimeShare(){}
	static string getPath(string TIFF_PATH , int ix , int iy , int iz)
	{
		return TIFF_PATH + "z" + dataToString(iz) + "/y" + dataToString(iy) + "/" +
			dataToString(ix) + "_" + dataToString(iy) + "_" + dataToString(iz) + ".tif";
	}
	static void outputCurrentSystemTime()
	{
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		printf("%4d/%02d/%02d %02d:%02d:%02d.%03d week%1d\n",
			sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
	}
	static string getWorkDirectory()
	{
		char *buffer;
		//也可以将buffer作为输出参数
		if ((buffer = getcwd(NULL, 0)) == NULL)
		{
			perror("getcwd error");
		}
		return string(buffer);
	}
	static string dataToString(float data)
	{
		stringstream ss;
		ss << data;
		return ss.str();
	}
	~TimeShare(){}
};