#include "QImageLabel.h"


QImageLabel::QImageLabel(QWidget * parent) : QLabel(parent)
{
	this->setAutoFillBackground(true); // enable us can change the background
	QPalette label_palette = this->palette();
	label_palette.setColor(QPalette::Window, Qt::lightGray);   //change the background 
	this->setPalette(label_palette);
	this->setEnabled(true);

	setMouseTracking(true);
	b_mouse_left_button_clicked = false;
	b_mouse_right_button_clicked = false;

	showLineFlag = true;
	showPointFlag = true;
	
	showImageBounding = 100;
	f_zoom_step = 0.5;
	f_zoom_ratio_max = 4;
	f_zoom_ratio_min = 1;

	showPointRadius = 2;
	showLineRadius = 1;

	mappingMin = 0;
	mappingMax = 255;

	mappingFlag = 0;

	img = nullptr;

}

void QImageLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);
	QPainter painter(this);
	if (img != nullptr)
	{
		QImage tempImg = img->copy();
		int c;
		for (int x = 0; x < tempImg.width(); x++)
		{
			for (int y = 0; y < tempImg.height(); y++)
			{
				c = tempImg.pixelColor(x, y).red();
				if (c < mappingMin)
				{
					tempImg.setPixelColor(QPoint(x, y), qRgb(0, 0, 0));
				}
				else if (c > mappingMax)
				{
					tempImg.setPixelColor(QPoint(x, y), qRgb(255, 255, 255));
				}
				else
				{
					if (mappingFlag == 0)
					{
						c = float(c - mappingMin) / (mappingMax - mappingMin) * mappingMax;
					}
					else
					{
						c = float(c - mappingMin) / (mappingMax - mappingMin) * (255 - mappingMin) + mappingMin;
					}
					tempImg.setPixelColor(QPoint(x, y), qRgb(c, c, c));
				}
			}
		}
		tempImg = tempImg.scaled(QSize(showImageWidth, showImageHeight), Qt::IgnoreAspectRatio);
		painter.drawImage(QPoint(showImageX , showImageY) , tempImg);

		if (showLineFlag)
		{
			drawLine(painter);
		}

		if (showPointFlag)
		{
			drawPoints(painter);
		}
	}
}

// destructor
QImageLabel::~QImageLabel() {

}

void QImageLabel::initImage()
{
	if (this->b_is_front_image_opened)
	{
		// zoom parameter
		f_zoom_current_scale = 1.0;

		// get a image copy and show the image
		QImage qimage_temp = img->copy();

		QImage * qimage_scaled = new QImage;
		*qimage_scaled = qimage_temp.scaled(QSize(this->width(), this->height()), Qt::IgnoreAspectRatio);
		this->setPixmap(QPixmap::fromImage(*qimage_scaled));
		delete qimage_scaled;

		// reset parameters about show image
		f_zoom_current_scale = 1;
	}
}

void QImageLabel::setImage(QImage *img, std::vector<MPoint> l, std::vector<MPoint> p, std::vector<MPoint> boundPoints)
{

	if (this->img != nullptr) //设置之前进行内存的释放
	{
		delete this->img;
		this->img = nullptr;
	}

	if (img != nullptr)
	{
		this->img = img;
		b_is_front_image_opened = true;
		
		//计算图像的放缩倍数
		float maxlen = img->width() > img->height() ? img->width() : img->height();
		imageRatio = this->width() / maxlen;

		showImageWidth = img->width() * imageRatio;
		showImageHeight = img->height() * imageRatio;

		showImageX = this->width() / 2 - showImageWidth / 2;
		showImageY = this->height() / 2 - showImageHeight / 2;

		f_zoom_ratio_min = imageRatio; //最小的缩小倍数即为开始时所显示的倍数

		this->l = l;
		this->p = p;
		this->boundPoints = boundPoints;

		repaint();
	}
	else
	{
		this->b_is_front_image_opened = false ;
		this->clear();
	}
}


void QImageLabel::showImage()
{
	// test if qimage_front_image is not opened
	if (img == NULL) {
		return;
	}

	// show image 
	QImage qimage_temp = img->copy();

	// judge if the start_x or start_y is legal
	if (showImageX + this->width() > this->width() * f_zoom_current_scale) {
		showImageX = this->width()*f_zoom_current_scale - this->width() - 1;
	}
	if (showImageY + this->height() > this->height()*f_zoom_current_scale) {
		showImageY = this->height()*f_zoom_current_scale - this->height() - 1;
	}

	QImage * qimage_scaled = new QImage;
	//图像的裁切操作
	*qimage_scaled = qimage_temp.scaled(QSize(this->width()*f_zoom_current_scale, this->height()*f_zoom_current_scale),
		Qt::IgnoreAspectRatio).copy(showImageX, showImageY, this->width(), this->height());
	this->setPixmap(QPixmap::fromImage(*qimage_scaled));
	delete qimage_scaled;
}


