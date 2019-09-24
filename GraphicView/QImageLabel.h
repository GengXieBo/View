#pragma once
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <vector>
#include "MPoint.h"
#include "MLog.h"
#include "SharedGlobalVariable.h"

class QImageLabel : public QLabel {
	Q_OBJECT
	signals :
	void MouseRelease(QMouseEvent *evt);
	void KeyPressed(QKeyEvent *evt);
	void MouseMoved(QMouseEvent* evt);
	void MousePressed(QMouseEvent* evt);
	void MouseDoubliClick(QMouseEvent* evt);
	void WheelEvent(QWheelEvent* evt);
	void mouseMoveInfo(int x, int y);

public:
	QImageLabel(QWidget * parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *event);
	void showImage();
	void setImage(QImage *img, std::vector<MPoint> , std::vector<MPoint> , std::vector<MPoint>);
	void initImage();
	void translateImage();
	void changeShowLineState(bool);
	void changeShowPointState(bool);
	std::vector<MPoint> getCurrentLinePoints();

	void drawLine(QPainter &painter);
	void drawPoints(QPainter &painter);

	void mouseLeftClickReponse(int x, int y);

	~QImageLabel();

	//线与点
	std::vector<MPoint> l;
	std::vector<MPoint> p;
	int showPointRadius;
	int showLineRadius;
	//边界
	std::vector<MPoint> boundPoints;

	//图片的动态属性
	int showImageWidth ;
	int showImageHeight ;

	// image show start x, start y
	int showImageX ;
	int showImageY;

	// image zoom in ratio
	float imageRatio;

	// zoom parameter
	float f_zoom_step;
	float f_zoom_ratio_max;
	float f_zoom_ratio_min;
	float f_zoom_current_scale;


	// QImage front image pointer
	QImage* img;
	bool b_is_front_image_opened;

	// bool variable
	bool is_translate_image;
	int i_mouse_last_position_x;
	int i_mouse_last_position_y;
	int i_mouse_new_position_x;
	int i_mouse_new_position_y;
	bool b_mouse_right_button_clicked;
	bool b_mouse_left_button_clicked;

	int showImageBounding;

	int mappingMin;
	int mappingMax;

	bool showLineFlag;
	bool showPointFlag;

	int mappingFlag;

protected:
	void mouseReleaseEvent(QMouseEvent*);  // listen to mouse event
	void mousePressEvent(QMouseEvent*);  // listen to mouse event
	void mouseMoveEvent(QMouseEvent*);  // listen to mouse event
	void keyPressEvent(QKeyEvent *);  // listen to key press event
	void mouseDoubleClickEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

	public slots:
	void setMapping(int min, int max , int flag);

};
