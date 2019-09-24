#ifndef MEVENT_H
#define MEVENT_H

#include <QtCore\QEvent>
#include <QtGui\qimage.h>
/*主要负责信息的传递*/
class MEvent : public QEvent
{

public:
	MEvent(Type type);
	void setValue(int value);
	int getValue();
	void setImg(QImage img);
	QImage getImg();
	~MEvent();

private:
	int value;
	QImage img;
};

#endif // MEVENT_H
