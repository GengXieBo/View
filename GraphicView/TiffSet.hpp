#ifndef TIFFSET_H
#define TIFFSET_H
#include <string>
/*---����һЩtiffͼƬ���õĶ���---*/
#define TIFF_WIDTH 256 //��ȡ��Ŀ�
#define TIFF_HEIGHT 256 //��ȡ��ĸ�
#define TIFF_Z_R 10 //��ȡ��ĺ�Ȱ뾶

/*---ͼƬ���е�ͼƬ��Ϣ---*/
#define TIFF_BLOCK_WIDTH 512 //��
#define TIFF_BLOCK_HEIGHT 512 //��
#define TIFF_BLOCK_FRAMES 512 //֡��
#define TIFF_BLOCK_BITSPERSAMPLE 2 //ͼ��ÿ�����ص���ռ���ֽ���

/*---����tiff��洢��·��---*/
//class _TIFF_PATH //��֤����ȫ��ֻ��һ��
//{
//public :
//	static std::string TIFF_PATH;
//};

/*����tiff��Ļ�������С*/
#define MAX_BLOCKS 10 //�ȶ��建���СΪ10

/*����tiff������С�ķ�������*/
#define MAX_TIFF_SCALE 2.5
#define MIN_TIFF_SCALE 1

/*����ͼƬ��ɫ�ռ��ӳ�䷶Χ*/
#define MIN_TIFF_MAPPING 0
#define MAX_TIFF_MAPPING 255

/*����QImageLabel��С*/
#define QIMAGE_LABEL_WIDTH 600
#define QIMAGE_LABEL_HEIGHT 600

/*����ÿ����ͶӰ�İ뾶*/
#define	POINT_BLOCK_RADIUS 8
#endif