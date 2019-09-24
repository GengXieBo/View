#pragma once
#include <vector>
#include <map>
#include <fstream>
#include "MLog.h"
#include "MPoint.h"
#include "TiffSet.hpp"
using namespace std;

typedef vector<MPoint> line;
typedef vector<MPoint> points;

class TxtHelper
{
public:
	TxtHelper();
	bool readPointFile(string fileName, map<int, vector<MPoint> > &);
	void saveLinePoints();
	bool openLineFile(string fileName);
	
	line getCurrentLine();
	points getCurrentLinePoints();

	void setLinePoints(int lineNum, std::vector<MPoint>);
	void setCurrentLine(int lineNum);

	bool preLine();
	bool nextLine();

	vector<string> splitString(string line, string split);
	map<int, line> getLines();

	void closeLine();

	~TxtHelper();

	bool isLineOpen;
	int lineCounts;
	int currentLineNum;

private:
	map<int, line> lines;
	map<int, points> linePoints;
	MPoint boundPoints[2];
	string fileName;
};

