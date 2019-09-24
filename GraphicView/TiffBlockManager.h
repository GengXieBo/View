#pragma once
#include <tiff.h>
#include <stdio.h>
#include <qdebug.h>
#include "TiffSet.hpp"
#include "MLog.h"

/*进行块的定义*/
typedef struct _TiffBlock{
	bool tiffFlag; //是否成功读取的标志位
	uint16 *buffer;
	int x;
	int y;
	int z;
	struct _TiffBlock *pre, *next; //指向上一块与下一块的指针
}TiffBlock, *PTiffBlock;

/*管理加载进内存的tiff块，减小重新读读入的代价，本质上是一个队列结构*/
class TiffBlockManager
{
public:

	TiffBlockManager();
	void clear();
	bool addBlock(PTiffBlock tiffBlock); //添加新的tiff块
	PTiffBlock getTiffBlock(int x, int y, int z); //根据x , y , z进行tiff块的获取，如果失败则返回NULL
	void showBlocks();
	~TiffBlockManager();

private:
	int maxBlocks; //存储最大能放下的tiff块(512 * 512 * 512)
	int currentBlocks; //记录当前的块数
	PTiffBlock head;
	PTiffBlock tail; //指向队头与队尾的块指针
	QMutex mutex; //进行多线程的控制操作
};


