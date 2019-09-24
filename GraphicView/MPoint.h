#pragma once
class MPoint
{
public:
	MPoint();
	~MPoint();

public:
	int num; //表示该点编号
	float fx;
	float fy;
	float fz;
	int ix; 
	int iy;
	int iz;
	float showx;
	float showy;
	float showz; //显示在Label上的坐标点
	int status; //-2为删除、-1为选中确认、1为初始状态、2为新增点
	int lineNum;
	int parent; //记录点结构的父节点
	bool isLook; //是否被查看过
};

