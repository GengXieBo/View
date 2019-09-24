#include "TiffHelper.h"


TiffHelper::TiffHelper()
{
}

QImage* TiffHelper::getImgByLine(std::vector<MPoint> l, std::vector<MPoint> &boundPoints)
{
	MPoint pb[2];
	pb[0].fx = pb[0].fy = pb[0].fz = 9999999;
	pb[1].fx = pb[1].fy = pb[1].fz = 0;
	for (MPoint p : l)
	{
		if (p.fx < pb[0].fx)
		{
			pb[0].fx = p.fx;
		}
		if (p.fy < pb[0].fy)
		{
			pb[0].fy = p.fy;
		}
		if (p.fz < pb[0].fz)
		{
			pb[0].fz = p.fz;
		}
		if (p.fx > pb[1].fx)
		{
			pb[1].fx = p.fx;
		}
		if (p.fy > pb[1].fy)
		{
			pb[1].fy = p.fy;
		}
		if (p.fz > pb[1].fz)
		{
			pb[1].fz = p.fz;
		}
	}

	int t[3]; //分别得到三个方向的块数
	identifyMostDNumber(pb, t);

	boundPoints[0].fx = floor(pb[0].fx / TIFF_BLOCK_WIDTH) * TIFF_BLOCK_WIDTH;
	boundPoints[0].fy = floor(pb[0].fy / TIFF_BLOCK_HEIGHT) * TIFF_BLOCK_HEIGHT;
	boundPoints[0].fz = floor(pb[0].fz / TIFF_BLOCK_FRAMES) * TIFF_BLOCK_FRAMES;

	boundPoints[1].fx = boundPoints[0].fx + t[0] * TIFF_BLOCK_WIDTH - 1;
	boundPoints[1].fy = boundPoints[0].fy + t[1] * TIFF_BLOCK_HEIGHT - 1;
	boundPoints[1].fz = boundPoints[0].fz + t[2] * TIFF_BLOCK_FRAMES - 1;

	return getProjectionImg(l, pb, t);
}

