#include "paintminithread.h"

PaintMiniThread::PaintMiniThread(QObject *parent)
	: QThread(parent)
{

}

void PaintMiniThread::setPainter(QPainter *painter)
{
	this->painter = painter;
}

void PaintMiniThread::run()
{
	for (int i = 10; i < 200; i += 5)
	{
		painter->drawEllipse(QPoint(i, i), 2, 2);
	}
}

PaintMiniThread::~PaintMiniThread()
{

}
