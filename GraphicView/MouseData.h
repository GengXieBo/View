#pragma once
class MouseData
{
public:
	MouseData();
	void setMouseStatus(int mouseData);
	int getMouseStatus();
	~MouseData();
	bool imageFlag; //判断当前是否存在图片
private:
	int mouseStatus; //存储鼠标当前的状态
};

