#ifndef LEFTLAYOUT_H
#define LEFTLAYOUT_H

#include <QObject>
#include <QtWidgets\qwidget.h>
#include <QtWidgets\qstackedwidget.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qlistwidget.h>
#include <QtWidgets\qboxlayout.h>
#include <QtWidgets\qpushbutton.h>
#include <qdebug.h>
#include <QtWidgets\qspinbox.h>
#include <QtWidgets\qprogressbar.h>
#include <iostream>
#include <QLineEdit>
#include "TimeShare.hpp"
#include "MPoint.h"
#include "MiniMap.h"

class LeftLayout : public QWidget
{
	Q_OBJECT

public:
	LeftLayout(QWidget *parent);
	void setUi();
	void mousePressEvent(QMouseEvent *event);
	void setLineCountLabel(string lineCount);
	void setLineNumBoxValue(int value);
	~LeftLayout();

	public slots:
	void progressBarChanged(int value);
	void slotLineNumChanged();
	void minTiffMappingChanged(int min); //图片投影下限改变
	void maxTiffMappingChanged(int max); //图片投影上限改变
	void slotShowMiniMap(bool isShow);

private:
	QListWidget *list;
	QStackedWidget *stack;
	QLabel *label1;

	//定义显示的线条
	QLabel *currentLineNum;
	QLabel *lineNumLabel;
	QLineEdit *lineNumEdit;

	//定义图像投影映射的滑动条
	QLabel *minValueLabel;
	QSlider *minTiffMappingSlider;
	QSpinBox *minTiffMappingSpinBox;

	QLabel *maxValueLabel;
	QSlider *maxTiffMappingSlider;
	QSpinBox *maxTiffMappingSpinBox;

	MiniMap *miniMap;

	QProgressBar *progressBar;
signals:
	void lineNumChanged(int n);
	void tiffMappingChanged(int min, int max , int flag);
};

#endif // LEFTLAYOUT_H
