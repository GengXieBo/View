#include "TiffBlockManager.h"


TiffBlockManager::TiffBlockManager()
{
	this->maxBlocks = MAX_BLOCKS;
	this->currentBlocks = 0;
	this->head = NULL;
	this->tail = NULL;
}

/*��������ϵ�����ָ��*/
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
/*���tiff�����*/
bool TiffBlockManager::addBlock(PTiffBlock tiffBlock)
{
	QMutexLocker locker(&mutex);
	bool result = false;
	if (tiffBlock == NULL)
	{
		return result;
	}
	MLog::log("debug", "TiffBlockManager:addBlock", "currentBlocks : " + to_string(currentBlocks));
	if (currentBlocks == maxBlocks - 1) //��������ʱ�����ж�β��ɾ�� 
	{
		MLog::log("debug", "TiffBlockManager:addBlock", "delete memeory");
		PTiffBlock temp;
		temp = tail->pre;
		delete tail->buffer;
		delete tail;
		temp->next = NULL;
		tail = temp;
		currentBlocks--; //��tiff������1
	}

	if (currentBlocks == 0) //�ж϶����Ƿ�Ϊ��
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

	//���ȡ���Ŀ鲻Ϊ�գ��򽫵�ǰ��ŵ�����
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

/*��ʾ���еĿ� , �Ӷ�ͷ����β*/
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