void QImageLabel::mouseReleaseEvent(QMouseEvent *evt)
{
	qDebug() << "in function ClickedLabel mouse release" << endl;
	emit MouseRelease(evt);

	//change the flag
	if (evt->button() == Qt::LeftButton) {
		b_mouse_left_button_clicked = false;
	}
	else if (evt->button() == Qt::RightButton) {
		b_mouse_right_button_clicked = false;
	}

}


void QImageLabel::keyPressEvent(QKeyEvent *evt) {
	// listen to key press event
	qDebug() << "in function ClickedLabel key press" << endl;
	emit KeyPressed(evt);
}

/*进行鼠标移动事件的监听*/
void QImageLabel::mouseMoveEvent(QMouseEvent *event) {
	// case 1: front image is opened;
	if (b_is_front_image_opened) {
		int x = event->x();
		int y = event->y();
		//判断鼠标是否在图片范围内
		if (x >= showImageX && x < showImageX + showImageWidth && y >= showImageY && y < showImageY + showImageHeight)
		{
			emit mouseMoveInfo(x - showImageX, y - showImageY);
		}
		if (b_mouse_right_button_clicked) {
			i_mouse_new_position_x = x;
			i_mouse_new_position_y = y;
			translateImage();
		}
	}
}

void QImageLabel::mousePressEvent(QMouseEvent *event) {
	// case1 : front image is opened
	if (b_is_front_image_opened) 
	{
		//判断鼠标点击的位置是否在图片范围内
		int x = event->x();
		int y = event->y();

		if (x >= showImageX && x < showImageX + showImageWidth && y >= showImageY && y < showImageY + showImageHeight)
		{
			if (event->button() == Qt::LeftButton) 
			{
				b_mouse_left_button_clicked = true;
				mouseLeftClickReponse(x, y);

			}
			else if (event->button() == Qt::RightButton) 
			{
				// translate image
				b_mouse_right_button_clicked = true;
				i_mouse_last_position_x = event->x();
				i_mouse_last_position_y = event->y();
			}
		}
	}
}


void QImageLabel::mouseDoubleClickEvent(QMouseEvent *event) {
	qDebug() << "in function mouseDoubleClickEvent" << endl;
	emit MouseDoubliClick(event);
}

void QImageLabel::wheelEvent(QWheelEvent *event) {
	qDebug() << "in function wheelEvent" << endl;
	emit WheelEvent(event);

	int x = event->x();
	int y = event->y();
	int min_x = showImageX < 0 ? 0 : showImageX;
	int min_y = showImageY < 0 ? 0 : showImageY;
	if (x >= min_x && x < showImageX + showImageWidth && y >= min_y && y < showImageY + showImageHeight) //首先判断鼠标是否在图像上
	{
		if (b_is_front_image_opened)
		{
			float f_degree_delta = event->delta() * 1.0 / 640;
			float preImageRatio = imageRatio;
			if (imageRatio + f_degree_delta > f_zoom_ratio_max || imageRatio + f_degree_delta < f_zoom_ratio_min) {
				return;
			}
			
			imageRatio += f_degree_delta;


			showImageWidth = img->width() * imageRatio;
			showImageHeight = img->height() * imageRatio;


			float relativeX = (x - showImageX) / preImageRatio * imageRatio;
			float relativeY = (y - showImageY) / preImageRatio * imageRatio;

			showImageX = x - relativeX;
			showImageY = y - relativeY;

				
			repaint();
		}
	}

}

void QImageLabel::translateImage()
{
	int i_distance = (i_mouse_new_position_x - i_mouse_last_position_x)*(i_mouse_new_position_x - i_mouse_last_position_x) + 
					 (i_mouse_new_position_y - i_mouse_last_position_y)*(i_mouse_new_position_y - i_mouse_last_position_y) ;
	if (i_distance < 50) {
		return;
	}

	// compute the delta
	int i_delta_x = i_mouse_new_position_x - i_mouse_last_position_x;
	int i_delta_y = i_mouse_new_position_y - i_mouse_last_position_y;


	// start x exceeds the left edge
	if (showImageX + i_delta_x < showImageBounding - showImageWidth) {
		showImageX = showImageBounding - showImageWidth;

	}
	else if (this->width() - showImageX - i_delta_x < showImageBounding)
	{
		showImageX = this->width() - showImageBounding;
	}
	else {
		showImageX += i_delta_x;
	}

	// start y exceeds the top edge
	if (showImageY + i_delta_y < showImageBounding - showImageHeight) {
		showImageY = showImageBounding - showImageHeight;

	}
	else if (this->height() - showImageY - i_delta_y < showImageBounding) {
		showImageY = this->height() - showImageBounding;
	}
	else {
		showImageY += i_delta_y;
	}

	i_mouse_last_position_x = i_mouse_new_position_x;
	i_mouse_last_position_y = i_mouse_new_position_y;

	repaint();
}

