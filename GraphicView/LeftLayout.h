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
	void minTiffMappingChanged(int min); //ͼƬͶӰ���޸ı�
	void maxTiffMappingChanged(int max); //ͼƬͶӰ���޸ı�
	void slotShowMiniMap(bool isShow);

private:
	QListWidget *list;
	QStackedWidget *stack;
	QLabel *label1;

	//������ʾ������
	QLabel *currentLineNum;
	QLabel *lineNumLabel;
	QLineEdit *lineNumEdit;

	//����ͼ��ͶӰӳ��Ļ�����
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
