#pragma once
#include "Role.h"
class GraphSearcher;

class AI : public Role
{
public:
	AI(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType);
	virtual ~AI();
	virtual void Update(float deltaTime);

	GraphSearcher* AISearcher() const { return m_AISearcher; }
	void AISearcher(GraphSearcher* val) { m_AISearcher = val; }
	bool GoToDest(int x, int y);
protected:
	bool IsGraphChange();
	void UpdateAISearcher();
private:
	GraphSearcher* m_AISearcher;
};