QImage* TiffHelper::getProjectionImg(std::vector<MPoint> points, MPoint ps[], int t[])
{
	//此处建立投影画布,初始值默认为0
	QImage *img = new QImage(t[0] * TIFF_BLOCK_WIDTH , t[1] * TIFF_BLOCK_HEIGHT , QImage::Format_RGB888);
	img->fill(qRgb(0, 0, 0));

	//std::vector<uint16*> buffer(t[0] * t[1] * t[2]);
	vector<PTiffBlock> tiffBlocks; //存储每一个块的tiff块数据
	vector<ReadBlockThread*> readBlockThreads;
	int block_num = 0;
	for (int x = 0; x < t[0]; x++)
	{
		for (int y = 0; y < t[1]; y++)
		{
			int ix, iy, iz;
			ix = floor((ps[0].fx - 0.1) / TIFF_BLOCK_WIDTH) + x;
			iy = floor((ps[0].fy - 0.1) / TIFF_BLOCK_HEIGHT) + y;
			for (int z = 0; z < t[2]; z++)
			{
				iz = floor((ps[0].fz - 0.1) / TIFF_BLOCK_FRAMES) + z;
	/*			if (!readTiffByPath(blockPath, &(buffer[block_num++])))
				{
					for (int i = 0; i < block_num; i++)
					{
						delete buffer[i];
					}
					delete img;
					return nullptr;
				}*/
				PTiffBlock tiffBlock = new TiffBlock();
				tiffBlock->tiffFlag = true;
				tiffBlock->next = tiffBlock->pre = nullptr;
				tiffBlock->x = ix;
				tiffBlock->y = iy;
				tiffBlock->z = iz;
				tiffBlocks.push_back(tiffBlock);
				ReadBlockThread *readBlockThread = new ReadBlockThread(NULL);
				readBlockThreads.push_back(readBlockThread);
				readBlockThread->setTiffBlock(tiffBlock);
				readBlockThread->start();
			}
		}
	}

	for (int i = 0; i < readBlockThreads.size(); i++)
	{
		readBlockThreads[i]->wait();
		//结束后进行指针的销毁
		delete readBlockThreads[i];
		MLog::log("debug", "ReadBlock:readMostD2", "block " + to_string(i) + "read success  ... ");
		if (!tiffBlocks[i]->tiffFlag) //当块读取失败时立即返回
		{
			MLog::log("debug", "ReadBlock:readMostD2", "read tiff failed ... ");
			return nullptr;
		}
	}


	//创建三维数组空间
	//uint16 ***img_data = new uint16 **[t[0] * TIFF_BLOCK_WIDTH];
	//for (int x = 0; x < t[0] * TIFF_BLOCK_WIDTH; x++)
	//{
	//	img_data[x] = new uint16*[t[1] * TIFF_BLOCK_HEIGHT];
	//	for (int y = 0; y < t[1] * TIFF_BLOCK_HEIGHT; y++)
	//	{
	//		img_data[x][y] = new uint16[t[2] * TIFF_BLOCK_FRAMES];
	//	}
	//}

	//对数组空间赋值
	//for (int z = 0; z < t[2] * TIFF_BLOCK_FRAMES; z++)
	//{
	//	for (int y = 0; y < t[1] * TIFF_BLOCK_HEIGHT; y++)
	//	{
	//		for (int x = 0; x < t[0] * TIFF_BLOCK_WIDTH; x++)
	//		{
	//			int tx = x / TIFF_BLOCK_WIDTH;
	//			int ty = y / TIFF_BLOCK_HEIGHT;
	//			int tz = z / TIFF_BLOCK_FRAMES;
	//			int index = tx * t[1] * t[2] + ty * t[2] + tz;
	//			img_data[x][y][z] = buffer[index][z % TIFF_BLOCK_FRAMES * TIFF_BLOCK_WIDTH * TIFF_BLOCK_HEIGHT + y % TIFF_BLOCK_HEIGHT * TIFF_BLOCK_WIDTH + x % TIFF_BLOCK_WIDTH];
	//		}
	//	}
	//}


	//获取起始坐标
	int sp[3];
	sp[0] = floor(ps[0].fx / TIFF_BLOCK_WIDTH) * TIFF_BLOCK_WIDTH;
	sp[1] = floor(ps[0].fy / TIFF_BLOCK_HEIGHT) * TIFF_BLOCK_HEIGHT;
	sp[2] = floor(ps[0].fz / TIFF_BLOCK_FRAMES) * TIFF_BLOCK_FRAMES;

	//提前遍历一遍得到最大与最小的像素值
	int max_c = 0;
	int min_c = 4096;
	for (MPoint p : points)
	{
		int tp[3] = { p.fx - sp[0], p.fy - sp[1], p.fz - sp[2] }; //得到在块中的相对位置
		int sx, sy, sz, ex, ey, ez;
		sx = tp[0] - POINT_BLOCK_RADIUS < 0 ? 0 : tp[0] - POINT_BLOCK_RADIUS;
		sy = tp[1] - POINT_BLOCK_RADIUS < 0 ? 0 : tp[1] - POINT_BLOCK_RADIUS;
		sz = tp[2] - POINT_BLOCK_RADIUS / 2 < 0 ? 0 : tp[2] - POINT_BLOCK_RADIUS / 2;

		ex = tp[0] + POINT_BLOCK_RADIUS > t[0] * TIFF_BLOCK_WIDTH - 1 ? t[0] * TIFF_BLOCK_WIDTH - 1 : tp[0] + POINT_BLOCK_RADIUS;
		ey = tp[1] + POINT_BLOCK_RADIUS > t[1] * TIFF_BLOCK_HEIGHT - 1 ? t[1] * TIFF_BLOCK_HEIGHT - 1 : tp[1] + POINT_BLOCK_RADIUS;
		ez = tp[2] + POINT_BLOCK_RADIUS / 2 > t[2] * TIFF_BLOCK_FRAMES - 1 ? t[2] * TIFF_BLOCK_FRAMES - 1 : tp[2] + POINT_BLOCK_RADIUS / 2; //进行块上下边界的获取


		for (int y = sy; y <= ey; y++)
		{
			for (int x = sx; x <= ex; x++)
			{
				for (int z = sz; z <= ez; z++)
				{
					int tx = x / TIFF_BLOCK_WIDTH;
					int ty = y / TIFF_BLOCK_HEIGHT;
					int tz = z / TIFF_BLOCK_FRAMES;
					int index = tx * t[1] * t[2] + ty * t[2] + tz;
					int c = tiffBlocks[index]->buffer[z % TIFF_BLOCK_FRAMES * TIFF_BLOCK_WIDTH * TIFF_BLOCK_HEIGHT + y % TIFF_BLOCK_HEIGHT * TIFF_BLOCK_WIDTH + x % TIFF_BLOCK_WIDTH];
					if (c > max_c)
					{
						max_c = c;
					}
					if (c < min_c)
					{
						min_c = c;
					}
				}
			}
		}
	}

	for (MPoint p : points)
	{
		int tp[3] = { p.fx - sp[0], p.fy - sp[1], p.fz - sp[2] }; //得到在块中的相对位置
		int sx, sy, sz, ex, ey, ez;
		sx = tp[0] - POINT_BLOCK_RADIUS < 0 ? 0 : tp[0] - POINT_BLOCK_RADIUS;
		sy = tp[1] - POINT_BLOCK_RADIUS < 0 ? 0 : tp[1] - POINT_BLOCK_RADIUS;
		sz = tp[2] - POINT_BLOCK_RADIUS / 2 < 0 ? 0 : tp[2] - POINT_BLOCK_RADIUS / 2;

		ex = tp[0] + POINT_BLOCK_RADIUS > t[0] * TIFF_BLOCK_WIDTH - 1 ? t[0] * TIFF_BLOCK_WIDTH - 1 : tp[0] + POINT_BLOCK_RADIUS;
		ey = tp[1] + POINT_BLOCK_RADIUS > t[1] * TIFF_BLOCK_HEIGHT - 1 ? t[1] * TIFF_BLOCK_HEIGHT - 1 : tp[1] + POINT_BLOCK_RADIUS;
		ez = tp[2] + POINT_BLOCK_RADIUS / 2 > t[2] * TIFF_BLOCK_FRAMES - 1 ? t[2] * TIFF_BLOCK_FRAMES - 1 : tp[2] + POINT_BLOCK_RADIUS / 2; //进行块上下边界的获取


		for (int y = sy; y <= ey; y++)
		{
			for (int x = sx; x <= ex; x++)
			{
				int maxC = 0;
				for (int z = sz; z <= ez; z++)
				{
					int tx = x / TIFF_BLOCK_WIDTH;
					int ty = y / TIFF_BLOCK_HEIGHT;
					int tz = z / TIFF_BLOCK_FRAMES;
					int index = tx * t[1] * t[2] + ty * t[2] + tz;
					int c = tiffBlocks[index]->buffer[z % TIFF_BLOCK_FRAMES * TIFF_BLOCK_WIDTH * TIFF_BLOCK_HEIGHT + y % TIFF_BLOCK_HEIGHT * TIFF_BLOCK_WIDTH + x % TIFF_BLOCK_WIDTH];
					if (c > maxC)
					{
						maxC = c;
					}
				}
				maxC = double(maxC - min_c) / (max_c - min_c) * 255; // 进行颜色空间的转换
				img->setPixelColor(x, y, qRgb(maxC, maxC, maxC));
			}
		}
	}

	//释放内存空间
	for (int i = 0; i < tiffBlocks.size(); i++)
	{
		delete tiffBlocks[i];
	}

	//releaseImgData(img_data , t[0] * TIFF_BLOCK_HEIGHT , t[1] * TIFF_BLOCK_WIDTH);
	MLog::log("debug", "TiffHelper::getProjectionImg", "get img done ... ");
	return img;
}

