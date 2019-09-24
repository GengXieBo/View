#ifndef TIFFSET_H
#define TIFFSET_H
#include <string>
/*---进行一些tiff图片设置的定义---*/
#define TIFF_WIDTH 256 //读取块的宽
#define TIFF_HEIGHT 256 //读取块的高
#define TIFF_Z_R 10 //读取块的厚度半径

/*---图片库中的图片信息---*/
#define TIFF_BLOCK_WIDTH 512 //宽
#define TIFF_BLOCK_HEIGHT 512 //高
#define TIFF_BLOCK_FRAMES 512 //帧数
#define TIFF_BLOCK_BITSPERSAMPLE 2 //图像每个像素点所占的字节数

/*---定义tiff块存储的路径---*/
//class _TIFF_PATH //保证变量全局只有一份
//{
//public :
//	static std::string TIFF_PATH;
//};

/*设置tiff块的缓冲区大小*/
#define MAX_BLOCKS 10 //先定义缓冲大小为10

/*设置tiff最大和最小的放缩比例*/
#define MAX_TIFF_SCALE 2.5
#define MIN_TIFF_SCALE 1

/*设置图片颜色空间的映射范围*/
#define MIN_TIFF_MAPPING 0
#define MAX_TIFF_MAPPING 255

/*设置QImageLabel大小*/
#define QIMAGE_LABEL_WIDTH 600
#define QIMAGE_LABEL_HEIGHT 600

/*设置每个点投影的半径*/
#define	POINT_BLOCK_RADIUS 8
#endif