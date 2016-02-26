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
	StepToDest(14, 0);
}

bool AI::StepToDest(int x, int y)
{
	int xOffset = this->MapPosX() - x, yOffset = this->MapPosY() - y;
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
	else if(GetPixelPosX() - CalPixelPos(x,y).GetX() <= 0
		&& GetPixelPosY() - CalPixelPos(x,y).GetY() <= 0 
		|| !this->GetCanMove()) //Åö×²Æ«²î
	{
		this->StopWalk();
		this->SpreadDirty();
	}
	return true;
}
