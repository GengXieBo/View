#include "View.h"


View::View()
{
	ui.setupUi(this);

	boundPoints = std::vector<MPoint>(2);
	isShowMiniMap = false;
	setToolbarStatus(mouseData.getMouseStatus());
	//信号与槽
	connect(ui.actionFileOpen, SIGNAL(triggered()), this, SLOT(slotOpenLineFile()));
	connect(ui.actionFileClose, SIGNAL(triggered()), this, SLOT(slotCloseLineFile()));
	
	connect(ui.actionNextLineTool, SIGNAL(triggered()), this, SLOT(slotNextLine()));
	connect(ui.actionPreLineTool, SIGNAL(triggered()), this, SLOT(slotPreLine()));

	connect(ui.actionDeleteTool, SIGNAL(triggered()), this, SLOT(slotDeleteActionTool()));
	connect(ui.actionPaintTool, SIGNAL(triggered()), this, SLOT(slotPaintActionTool()));
	connect(ui.actionMouseTool, SIGNAL(triggered()), this, SLOT(slotChooseActionTool()));
	connect(ui.actionSetTiffPath, SIGNAL(triggered()), this, SLOT(slotSetTiffPath()));

	connect(ui.leftLayout, SIGNAL(tiffMappingChanged(int, int , int)), ui.imageLabel, SLOT(setMapping(int, int , int)));
	connect(ui.leftLayout, SIGNAL(lineNumChanged(int)), this, SLOT(slotLineNumChanged(int)));

	connect(ui.actionShowMiniMap, SIGNAL(triggered()), this, SLOT(slotShowMiniMap()));
	connect(this, SIGNAL(showMiniMap(bool)), ui.leftLayout, SLOT(slotShowMiniMap(bool)));

	connect(ui.actionShowPoint, SIGNAL(triggered()), this, SLOT(slotShowPoint()));
	connect(ui.actionShowLine, SIGNAL(triggered()), this, SLOT(slotShowLine()));

	connect(ui.imageLabel, SIGNAL(mouseMoveInfo(int, int)), this, SLOT(mousePositionChangedStatus(int, int)));
}


//打开前景图片
void View::slotOpenLineFile() 
{
	QString lineFileName = QFileDialog::getOpenFileName(this,
		tr("select line file"),
		".//",
		tr("Image (*.line *.l)"));

	if (txtHelper.openLineFile(lineFileName.toStdString())) 
	{
		ui.leftLayout->setLineCountLabel(TimeShare::dataToString(1) + "  --  " + TimeShare::dataToString(txtHelper.lineCounts));
		showLineOperate();
	}
	else 
	{
		QMessageBox::information(this , tr("info") , tr("you select no file!"));
	}
}

void View::slotLineNumChanged(int lineNum)
{
	if (txtHelper.isLineOpen)
	{
		if (lineNum >= 1 && lineNum <= txtHelper.lineCounts)
		{
			std::vector<MPoint> points = ui.imageLabel->getCurrentLinePoints();
			if (points.size() > 0)
			{
				txtHelper.setLinePoints(points[0].lineNum, points); //更改最后一条线的状态
			}
			txtHelper.setCurrentLine(lineNum);
			showLineOperate();
		}
	}
}

void View::closeEvent(QCloseEvent *event)
{
	slotCloseLineFile();
}

//进行图片的关闭
void View::slotCloseLineFile()
{
	if (txtHelper.isLineOpen)
	{
		std::vector<MPoint> points = ui.imageLabel->getCurrentLinePoints();
		if (points.size() > 0)
		{
			txtHelper.setLinePoints(points[0].lineNum, points); //更改最后一条线的状态
		}

		txtHelper.saveLinePoints(); //进行更改线段的保存
		txtHelper.closeLine();
		ui.imageLabel->setImage(nullptr, vector<MPoint>(), vector<MPoint>(), vector<MPoint>());

		txtHelper.isLineOpen = false;
		ui.leftLayout->setLineCountLabel("");
	}
}

void View::slotNextLine()
{
	if (txtHelper.nextLine())
	{
		std::vector<MPoint> points = ui.imageLabel->getCurrentLinePoints();
		if (points.size() > 0)
		{
			txtHelper.setLinePoints(points[0].lineNum, points);
		}
		showLineOperate();
	}
}

