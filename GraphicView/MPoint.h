#pragma once
class MPoint
{
public:
	MPoint();
	~MPoint();

public:
	int num; //��ʾ�õ���
	float fx;
	float fy;
	float fz;
	int ix; 
	int iy;
	int iz;
	float showx;
	float showy;
	float showz; //��ʾ��Label�ϵ������
	int status; //-2Ϊɾ����-1Ϊѡ��ȷ�ϡ�1Ϊ��ʼ״̬��2Ϊ������
	int lineNum;
	int parent; //��¼��ṹ�ĸ��ڵ�
	bool isLook; //�Ƿ񱻲鿴��
};

