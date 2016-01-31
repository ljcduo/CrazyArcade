#pragma once	

#include <string>
#include "Type.h"
#include "Point.h"

namespace Util
{
	const Point ORIGINPIX = Point(20,39);
	const int MAPPIECEPIX = 40;
	std::wstring CreateMapName(int x, int y, std::wstring Obj);
}