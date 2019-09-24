#ifndef MINIMAP_H
#define MINIMAP_H

#include <QLabel>
#include <qpainter.h>
#include <string>
#include <fstream>
#include <QApplication>
#include <iostream>
#include <thread>
#include "TimeShare.hpp"
#include "MLog.h"
#include "SharedGlobalVariable.h"
#include "PaintMiniThread.h"
#include "MEvent.h"
#include <QtCore\qmutex.h>
#include <QtCore\qreadwritelock.h>
#include <Qt3DInput\qmouseevent.h>
#include "MPoint.h"
#include "SharedGlobalVariable.h"
using namespace std;
extern int mutexV;
extern int clickIndex;
typedef struct _PointNode
{
	int num;
	float x;
	float y;
	int parent;
} PointNode;

class MiniMap : public QLabel
{
	Q_OBJECT

public:
	MiniMap(QWidget *parent = 0);
	void paintEvent(QPaintEvent *event); //绘制小地图
	static void getMiniMapFromFile(void *mini);
	void getLineByPoint();
	void startThread();
	void clear();
	void changeMiniMapShowState(bool isShow); //改变minimap的显示状态
	bool event(QEvent *e); //重写事件接收函数
	static void loadMiniMapThread(void *mini);
	QVector<string> splitString(string line, string split); //进行读取字串的裁剪

	~MiniMap();

	QImage miniMapImage;
	QImage tempMapImage;
	QReadWriteLock lock;
private:
	PaintMiniThread *paintMiniThread;
	QVector<QLine> lines; //记录由点得到的线
	int progressValue;
	std::thread *t1; //此处存储线程
	std::thread *t2; //读取minimap的线程

	bool ifShowMiniMap; //增加标志位，是否进行小地图的显示
	bool isExitImg; //是否绘制图片的标志位

	QVector<QPoint> relativePoints;

signals:
	void setProgressBarValue(int value);
	void locatePoint(MPoint p);
};

#endif // MINIMAP_H
