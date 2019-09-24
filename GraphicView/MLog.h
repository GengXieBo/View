#pragma once
#include <iostream>
#include <string>
#include "TimeShare.hpp"
using namespace std;
extern int mutualI;
class MLog
{
public:
	MLog();
	static void log(string level, string position, string info);
	~MLog();
};