void View::slotPreLine()
{
	if (txtHelper.preLine())
	{
		std::vector<MPoint> points = ui.imageLabel->getCurrentLinePoints();
		if (points.size() > 0)
		{
			txtHelper.setLinePoints(points[0].lineNum, points);
		}
		showLineOperate();
	}
}

void View::slotPaintActionTool()
{
	mouseData.setMouseStatus(1);
	setToolbarStatus(mouseData.getMouseStatus());
}
void View::slotDeleteActionTool()
{
	mouseData.setMouseStatus(2);
	setToolbarStatus(mouseData.getMouseStatus());
}
void View::slotChooseActionTool()
{
	mouseData.setMouseStatus(0);
	setToolbarStatus(mouseData.getMouseStatus());
}

void View::showLineOperate()
{
	MLog::log("debug", "View::showLineOperate", "show a new image ...");
	
	ui.leftLayout->setLineNumBoxValue(txtHelper.currentLineNum);

	lines = txtHelper.getCurrentLine();
	linePoints = txtHelper.getCurrentLinePoints();
	QImage *img = tiffHelper.getImgByLine(lines, boundPoints);
	ui.imageLabel->setImage(img, lines, linePoints , boundPoints);

	emit showMiniMap(ui.actionShowMiniMap->isChecked()); //切换线段的时候会显示
}

/*设置工具栏状态*/
void View::setToolbarStatus(int mouseStatus)
{
	switch (mouseStatus)
	{
	case 0:
		this->setCursor(Qt::ArrowCursor);
		ui.actionMouseTool->setEnabled(false);
		ui.actionPaintTool->setEnabled(true);
		ui.actionDeleteTool->setEnabled(true);
		break;
	case 1:
		this->setCursor(Qt::PointingHandCursor);
		ui.actionMouseTool->setEnabled(true);
		ui.actionPaintTool->setEnabled(false);
		ui.actionDeleteTool->setEnabled(true);
		break;
	case 2:
		this->setCursor(Qt::CrossCursor);
		ui.actionMouseTool->setEnabled(true);
		ui.actionPaintTool->setEnabled(true);
		ui.actionDeleteTool->setEnabled(false);
		break;
	default:
		//do nothing
		break;
	}
}

/*设置tiff块路径的地址*/
void View::slotSetTiffPath()
{
	QString tiffDirectory = QFileDialog::getExistingDirectory(this, "tiff path set");
	if (tiffDirectory.isEmpty())
	{
		ui.statusBar->showMessage("tiff set failed ... ");
		return;
	}
	TIFF_PATH = tiffDirectory.toStdString() + "/";
	ui.statusBar->showMessage(("tiff path " + TIFF_PATH + " set success ... ").data());
}


void View::slotShowMiniMap()
{
	cout << "you clicked the show mini map ... " << endl;
	bool state = ui.actionShowMiniMap->isChecked();
	if (!txtHelper.isLineOpen)
	{
		ui.actionShowMiniMap->setChecked(!state);
		return;
	}
	emit showMiniMap(state);
}
void View::slotShowLine()
{
	bool state = ui.actionShowLine->isChecked();
	ui.imageLabel->changeShowLineState(state);
}
void View::slotShowPoint()
{
	bool state = ui.actionShowPoint->isChecked();
	ui.imageLabel->changeShowPointState(state);
}

/*设置状态栏的位置信息*/
void View::mousePositionChangedStatus(int x, int y)
{
	ui.statusBar->showMessage((string("current position : (") + TimeShare::dataToString(x) + string(" , ") + TimeShare::dataToString(y) + string(")")).data());
}

void View::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() == Qt::ControlModifier)
	{
		switch (event->key())
		{
		case Qt::Key_D:
			ui.actionShowLine->setChecked(!ui.actionShowLine->isChecked());
			ui.imageLabel->changeShowLineState(ui.actionShowLine->isChecked());
			break;
		case Qt::Key_F:
			ui.actionShowPoint->setChecked(!ui.actionShowPoint->isChecked());
			ui.imageLabel->changeShowPointState(ui.actionShowPoint->isChecked());
			break;
		default:
			break;
		}
	}
}


View::~View()
{
}
