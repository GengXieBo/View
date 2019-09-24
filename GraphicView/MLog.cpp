#include "MLog.h"
int mutualI = 1;
MLog::MLog()
{
}

void MLog::log(string level, string position, string info)
{
	while (mutualI < 1);
	mutualI--;
	cout << level << " " << position << " " << info << "\t";
	TimeShare::outputCurrentSystemTime();
	mutualI++;
}

MLog::~MLog()
{
}