void TiffHelper::readFramesThread(TIFF *tiff , uint16** buffer , int sf , int ef , int width , int height , int totalFrame)
{
	for (int s = sf; s < ef; s++)
	{
		//MLog::log("debug", "TiffHelepr:readTiffFromPathToTiffBlock", "N_size : " + TimeShare::dataToString(N_size));
		for (int row = 0; row < height; row++)
		{
			TIFFReadScanline(tiff, (&(*buffer)[s * width * height] + row * width), row); //获得该行的地址，并且进行按行读取
		}
		TIFFReadDirectory(tiff);
	}
}

bool TiffHelper::readTiffByPath(std::string path, uint16** buffer)
{
	int threadNum = std::thread::hardware_concurrency();
	TIFF *tiff = TIFFOpen(path.data(), "r");	 //以只读的方式打开文件
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
	//qDebug() << "width : " << width << " height : " << height << " totalFrame:" << totalFrame << " stripSize : " << stripSize << " btisPerPixel : " << bitsPerPixel;
	if (bitsPerPixel == 16) //根据图像的每个像素点所占bit位分别进行图像数据的读取
	{
		*buffer = new uint16[totalFrame * stripSize]; //申请存储图像的内存空间
		int N_size = 0;
		for (int s = 0; s < totalFrame; s++)
		{
			//MLog::log("debug", "TiffHelepr:readTiffFromPathToTiffBlock", "N_size : " + TimeShare::dataToString(N_size));
			for (int row = 0; row < height; row++)
			{
				TIFFReadScanline(tiff, (&(*buffer)[N_size] + row * width), row); //获得该行的地址，并且进行按行读取
			}
			N_size += width * height;
			TIFFReadDirectory(tiff); //进行每一页的读入，即翻页
		}
	}
	else
	{
		qDebug() << "unkonwn tif , read " << path.data() << " failed ...";
		return false;
	}
	TIFFClose(tiff);
	qDebug() << "read " << path.data() << " success ...";
	return true;
}
//得到三个方向的块数信息
void TiffHelper::identifyMostDNumber(MPoint ps[], int t[])
{
	int startBlock[3]; //得到三个方向的起始块坐标
	startBlock[0] = floor(float(ps[0].fx - 0.1) / TIFF_BLOCK_WIDTH) * TIFF_BLOCK_WIDTH + TIFF_BLOCK_WIDTH;
	startBlock[1] = floor(float(ps[0].fy - 0.1) / TIFF_BLOCK_HEIGHT) * TIFF_BLOCK_HEIGHT + TIFF_BLOCK_HEIGHT;
	startBlock[2] = floor(float(ps[0].fz - 0.1) / TIFF_BLOCK_FRAMES) * TIFF_BLOCK_FRAMES + TIFF_BLOCK_FRAMES;

	if (ps[1].fx < startBlock[0]) //取到x方向上的块数
	{
		t[0] = 1;
	}
	else
	{
		t[0] = ceil(float(ps[1].fx - startBlock[0]) / (float)TIFF_BLOCK_WIDTH) + 1;
	}

	if (ps[1].fy < startBlock[1]) //取到y方向上的块数
	{
		t[1] = 1;
	}
	else
	{
		t[1] = ceil(float(ps[1].fy - startBlock[1]) / (float)TIFF_BLOCK_HEIGHT) + 1;
	}

	if (ps[1].fz < startBlock[2]) //取到z方向的块数
	{
		t[2] = 1;
	}
	else
	{
		t[2] = ceil(float(ps[1].fz - startBlock[2]) / (float)TIFF_BLOCK_FRAMES) + 1;
	}
}
bool TiffHelper::saveTiffByPath(std::string path, uint16* buffer, int size[])
{
	int width = size[0];
	int height = size[1];
	int slice = size[2];

	TIFF* out = TIFFOpen(path.data(), "w");
	if (out)
	{
		int N_size = 0;
		size_t nCur = 0;
		//UChar den = (sizeof(T) == 1) ? 1 : 4;
		do{
			TIFFSetField(out, TIFFTAG_SUBFILETYPE, FILETYPE_PAGE);
			TIFFSetField(out, TIFFTAG_PAGENUMBER, slice);
			TIFFSetField(out, TIFFTAG_IMAGEWIDTH, (uint32)width);
			TIFFSetField(out, TIFFTAG_IMAGELENGTH, (uint32)height);
			//TIFFSetField(out, TIFFTAG_RESOLUTIONUNIT, 2);
			/*TIFFSetField(out, TIFFTAG_YRESOLUTION, 196.0f);
			TIFFSetField(out, TIFFTAG_XRESOLUTION, 204.0f);*/
			TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
			// 
			TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 16);    //根据图像位深填不同的值
			TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 1);
			TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
			TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
			TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
			TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, height);


			for (int m = 0; m < height; m++)
			{
				TIFFWriteScanline(out, &buffer[N_size + width*m], m, 0);
			}
			//TIFFWriteEncodedStrip(out, 0, &buffer[N_size], width * height);      //另一种写入方法

			++nCur;
			N_size = N_size + width*height;
		} while (TIFFWriteDirectory(out) && nCur < slice);
		TIFFClose(out);
		qDebug() << "save "<<path.data()<<" success ... ";
		return true;
	}
	qDebug() << "save " << path.data() << " failed ... ";
	return false;
}

void TiffHelper::releaseImgData(uint16 ***img_data , int width , int height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			delete img_data[x][y];
		}
		delete img_data[x];
	}
	MLog::log("debug", "TiffHelper::releaseImgData", "release data success ... ");
}

TiffHelper::~TiffHelper()
{
}
