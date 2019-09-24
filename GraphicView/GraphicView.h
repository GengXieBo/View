#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GraphicView.h"

class GraphicView : public QMainWindow
{
	Q_OBJECT

public:
	GraphicView(QWidget *parent = Q_NULLPTR);

private:
	Ui::GraphicViewClass ui;
};
