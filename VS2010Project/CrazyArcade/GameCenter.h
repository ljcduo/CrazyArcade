#pragma once

#include "DXCenter.h"

class GameCenter : public DXCenter
{
SINGLETON_INHERIT_DERIVE(GameCenter);

protected:
	void Render();
	void Updte();
};