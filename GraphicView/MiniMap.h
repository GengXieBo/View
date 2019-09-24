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
	void paintEvent(QPaintEvent *event); //����С��ͼ
	static void getMiniMapFromFile(void *mini);
	void getLineByPoint();
	void startThread();
	void clear();
	void changeMiniMapShowState(bool isShow); //�ı�minimap����ʾ״̬
	bool event(QEvent *e); //��д�¼����պ���
	static void loadMiniMapThread(void *mini);
	QVector<string> splitString(string line, string split); //���ж�ȡ�ִ��Ĳü�

	~MiniMap();

	QImage miniMapImage;
	QImage tempMapImage;
	QReadWriteLock lock;
private:
	PaintMiniThread *paintMiniThread;
	QVector<QLine> lines; //��¼�ɵ�õ�����
	int progressValue;
	std::thread *t1; //�˴��洢�߳�
	std::thread *t2; //��ȡminimap���߳�

	bool ifShowMiniMap; //���ӱ�־λ���Ƿ����С��ͼ����ʾ
	bool isExitImg; //�Ƿ����ͼƬ�ı�־λ

	QVector<QPoint> relativePoints;

signals:
	void setProgressBarValue(int value);
	void locatePoint(MPoint p);
};

#endif // MINIMAP_H
