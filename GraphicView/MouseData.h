#pragma once
class MouseData
{
public:
	MouseData();
	void setMouseStatus(int mouseData);
	int getMouseStatus();
	~MouseData();
	bool imageFlag; //�жϵ�ǰ�Ƿ����ͼƬ
private:
	int mouseStatus; //�洢��굱ǰ��״̬
};

