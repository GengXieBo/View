#include "TiffBlockManager.h"


TiffBlockManager::TiffBlockManager()
{
	this->maxBlocks = MAX_BLOCKS;
	this->currentBlocks = 0;
	this->head = NULL;
	this->tail = NULL;
}

/*清除队列上的所有指针*/
void TiffBlockManager::clear()
{
	QMutexLocker locker(&mutex);
	if (this->currentBlocks > 0)
	{
		PTiffBlock temp = NULL;
		while (head != NULL)
		{
			temp = head;
			head = head->next;
			delete temp->buffer;
			delete temp;
		}
		currentBlocks = 0;
		head = tail = NULL;
	}
}
/*添加tiff块操作*/
bool TiffBlockManager::addBlock(PTiffBlock tiffBlock)
{
	QMutexLocker locker(&mutex);
	bool result = false;
	if (tiffBlock == NULL)
	{
		return result;
	}
	MLog::log("debug", "TiffBlockManager:addBlock", "currentBlocks : " + to_string(currentBlocks));
	if (currentBlocks == maxBlocks - 1) //当队列满时，进行队尾的删除 
	{
		MLog::log("debug", "TiffBlockManager:addBlock", "delete memeory");
		PTiffBlock temp;
		temp = tail->pre;
		delete tail->buffer;
		delete tail;
		temp->next = NULL;
		tail = temp;
		currentBlocks--; //将tiff块数减1
	}

	if (currentBlocks == 0) //判断队列是否为空
	{
		head = tail = tiffBlock;
		result = true;
		currentBlocks++;
		return result;
	}
	tiffBlock->next = head;
	head->pre = tiffBlock;
	head = tiffBlock;
	currentBlocks++;
	result = true;
	return result;
}

PTiffBlock TiffBlockManager::getTiffBlock(int x, int y, int z)
{
	QMutexLocker locker(&mutex);
	PTiffBlock temp = head;
	while (temp != NULL)
	{
		//MLog::log("debug" , "TiffBlockManager:getTiffBlock" , "judge wether getTiffBlock die ... ");
		if (temp->x == x && temp->y == y && temp->z == z)
		{
			break;
		}
		temp = temp->next;
	}

	//如果取出的块不为空，则将当前块放到队首
	if (temp != NULL)
	{
		if (temp == head)
		{
			return temp;
		}
		else if (temp == tail)
		{
			tail = tail->pre;
			tail->next = NULL;
			temp->pre = NULL;
			temp->next = head;
			head->pre = temp;
			head = temp;
			return temp;
		}
		else
		{
			temp->pre->next = temp->next;
			temp->next->pre = temp->pre;
			temp->pre = NULL;
			temp->next = head;
			head->pre = temp;
			head = temp;
			return temp;
		}
	}
	else
	{
		return NULL;
	}
}

/*显示所有的块 , 从队头到队尾*/
void TiffBlockManager::showBlocks()
{
	PTiffBlock temp = head;
	while (temp != NULL)
	{
		qDebug() << "x : " << temp->x << " y : " << temp->y << " z : " << temp->z;
		temp = temp->next;
	}
}
TiffBlockManager::~TiffBlockManager()
{
}
