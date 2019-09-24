#pragma once
#include <string>
#include "tiffio.h"
#include <qdebug.h>
#include <thread>
#include <QtWidgets/QWidget>
#include <vector>
#include <string>
#include <thread>
#include "MPoint.h"
#include "TiffSet.hpp"
#include "TimeShare.hpp"
#include "MPoint.h"
#include "MLog.h"
#include "SharedGlobalVariable.h"
#include "ReadBlockThread.h"
class TiffHelper
{
public:
	TiffHelper();
	QImage* getImgByLine(std::vector<MPoint>, std::vector<MPoint> &boundPoints); //返回左上角与右下角坐标
	~TiffHelper();
private:
	void identifyMostDNumber(MPoint ps[], int t[]);
	void readFramesThread(TIFF *tiff, uint16** buffer, int sf, int ef, int width, int height, int totalFrame);
	QImage* getProjectionImg(std::vector<MPoint> points, MPoint ps[], int t[]);
	bool readTiffByPath(std::string path, uint16 **buffer);
	bool saveTiffByPath(std::string path, uint16* buffer, int size[]);
	static void releaseImgData(uint16 ***img_data, int width, int height);
};

