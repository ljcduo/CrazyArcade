#pragma once

#include <map>
#include "Rect.h"
#include "Util.h"
#include <vector>

namespace Util
{
	bool CollisionInsideRect(LGRect inside, LGRect outside);
	bool isCollsionWithRect(LGRect rect1, LGRect rect2);
	wchar_t* CharToWchar(const char* c);
	bool AccumulateToOne(float* sum, float const& AddNum);
	LGRect CalCrossRect(LGRect rect1, LGRect rect2);
	int Convert2Dto1D(int x, int y, int colNum);
	void Convert1Dto2D(int index, int colNum, int* x, int* y);
}