#include "MEvent.h"

MEvent::MEvent(Type type) :QEvent(type)
{

}


void MEvent::setValue(int value)
{
	this->value = value;
}

int MEvent::getValue()
{
	return value;
}

void MEvent::setImg(QImage img)
{
	this->img = img;
}

QImage MEvent::getImg()
{
	return img;
}

MEvent::~MEvent()
{

}
