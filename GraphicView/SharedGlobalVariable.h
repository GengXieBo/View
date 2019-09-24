#pragma once
#ifndef SHAREGLOBALVARUABLE_H
#define SHAREGLOBALVARUABLE_H

#include <QtWidgets\qprogressdialog.h>
#include "MouseData.h"
#include "TxtHelper.h"
#include "TiffBlockManager.h"
#include <string>
extern TxtHelper txtHelper;
extern MouseData mouseData;
extern TiffBlockManager tiffBlockManager;
extern std::string TIFF_PATH ;
#endif

