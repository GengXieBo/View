#include "MouseData.h"


MouseData::MouseData()
{
	mouseStatus = 0;
	imageFlag = false;
}


MouseData::~MouseData()
{
}

void MouseData::setMouseStatus(int mouseData)
{
	this->mouseStatus = mouseData;
}

int MouseData::getMouseStatus()
{
	return mouseStatus;
}
