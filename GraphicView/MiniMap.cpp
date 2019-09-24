#include "minimap.h"

int mutexV = 1;
int clickIndex = -1;

MiniMap::MiniMap(QWidget *parent)
	: QLabel(parent)
{
	progressValue = 0;
	ifShowMiniMap = false;
	isExitImg = false;
	t2 = nullptr;
}

void MiniMap::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	if (ifShowMiniMap)
	{
		QMutex mutex;
		QPainter painter(this);
		MLog::log("debug", "MiniMap:paintEvent", "before draw the minimap ... ");
		QPoint p(0, 0);
		if (tempMapImage.width() > this->width())
		{
			tempMapImage = tempMapImage.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation); //����ƽ����ͼƬ����,ʹͼ����Ӧ����ʾ���
		}
		else
		{
			p.setX(this->width() / 2 - tempMapImage.width() / 2);
			p.setY(this->height() / 2 - tempMapImage.height() / 2);
		}
		painter.drawImage(p, tempMapImage);
	}
}
/*�˴�����С��ͼ�ļ��أ����ڵ�̫�༴�����̲߳���*/
void MiniMap::getMiniMapFromFile(void *mini)
{
	MiniMap *miniMap = (MiniMap*)mini;
	float minBoundingX;
	float maxBoundingX;
	float minBoundingY;
	float maxBoundingY;
	minBoundingX = minBoundingY = 9999999;
	maxBoundingX = maxBoundingY = 0;
	map<int, line> lines = txtHelper.getLines();
	int count = 0;
	//��֮ǰ�����ҵ��������Сֵ
	for (int i = 1; i <= txtHelper.lineCounts; i++)
	{
		for (int j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j].fx >  maxBoundingX)
			{
				maxBoundingX = lines[i][j].fx;
			}
			else if (lines[i][j].fx <  minBoundingX)
			{
				minBoundingX = lines[i][j].fx;
			}
			if (lines[i][j].fy > maxBoundingY)
			{
				maxBoundingY = lines[i][j].fy;
			}
			else if (lines[i][j].fy <  minBoundingY)
			{
				minBoundingY = lines[i][j].fy;
			}
			count++;
		}
	}
	int imgSize = 3072;
	QImage tempImg(imgSize, imgSize, QImage::Format_ARGB32);
	//���л��ʵĳ�ʼ���������еĵ���Ƶ�QImage��
	QPainter painter(&tempImg);
	int currentX, currentY;
	//���пռ䷶Χ��ӳ��
	miniMap->setPixmap(QPixmap::fromImage(QImage()));
	miniMap->relativePoints.clear();
	int k = 0;
	for (int i = 1; i <= txtHelper.lineCounts; i++)
	{
		for (int j = 0; j < lines[i].size(); j++)
		{
			if (mutexV == 0)
			{
				return;
			}
			int x = ((lines[i][j].fx - minBoundingX) / float(maxBoundingX - minBoundingX)) * 3071;
			int y = ((lines[i][j].fy - minBoundingY) / float(maxBoundingY - minBoundingY)) * 3071;

			painter.setPen(QPen(Qt::blue, 1));
			if (lines[i][j].lineNum == txtHelper.currentLineNum)
			{
				painter.setPen(QPen(Qt::red, 4));
				painter.drawEllipse(QPoint(x, y), 4, 4);
			}
			painter.drawEllipse(QPoint(x, y), 1, 1);
			k++;
			miniMap->relativePoints.push_back(QPoint((float)x / imgSize * miniMap->width(), (float)y / imgSize * miniMap->height()));
			int ratio = float(k) / float(count) * 100 + 1;
			MEvent me(QEvent::Type(QEvent::User + 1)); //�����¼��Ĵ���
			me.setValue(ratio);
			QApplication::postEvent(miniMap, new MEvent(me));
		}
	}
	MLog::log("debug", "MiniMap:getMiniMapFromFile", "complete draw img ... ");
	//������ɺ������Ϣ������
	MEvent me(QEvent::Type(QEvent::User + 2));
	me.setImg(tempImg);
	QApplication::postEvent(miniMap, new MEvent(me));//����ͼƬ��Ϣ�ķ���
}


void MiniMap::startThread()
{
	mutexV = 0;
	if (t2 != nullptr)
	{
		t2->join();
	}
	mutexV = 1;
	t2 = new std::thread(getMiniMapFromFile, this);
}

void MiniMap::clear()
{
	mutexV = 0;
	ifShowMiniMap = false;
	repaint();
}

QVector<string> MiniMap::splitString(string line, string split)
{
	QVector<string> uints;
	int index;
	while ((index = line.find_first_of(split)) != -1)
	{
		uints.push_back(line.substr(0, index));
		line = line.substr(index + 1);
	}
	uints.push_back(line);
	return uints;
}


bool MiniMap::event(QEvent *e)
{
	switch (e->type())
	{
	case QEvent::User + 1:
	{
		MEvent *me = (MEvent*)e;
		progressValue = me->getValue();
		emit setProgressBarValue(progressValue);
		return 0;
	}
	break;
	case QEvent::User + 2:
	{
		MEvent *me = (MEvent*)e;
		tempMapImage = me->getImg();
		MLog::log("debug", "MiniMap:event", "recieve the message User 2 ... ");
		repaint(); //�˴��������»���
		return 0;
	}
	default:
		break;
	}
	return QLabel::event(e);
}


void MiniMap::changeMiniMapShowState(bool isShow)
{
	MLog::log("debug", "MiniMap::changeMiniMapShowState", "show show show ... ");
	if (isShow)
	{
		ifShowMiniMap = true;
		startThread();
	}
	else
	{
		ifShowMiniMap = false;
		repaint();
	}
}

MiniMap::~MiniMap()
{
	
}
