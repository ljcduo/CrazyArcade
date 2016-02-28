#include "LGUtil.h"
#include <Windows.h>
#include <wchar.h>
#include <stdio.h>
#include <stdio.h>
#include "Point.h"



namespace Util{

wchar_t* Util::CharToWchar(const char* c)
{
	int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0);  
	wchar_t* wchar=new wchar_t[len+1];  
	MultiByteToWideChar(CP_ACP,0,c,strlen(c),wchar,len);  
	wchar[len]='\0';  
	return wchar;
}

bool Util::AccumulateToOne(float* sum, float const& AddNum)
{
	*sum += AddNum;
	if (*sum > 1)
	{
		*sum = 0;
		return true;
	}
	return false;
}

bool Util::isCollsionWithRect(LGRect rect1, LGRect rect2) 
{
	int offsetValue = 0;

	float x1 = rect1.GetX();
	float y1 = rect1.GetY();
	float w1 = rect1.GetWidth();
	float h1 = rect1.GetHeight();

	float x2 = rect2.GetX();
	float y2 = rect2.GetY();
	float w2 = rect2.GetWidth();
	float h2 = rect2.GetHeight();

	if (x1 >= x2 && x1 >= x2 + w2) {  
		return false;  
	} else if (x1 <= x2 && x1 + w1 <= x2) {  
		return false;  
	} else if (y1 >= y2 && y1 >= y2 + h2) {  
		return false;  
	} else if (y1 <= y2 && y1 + h1 <= y2) {  
		return false;  
	}

	return true;  
}  



bool CollisionInsideRect(LGRect inside, LGRect outside)
{
	float x1 = inside.GetX();
	float y1 = inside.GetY();
	float w1 = inside.GetWidth();
	float h1 = inside.GetHeight();

	float x2 = outside.GetX();
	float y2 = outside.GetY();
	float w2 = outside.GetWidth();
	float h2 = outside.GetHeight();

	if (x1 >= x2 && x1 + w1 <= x2 + w2 && y1 >= y2 && y1 + h1 <= y2 + h2)
	{
		return true;
	}

	return false;

}



bool PointCollisionRect(Point point ,LGRect rect)
{
	float x1 = point.GetX();
	float y1 = point.GetY();

	float x2 = rect.GetX();
	float y2 = rect.GetY();
	float w = rect.GetWidth();
	float h = rect.GetHeight();

	if (x1 >= x2 && x1 <= x2 + w && y1 >= y2 && y1 <= y2 + h) {  
		return true;
	}   
	return false; 
}

LGRect CalCrossRect(LGRect rect1, LGRect rect2)
{
	float Xa1 = rect1.GetX();
	float Ya1 = rect1.GetY() + rect1.GetHeight();
	float Xa2 = rect1.GetX() + rect1.GetWidth();
	float Ya2 = rect1.GetY();

	float Xb1 = rect2.GetX();
	float Yb1 = rect2.GetY() + rect2.GetHeight();
	float Xb2 = rect2.GetX() + rect2.GetWidth();
	float Yb2 = rect2.GetY();

	float Xc1 = max(Xa1,Xb1);
	float Yc1 = min(Ya1,Yb1);
	float Xc2 = min(Xa2,Xb2);
	float Yc2 = max(Ya2,Yb2);

	if(Xc1 <= Xc2 && Yc1 >= Yc2 )
	{
		return LGRect(Xc1,Yc2,Xc2-Xc1,Yc1-Yc2);
	}

	return LGRect();
}

}

int Util::Convert2Dto1D(int x, int y, int colNum)
{
	return x*colNum + y;
}

void Util::Convert1Dto2D(int index, int colNum, int* x, int* y)
{
	*x = index / colNum;
	*y = index % colNum;
}