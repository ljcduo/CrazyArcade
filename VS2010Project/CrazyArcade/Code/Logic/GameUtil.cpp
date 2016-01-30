#include "GameUtil.h"
#include <Windows.h>

std::wstring Util::CreateMapName(int x, int y, std::wstring Obj)
{
	wchar_t buffer[30];
	memset(buffer,0,sizeof(buffer));
	int rolePosX = x;
	int rolePoxY = y;
	Obj += L"(%d,%d)";
	wsprintfW(buffer, Obj.c_str(), rolePosX,rolePoxY);
	return buffer;
}

