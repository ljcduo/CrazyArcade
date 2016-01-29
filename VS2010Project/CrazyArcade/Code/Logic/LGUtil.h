#pragma once

#include <map>
#include "Rect.h"
#include "Util.h"
#include <vector>

namespace LayoutType
{
	enum E_Layout {E_GUIs,E_Roads,E_UnderBubbles,E_Bubbles,E_Roles=4,E_Soild=4,E_Blocks=4,E_Props=4};
}

namespace MapType
{
	enum E_MapType {E_None,E_RedHouse,E_BlueHouse,E_YellowHouse,
		E_TownBlockRed,E_TownBlockYellow,E_Tree,E_TownWindmill,E_TownWindmillAni,
		E_TownBox,E_Solid,E_SandBlockBuff,E_SandBlockYellow,E_SandBox,E_Bubble,E_Prop,E_Danger};
}

namespace ObjectType
{
	enum E_ObjectType {E_ObjCommon, E_ObjBlock, E_ObjRole, E_Bubble, E_Prop,E_Build};
}

namespace Util
{
	bool CollisionInsideRect(LGRect inside, LGRect outside);
	bool isCollsionWithRect(LGRect rect1, LGRect rect2);
	wchar_t* CharToWchar(const char* c);
	bool AccumulateToOne(float* sum, float const& AddNum);
	std::wstring CreateMapName(int x, int y, std::wstring Obj);
	//bool CollisionInsideRectVec(LGRect inside, std::vector<LGRect> outsideVec);
	LGRect CalCrossRect(LGRect rect1, LGRect rect2);
}