#include "AI.h"
#include "RoleState.h"

AI::AI(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType)
	: Role(objName,mapPosX,mapPosY,spriteType), m_AISearcher(NULL)
{

}

AI::~AI()
{

}

void AI::Update(float deltaTime)
{
	Role::Update(deltaTime);
	UpdateAISearcher();
}

bool AI::IsGraphChange()
{
	return true;
}

void AI::UpdateAISearcher()
{
	GoToDest(14, 0);
}

bool AI::GoToDest(int x, int y)
{
	int xOffset = this->GetMapPosX() - x, yOffset = this->GetMapPosY() - y;
	Util::DebugOut() << xOffset << "," << yOffset;
	if (xOffset != 0)
	{
		if (xOffset > 0)
			this->GetStateMachine()->ChangeState(WalkLeft::Instance());
		else
			this->GetStateMachine()->ChangeState(WalkRight::Instance());
	}
	else if (yOffset != 0)
	{
		if (yOffset > 0)
			this->GetStateMachine()->ChangeState(WalkDown::Instance());
		else
			this->GetStateMachine()->ChangeState(WalkUp::Instance());
	}
	else
	{
		this->StopWalk();
	}
	return true;
}
