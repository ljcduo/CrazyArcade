#pragma once
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include "Util.h"

#define Clock CrudeTimer::Instance()

class CrudeTimer
{
public:
	CrudeTimer();
	~CrudeTimer();
	// 返回从该类实例化以来的时间（秒）
	double GetTimePass();
	void reset();
private:
	// 当该类被实例化的时候记录开始的时间
	double m_dStartTime;
};