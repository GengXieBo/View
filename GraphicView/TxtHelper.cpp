#include "TxtHelper.h"


TxtHelper::TxtHelper()
{
	this->isLineOpen = false;
}


bool TxtHelper::readPointFile(string fileName, map<int , vector<MPoint> > &l)
{
	ifstream lineFile(fileName);
	if (!lineFile.is_open())
	{
		MLog::log("debug", "TxtPointHelper:readPointFile", fileName + " open failed ... ");
		return false;
	}
	string line;
	vector<string> uints;
	while (getline(lineFile, line))
	{
		uints = splitString(line, "\t");
		if (uints.size() != 7) //判断数据是否合格
		{
			return false;
		}
		MPoint p;
		p.num = atoi(uints[0].data());
		p.status = atoi(uints[1].data());
		p.fx = atof(uints[2].data()) / 0.2;
		p.fy = atof(uints[3].data()) / 0.2;
		p.fz = atof(uints[4].data());
		p.lineNum = atoi(uints[5].data());
		p.parent = atoi(uints[6].data());
		if (p.fx < 0 || p.fx > TIFF_BLOCK_WIDTH * 60 || p.fy < 0 || p.fy > TIFF_BLOCK_HEIGHT * 96 || p.fz < 0 || p.fz > TIFF_BLOCK_FRAMES * 16) //判断坐标是否溢出
		{
			return false;
		}
		l[p.lineNum].push_back(p);
	}
	lineFile.close();
	return true;
}

/*进行字符串的裁剪*/
vector<string> TxtHelper::splitString(string line, string split)
{
	vector<string> uints;
	int index;
	while ((index = line.find_first_of(split)) != -1)
	{
		uints.push_back(line.substr(0, index));
		line = line.substr(index + 1);
	}
	uints.push_back(line);
	return uints;
}

map<int, line> TxtHelper::getLines()
{
	if (isLineOpen)
	{
		return lines;
	}
	return map<int, line>();
}

bool TxtHelper::openLineFile(string lineFileName)
{
	if (!lineFileName.empty())
	{
		int pointIndex = lineFileName.find_last_of(".");
		string name = lineFileName.substr(0, pointIndex);
		fileName = name; //进行文件名的设置
		string linePointFileName = name + ".p";
		string plinePointFileName = name + ".pl";

		if (readPointFile(lineFileName, lines))
		{
			if (readPointFile(plinePointFileName, linePoints))
			{
				isLineOpen = true;
				currentLineNum = 1;
				lineCounts = lines.size();
				return true;
			}
			else if (readPointFile(linePointFileName, linePoints))
			{
				isLineOpen = true;
				currentLineNum = 1;
				lineCounts = lines.size();
				return true;
			}
			isLineOpen = false;
			return false;
		}
		else
		{
			isLineOpen = false;
			return false;
		}
	}
	else
	{
		isLineOpen = false;
		MLog::log("debug", "TxtPointHelper:openLineFile", "file name can not be empty ... ");
		return false;
	}
}

line TxtHelper::getCurrentLine()
{
	if (isLineOpen)
	{
		return lines[currentLineNum];
	}
	else
	{
		MLog::log("debug", "TxtPointHelper:getCurrentLine", "there is no line open ... ");
		return vector<MPoint>() ;
	}
}
points TxtHelper::getCurrentLinePoints()
{
	if (isLineOpen)
	{
		return linePoints[currentLineNum];
	}
	else
	{
		MLog::log("debug", "TxtPointHelper:getCurrentLinePoints", "there is no line open ... ");
		return vector<MPoint>();
	}
}

void TxtHelper::setCurrentLine(int lineNum)
{
	currentLineNum = lineNum;
}

void TxtHelper::setLinePoints(int lineNum, std::vector<MPoint> points)
{
	if (isLineOpen)
	{
		linePoints[lineNum] = points;
	}
}

bool TxtHelper::preLine()
{
	if (isLineOpen)
	{
		currentLineNum = (currentLineNum - 1) > 0 ? (currentLineNum - 1) : lineCounts ;
		return true;
	}
	else
	{
		MLog::log("debug", "TxtPointHelper:preLine", "there is no line open ... ");
		return false;
	}
}
bool TxtHelper::nextLine()
{
	if (isLineOpen)
	{
		currentLineNum = (currentLineNum + 1) > lineCounts ? 1 : (currentLineNum + 1) ;
		return true;
	}
	else
	{
		MLog::log("debug", "TxtPointHelper:nextLine", "there is no line open ... ");
		return false;
	}
}

void TxtHelper::closeLine()
{
	isLineOpen = false;
	lines.clear();
	linePoints.clear();
}

void TxtHelper::saveLinePoints()
{
	ofstream linePointsFile;
	linePointsFile.open(fileName + ".pl");
	int num = 0;
	for (int i = 1; i <= lineCounts; i++)
	{
		for (int j = 0; j < linePoints[i].size(); j++)
		{
			linePointsFile << (num++) << "\t" << linePoints[i][j].status << "\t" << linePoints[i][j].fx / 5.0 << "\t" << linePoints[i][j].fy / 5.0 << "\t"
				<< linePoints[i][j].fz << "\t" << linePoints[i][j].lineNum << "\t" << linePoints[i][j].parent << endl;
		}
	}
	linePointsFile.close();
}


TxtHelper::~TxtHelper()
{
}