void QImageLabel::drawLine(QPainter &painter)
{
	painter.setPen(QPen(Qt::red, showLineRadius));
	int px1, py1, px2, py2;
	for (int i = 0; i < l.size() - 1; i++)
	{
		px1 = (l[i].fx - boundPoints[0].fx) * imageRatio + showImageX;
		py1 = (l[i].fy - boundPoints[0].fy) * imageRatio + showImageY;

		px2 = (l[i + 1].fx - boundPoints[0].fx) * imageRatio + showImageX;
		py2 = (l[i + 1].fy - boundPoints[0].fy) * imageRatio + showImageY;

		painter.drawLine(QPoint(px1 , py1), QPoint(px2 , py2));
	}
}

void QImageLabel::drawPoints(QPainter &painter)
{
	int px, py;
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i].status != -2)
		{
			p[i].showx = (p[i].fx - boundPoints[0].fx) * imageRatio + showImageX;
			p[i].showy = (p[i].fy - boundPoints[0].fy) * imageRatio + showImageY;
			painter.setPen(QPen(Qt::blue, showPointRadius * imageRatio));
			if (p[i].status == 2)
			{
				painter.setPen(QPen(Qt::red, showPointRadius * imageRatio));
			}
			painter.drawEllipse(QPoint(p[i].showx, p[i].showy), int(showPointRadius * imageRatio), int(showPointRadius * imageRatio));
			if (p[i].status == -1)
			{
				painter.setPen(QPen(Qt::red, 2));
				painter.drawEllipse(QPoint(p[i].showx, p[i].showy), int(showPointRadius * imageRatio) + 1 , int(showPointRadius * imageRatio) + 1);
			}
		}
	}
}

void QImageLabel::mouseLeftClickReponse(int x, int y)
{
	switch (mouseData.getMouseStatus())
	{
	case 0:
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i].status != -2)
			{
				int dis = sqrt(pow(p[i].showx - x, 2) + pow(p[i].showy - y, 2));
				if (dis < 3)
				{
					p[i].status = -1; //设置为确认状态
				}
			}
		}
		break;
	case 1:
		{
			MPoint newPoint;
			newPoint.lineNum = l[0].lineNum; //设置线段编号
			newPoint.fx = (x - showImageX) / imageRatio + boundPoints[0].fx;
			newPoint.fy = (y - showImageY) / imageRatio + boundPoints[0].fy;
			
			//计算新增点的z方向坐标
			float minDis = 10000;
			int index = 0;
			for (int i = 0; i < l.size(); i++)
			{
				float dis = pow(newPoint.fx - l[i].fx, 2) + pow(newPoint.fy - l[i].fy, 2);
				if (dis < minDis)
				{
					minDis = dis;
					index = i;
				}
			}
			newPoint.fz = l[index].fz;
			newPoint.status = 2; //设置为新增点
			newPoint.parent = -1;
			p.push_back(newPoint);
		}
		break;
	case 2:
		for (int i = 0; i < p.size(); i++)
		{
			int dis = sqrt(pow(p[i].showx - x, 2) + pow(p[i].showy - y, 2));
			if (dis < 3)
			{
				p[i].status = -2; //将该点设置为删除状态
			}
		}
		break;
	default:
		break;
	}
	repaint();
}


std::vector<MPoint> QImageLabel::getCurrentLinePoints()
{
	if (this->b_is_front_image_opened)
	{
		return p;
	}
	else
	{
		return std::vector<MPoint>();
	}
}

void QImageLabel::setMapping(int min, int max , int flag)
{
	if (this->b_is_front_image_opened)
	{
		if (min >= 0 && max <= 255 && min <= max)
		{
			mappingMin = min;
			mappingMax = max;
			mappingFlag = flag;
			repaint();
		}
	}
}

void QImageLabel::changeShowLineState(bool state)
{
	showLineFlag = state;
	repaint();
}

void QImageLabel::changeShowPointState(bool state)
{
	showPointFlag = state;
	repaint();
}
