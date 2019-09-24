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
			//���п����ݵĸ���
			PTiffBlock tempTiffBlock = new TiffBlock();
			tempTiffBlock->buffer = tiffBlock->buffer;
			tempTiffBlock->next = NULL;
			tempTiffBlock->pre = NULL;
			tempTiffBlock->x = tiffBlock->x;
			tempTiffBlock->y = tiffBlock->y;
			tempTiffBlock->z = tiffBlock->z;

			tiffBlockManager.addBlock(tempTiffBlock); //���ÿ�����ڴ�
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
	TIFF *tiff = TIFFOpen(path.data(), "r"); //��ֻ���ķ�ʽ���ļ�
	if (tiff == NULL) //�ļ���ȡʧ����ֱ�ӷ���
	{
		qDebug() << path.data() << " read failed ... ";
		return false;
	}

	int width, height, totalFrame;
	TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height); //���ÿһ֡�ĳ������
	totalFrame = TIFFNumberOfDirectories(tiff); //���ͼ�����֡��

	uint16 bitsPerSample, samplePerPixel; //֮�������õ�
	TIFFGetField(tiff, TIFFTAG_BITSPERSAMPLE, &bitsPerSample);//�˴��õ���Ϊÿһ�������ֳ�
	TIFFGetField(tiff, TIFFTAG_SAMPLESPERPIXEL, &samplePerPixel); //ÿ������ռ���ٻ�����

	int compressionTag = 0; //�õ�ѹ����ʽ
	TIFFGetField(tiff, TIFFTAG_COMPRESSION, &compressionTag); //��Ȼ��ѹ����ʽ����Ҫ�ı��ȡ�����ݵķ�ʽ
	//qDebug() << "compressionTag : " << compressionTag;

	//���ÿ������ռ����bit
	uint16 bitsPerPixel = bitsPerSample * samplePerPixel;
	int stripSize = 0;
	stripSize = TIFFStripSize(tiff); //���ͼ���ÿһ֡�����ظ���
	if (bitsPerPixel == 16) //����ͼ���ÿ�����ص���ռbitλ�ֱ����ͼ�����ݵĶ�ȡ
	{
		tiffBlock->buffer = new uint16[totalFrame * stripSize]; //����洢ͼ����ڴ�ռ�
		int N_size = 0;
		for (int s = 0; s < totalFrame; s++)
		{
			//MLog::log("debug", "TiffHelepr:readTiffFromPathToTiffBlock", "N_size : " + TimeShare::dataToString(N_size));
			for (int row = 0; row < height; row++)
			{
				TIFFReadScanline(tiff, tiffBlock->buffer + N_size + row*int(width), row); //��ø��еĵ�ַ�����ҽ��а��ж�ȡ
			}
			N_size += width * height;
			TIFFReadDirectory(tiff); //����ÿһҳ�Ķ��룬����ҳ
		}
	}
	TIFFClose(tiff);
	return true;
}

ReadBlockThread::~ReadBlockThread()
{

}
