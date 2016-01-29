#include "Util.h"
#include <Windows.h>
#include <Strsafe.h>



bool Util::_trace(char *format, ...)
{
	char buffer[1000] = {0};
	va_list argptr;
	va_start(argptr, format);
	sprintf_s(buffer, format, argptr);
	va_end(argptr);
	OutputDebugStringA(buffer);
	return true;
}
