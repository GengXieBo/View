#pragma once
#include "qmainwindow.h"
#include "ui_View.h"
#include "TxtHelper.h"
#include "TiffHelper.h"
#include "MouseData.h"
#include "SharedGlobalVariable.h"
class View :public QMainWindow
{
	Q_OBJECT
public:
	View();

	void showLineOperate();
	void keyPressEvent(QKeyEvent *event);
	void setToolbarStatus(int mouseStatus);
	~View();


private:
	Ui::ViewClass ui;

	//Helper
	TiffHelper tiffHelper;

	//Attributes
	line lines;
	points linePoints;
	std::vector<MPoint> boundPoints;

	//是否进行小地图的显示
	bool isShowMiniMap;

	private slots:
	// slots
	void slotOpenLineFile();
	void slotCloseLineFile();
	void slotNextLine();
	void slotPreLine();
	void slotPaintActionTool();
	void slotDeleteActionTool();
	void slotChooseActionTool();
	void closeEvent(QCloseEvent *event);
	void slotSetTiffPath();
	void slotLineNumChanged(int lineNum);
	void slotShowMiniMap();
	void slotShowLine();
	void slotShowPoint();
	void mousePositionChangedStatus(int x, int y);

	signals:
	void showMiniMap(bool showState);
};

