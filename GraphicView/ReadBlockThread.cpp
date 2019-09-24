#include "readblockthread.h"

ReadBlockThread::ReadBlockThread(QObject *parent) :QThread(parent)
{

}

void ReadBlockThread::setPath(string tiffPath, uint16 **buffer)
{
	this->tiffPath = tiffPath;
	this->buffer = buffer;
}

void ReadBlockThread::setTiffBlock(PTiffBlock tiffBlock)
{
	this->tiffBlock = tiffBlock;
}

void ReadBlockThread::run()
{
	TiffHelper tiffHelper;
	PTiffBlock temp = nullptr;
	temp = tiffBlockManager.getTiffBlock(tiffBlock->x, tiffBlock->y, tiffBlock->z);
	if (temp != NULL)
	{
		tiffBlock->buffer = temp->buffer;
	}
	else
	{
		string path = TIFF_PATH + "z" + TimeShare::dataToString(tiffBlock->z) + "/y" + TimeShare::dataToString(tiffBlock->y) + "/" +
			TimeShare::dataToString(tiffBlock->x) + "_" + TimeShare::dataToString(tiffBlock->y) + "_" + TimeShare::dataToString(tiffBlock->z) + ".tif";
		if (readTiffFromPathToTiffBlock(path, tiffBlock))
		{
			//进行块内容的复制
			PTiffBlock tempTiffBlock = new TiffBlock();
			tempTiffBlock->buffer = tiffBlock->buffer;
			tempTiffBlock->next = NULL;
			tempTiffBlock->pre = NULL;
			tempTiffBlock->x = tiffBlock->x;
			tempTiffBlock->y = tiffBlock->y;
			tempTiffBlock->z = tiffBlock->z;

			tiffBlockManager.addBlock(tempTiffBlock); //将该块加入内存
		}
		else
		{
			tiffBlock->tiffFlag = false;
		}
	}
	qDebug() << "thread done ... ";
}

bool ReadBlockThread::readTiffFromPathToTiffBlock(string path, PTiffBlock tiffBlock)
{
	TIFF *tiff = TIFFOpen(path.data(), "r"); //以只读的方式打开文件
	if (tiff == NULL) //文件读取失败则直接返回
	{
		qDebug() << path.data() << " read failed ... ";
		return false;
	}

	int width, height, totalFrame;
	TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height); //获得每一帧的长宽与高
	totalFrame = TIFFNumberOfDirectories(tiff); //获得图像的总帧数

	uint16 bitsPerSample, samplePerPixel; //之后计算会用到
	TIFFGetField(tiff, TIFFTAG_BITSPERSAMPLE, &bitsPerSample);//此处得到的为每一个机器字长
	TIFFGetField(tiff, TIFFTAG_SAMPLESPERPIXEL, &samplePerPixel); //每个像素占多少机器字

	int compressionTag = 0; //得到压缩形式
	TIFFGetField(tiff, TIFFTAG_COMPRESSION, &compressionTag); //果然有压缩形式，需要改变读取的数据的方式
	//qDebug() << "compressionTag : " << compressionTag;

	//算出每个像素占多少bit
	uint16 bitsPerPixel = bitsPerSample * samplePerPixel;
	int stripSize = 0;
	stripSize = TIFFStripSize(tiff); //获得图像的每一帧的像素个数
	if (bitsPerPixel == 16) //根据图像的每个像素点所占bit位分别进行图像数据的读取
	{
		tiffBlock->buffer = new uint16[totalFrame * stripSize]; //申请存储图像的内存空间
		int N_size = 0;
		for (int s = 0; s < totalFrame; s++)
		{
			//MLog::log("debug", "TiffHelepr:readTiffFromPathToTiffBlock", "N_size : " + TimeShare::dataToString(N_size));
			for (int row = 0; row < height; row++)
			{
				TIFFReadScanline(tiff, tiffBlock->buffer + N_size + row*int(width), row); //获得该行的地址，并且进行按行读取
			}
			N_size += width * height;
			TIFFReadDirectory(tiff); //进行每一页的读入，即翻页
		}
	}
	TIFFClose(tiff);
	return true;
}

ReadBlockThread::~ReadBlockThread()
{

}
