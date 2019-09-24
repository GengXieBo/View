/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qlabel.h>
#include <QtCore\qdebug.h>
#include <QtWidgets\qboxlayout.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QWheelEvent>
#include "QImageLabel.h"
#include "LeftLayout.h"

QT_BEGIN_NAMESPACE

class Ui_ViewClass
{
public:
	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QStatusBar *statusBar;
	QWidget *centralWidget;

	QMenu *menuFile; //文件
	QMenu *menuSet; //设置

	QAction *actionFileOpen;
	QAction *actionFileClose;

	QAction *actionSetTiffPath; //设置tiff块路径
	QAction *actionShowMiniMap; //设置是否进行小地图的绘制
	QAction *actionShowLine;
	QAction *actionShowPoint;

	QAction *actionPaintTool;
	QAction *actionChooseTool;
	QAction *actionDeleteTool;
	QAction *actionMouseTool;
	QAction *actionPreLineTool;
	QAction *actionNextLineTool;

	QHBoxLayout *hBoxLayout; //中间控件的布局

	LeftLayout *leftLayout;
	QImageLabel *imageLabel; //进行图片显示的QLabel

	//在此处显示tiff的帧数信息
	QLabel *tiffLevelInfoLabel;

	void setupUi(QMainWindow *ViewClass)
	{
		if (ViewClass->objectName().isEmpty())
			ViewClass->setObjectName(QStringLiteral("ViewClass"));
		ViewClass->setFixedSize(1000, 800);
		menuBar = new QMenuBar(ViewClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		ViewClass->setMenuBar(menuBar);

		menuFile = new QMenu("file");
		actionFileOpen = new QAction("open", menuFile);
		actionFileClose = new QAction("close", menuFile);
		menuFile->addAction(actionFileOpen);
		menuFile->addAction(actionFileClose);

		menuSet = new QMenu("set");

		actionSetTiffPath = new QAction("set tiff path", menuSet);

		actionShowMiniMap = new QAction("show minimap", menuSet);
		actionShowMiniMap->setCheckable(true);
		actionShowMiniMap->setChecked(false); //默认为不显示状态

		actionShowLine = new QAction("show line", menuSet);
		actionShowLine->setCheckable(true);
		actionShowLine->setChecked(true);

		actionShowPoint = new QAction("show point", menuSet);
		actionShowPoint->setCheckable(true);
		actionShowPoint->setChecked(true);


		menuSet->addAction(actionSetTiffPath);
		menuSet->addAction(actionShowMiniMap);
		menuSet->addAction(actionShowLine);
		menuSet->addAction(actionShowPoint);

		menuBar->addMenu(menuFile);
		menuBar->addMenu(menuSet);

		mainToolBar = new QToolBar(ViewClass);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));

		actionPaintTool = new QAction(QIcon(":/GraphicView/Resources/paint.png"), "paint", mainToolBar);
		actionDeleteTool = new QAction(QIcon(":/GraphicView/Resources/delete.png"), "delete", mainToolBar);
		actionMouseTool = new QAction(QIcon(":/GraphicView/Resources/click.png"), "click", mainToolBar);
		actionPreLineTool = new QAction(QIcon(":/GraphicView/Resources/pre.png"), "prePoint(ctr+z)", mainToolBar);
		actionNextLineTool = new QAction(QIcon(":/GraphicView/Resources/next.png"), "nextPoint(ctr+x)", mainToolBar);

		mainToolBar->addAction(actionMouseTool);
		mainToolBar->addAction(actionPaintTool);
		mainToolBar->addAction(actionDeleteTool);
		mainToolBar->addAction(actionPreLineTool);
		mainToolBar->addAction(actionNextLineTool);

		ViewClass->addToolBar(mainToolBar);
		statusBar = new QStatusBar(ViewClass);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		ViewClass->setStatusBar(statusBar);

		//界面的初始化与更新
		leftLayout = new LeftLayout(ViewClass);
		leftLayout->resize(300, 600);

		imageLabel = new QImageLabel(ViewClass);
		imageLabel->resize(600, 600);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(leftLayout);
		hBoxLayout->addWidget(imageLabel);

		hBoxLayout->setStretchFactor(leftLayout, 1);
		hBoxLayout->setStretchFactor(imageLabel, 2);

		centralWidget = new QWidget();
		centralWidget->resize(900, 600);
		centralWidget->setLayout(hBoxLayout);
		ViewClass->setCentralWidget(centralWidget);

		tiffLevelInfoLabel = new QLabel(ViewClass);
		tiffLevelInfoLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
		tiffLevelInfoLabel->setText("tiff level info");
		statusBar->addPermanentWidget(tiffLevelInfoLabel);//显示永久信息


		retranslateUi(ViewClass);

		QMetaObject::connectSlotsByName(ViewClass);
	} // setupUi

	void retranslateUi(QMainWindow *ViewClass)
	{
		ViewClass->setWindowTitle(QApplication::translate("ViewClass", "View", 0));
	} // retranslateUi

};

namespace Ui {
	class ViewClass : public Ui_ViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
