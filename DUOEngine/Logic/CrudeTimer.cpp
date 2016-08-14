#include "CrudeTimer.h"

CrudeTimer::CrudeTimer()
{
	reset();
}

CrudeTimer::~CrudeTimer()
{

}

void CrudeTimer::reset()
{
	m_dStartTime = timeGetTime() * 0.001;
}

double CrudeTimer::GetTimePass()
{
	return timeGetTime() * 0.001 - m_dStartTime;
}