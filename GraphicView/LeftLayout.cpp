#include "LeftLayout.h"

LeftLayout::LeftLayout(QWidget *parent)
	: QWidget(parent)
{
	setUi();

	QObject::connect(lineNumEdit, SIGNAL(returnPressed()), this, SLOT(slotLineNumChanged()));
	QObject::connect(miniMap, SIGNAL(setProgressBarValue(int)), this, SLOT(progressBarChanged(int)));

	//进行图片映射的设置
	QObject::connect(minTiffMappingSpinBox, SIGNAL(valueChanged(int)), minTiffMappingSlider, SLOT(setValue(int)));
	QObject::connect(minTiffMappingSlider, SIGNAL(valueChanged(int)), minTiffMappingSpinBox, SLOT(setValue(int)));
	QObject::connect(minTiffMappingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(minTiffMappingChanged(int)));
	minTiffMappingSpinBox->setValue(0);

	QObject::connect(maxTiffMappingSpinBox, SIGNAL(valueChanged(int)), maxTiffMappingSlider, SLOT(setValue(int)));
	QObject::connect(maxTiffMappingSlider, SIGNAL(valueChanged(int)), maxTiffMappingSpinBox, SLOT(setValue(int)));
	QObject::connect(maxTiffMappingSpinBox, SIGNAL(valueChanged(int)), this, SLOT(maxTiffMappingChanged(int)));
	maxTiffMappingSpinBox->setValue(255);

	QObject::connect(miniMap, SIGNAL(setProgressBarValue(int)), this, SLOT(progressBarChanged(int)));

}

void LeftLayout::setLineCountLabel(string lineCount)
{
	this->lineNumLabel->setText(lineCount.data());
}

void LeftLayout::mousePressEvent(QMouseEvent *event)
{

}

void LeftLayout::progressBarChanged(int value)
{
	progressBar->setValue(value);
}


/*tiff图片投影的下限改变*/
void LeftLayout::minTiffMappingChanged(int min)
{
	int maxValue = maxTiffMappingSpinBox->value();
	//限制下边界的投影值，不允许超过上边界
	if (min > maxValue)
	{
		minTiffMappingSpinBox->setValue(maxValue);
	}
	emit tiffMappingChanged(min, maxValue , 0);
}
/*tiff图片投影的上限改变*/
void LeftLayout::maxTiffMappingChanged(int max)
{
	//获得tiff投影的下限值
	int minValue = minTiffMappingSpinBox->value();
	//设置上边界的值，不允许低于下边界
	if (max < minValue)
	{
		maxTiffMappingSpinBox->setValue(minValue);
	}
	emit tiffMappingChanged(minValue, max , 1);
}

void LeftLayout::slotShowMiniMap(bool isShow)
{
	//此处只是消息的中转站
	miniMap->changeMiniMapShowState(isShow);
}


void LeftLayout::slotLineNumChanged()
{
	string txt = lineNumEdit->text().toStdString();
	if (txt != "")
	{
		int lineNum = atoi(txt.data());
		emit lineNumChanged(lineNum);
	}
}

void LeftLayout::setLineNumBoxValue(int value)
{
	this->lineNumEdit->setText(TimeShare::dataToString(value).data());
}

LeftLayout::~LeftLayout()
{

}


void LeftLayout::setUi()
{

	currentLineNum = new QLabel("current line num : ");

	lineNumLabel = new QLabel("");
	lineNumEdit = new QLineEdit();
	lineNumEdit->setValidator(new QIntValidator(0, 100000 , this));

	label1 = new QLabel();
	QVBoxLayout *vBoxLayout = new QVBoxLayout(label1);
	QHBoxLayout *hBoxLayout = new QHBoxLayout();

	hBoxLayout->addWidget(currentLineNum);
	hBoxLayout->addWidget(lineNumEdit);
	hBoxLayout->addWidget(lineNumLabel);
	hBoxLayout->setStretchFactor(currentLineNum, 3);
	hBoxLayout->setStretchFactor(lineNumEdit, 2);
	hBoxLayout->setStretchFactor(lineNumLabel, 2);

	vBoxLayout->addLayout(hBoxLayout);

	QLabel *dividLine = new QLabel("---------------------------------------");
	QHBoxLayout *hLayout = new QHBoxLayout();
	hLayout->addWidget(dividLine , Qt::AlignCenter);

	vBoxLayout->addLayout(hLayout);

	//在此处进行映射滑动条的初始化
	QHBoxLayout *hBoxLayout1 = new QHBoxLayout();
	QHBoxLayout *hBoxLayout2 = new QHBoxLayout();

	this->minValueLabel = new QLabel("min:");
	this->maxValueLabel = new QLabel("max:");

	this->minTiffMappingSlider = new QSlider(Qt::Horizontal);
	this->minTiffMappingSpinBox = new QSpinBox();
	this->maxTiffMappingSlider = new QSlider(Qt::Horizontal);
	this->maxTiffMappingSpinBox = new QSpinBox();

	this->minTiffMappingSlider->setRange(0, 255);
	this->minTiffMappingSpinBox->setRange(0, 255);
	this->maxTiffMappingSlider->setRange(0, 255);
	this->maxTiffMappingSpinBox->setRange(0, 255);

	hBoxLayout1->addWidget(minValueLabel);
	hBoxLayout1->addWidget(minTiffMappingSpinBox);
	hBoxLayout1->addWidget(minTiffMappingSlider);

	hBoxLayout1->setStretchFactor(minValueLabel, 1);
	hBoxLayout1->setStretchFactor(minTiffMappingSpinBox, 1);
	hBoxLayout1->setStretchFactor(minTiffMappingSlider, 4);



	hBoxLayout2->addWidget(maxValueLabel);
	hBoxLayout2->addWidget(maxTiffMappingSpinBox);
	hBoxLayout2->addWidget(maxTiffMappingSlider);

	hBoxLayout2->setStretchFactor(maxValueLabel, 1);
	hBoxLayout2->setStretchFactor(maxTiffMappingSpinBox, 1);
	hBoxLayout2->setStretchFactor(maxTiffMappingSlider, 4);

	vBoxLayout->addLayout(hBoxLayout1);
	vBoxLayout->addLayout(hBoxLayout2);

	QVBoxLayout *tempvBoxLayout = new QVBoxLayout();
	miniMap = new MiniMap(this);
	miniMap->setStyleSheet("border:1px solid white");
	tempvBoxLayout->addWidget(miniMap);
	vBoxLayout->addLayout(tempvBoxLayout);

	progressBar = new QProgressBar(this);
	progressBar->setRange(0, 100);
	vBoxLayout->addWidget(progressBar);

	vBoxLayout->setStretchFactor(hBoxLayout, 1);
	vBoxLayout->setStretchFactor(hLayout, 1);
	vBoxLayout->setStretchFactor(hBoxLayout1, 1);
	vBoxLayout->setStretchFactor(hBoxLayout2, 1);
	vBoxLayout->setStretchFactor(tempvBoxLayout, 8);
	vBoxLayout->setStretchFactor(progressBar, 1);


	stack = new QStackedWidget(this);
	stack->addWidget(label1);

	QVBoxLayout *downLayout = new QVBoxLayout(this);

	downLayout->addWidget(stack);
	downLayout->setStretchFactor(stack, 5);
}
