#pragma once
#include <tiff.h>
#include <stdio.h>
#include <qdebug.h>
#include "TiffSet.hpp"
#include "MLog.h"

/*���п�Ķ���*/
typedef struct _TiffBlock{
	bool tiffFlag; //�Ƿ�ɹ���ȡ�ı�־λ
	uint16 *buffer;
	int x;
	int y;
	int z;
	struct _TiffBlock *pre, *next; //ָ����һ������һ���ָ��
}TiffBlock, *PTiffBlock;

/*������ؽ��ڴ��tiff�飬��С���¶�����Ĵ��ۣ���������һ�����нṹ*/
class TiffBlockManager
{
public:

	TiffBlockManager();
	void clear();
	bool addBlock(PTiffBlock tiffBlock); //����µ�tiff��
	PTiffBlock getTiffBlock(int x, int y, int z); //����x , y , z����tiff��Ļ�ȡ�����ʧ���򷵻�NULL
	void showBlocks();
	~TiffBlockManager();

private:
	int maxBlocks; //�洢����ܷ��µ�tiff��(512 * 512 * 512)
	int currentBlocks; //��¼��ǰ�Ŀ���
	PTiffBlock head;
	PTiffBlock tail; //ָ���ͷ���β�Ŀ�ָ��
	QMutex mutex; //���ж��̵߳Ŀ��Ʋ���
};


