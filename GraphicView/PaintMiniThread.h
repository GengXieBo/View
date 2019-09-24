#ifndef PAINTMINITHREAD_H
#define PAINTMINITHREAD_H

#include <QThread>
#include <QPainter>

class PaintMiniThread : public QThread
{
	Q_OBJECT

public:
	PaintMiniThread(QObject *parent);
	void setPainter(QPainter *painter);
	void run();
	~PaintMiniThread();

private:
	QPainter *painter;
};

#endif // PAINTMINITHREAD_H
