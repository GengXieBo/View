#ifndef READBLOCKTHREAD_H
#define READBLOCKTHREAD_H

#include <QThread>
#include <string>
#include "TiffHelper.h"
#include "TimeShare.hpp"
#include "SharedGlobalVariable.h"
using namespace std;
class ReadBlockThread : public QThread
{
	Q_OBJECT

public:
	ReadBlockThread(QObject *parent);
	void setPath(string tiffPath, uint16 **buffer);
	void setTiffBlock(PTiffBlock tiffBlock);
	bool readTiffFromPathToTiffBlock(string path, PTiffBlock tiffBlock);
	void run();
	~ReadBlockThread();

private:
	string tiffPath;
	uint16 **buffer;
	PTiffBlock tiffBlock;
	QMutex mutex;
};

#endif // READBLOCKTHREAD_H
