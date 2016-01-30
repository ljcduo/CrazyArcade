#pragma once

#include "GameUtil.h"
#include "GameObject.h"

class Prop;

class Block : public GameObject
{
public:
	Block(int posX, int posY,MapType::E_MapType blockType);
	~Block();
	Prop* const& GetInsideProp() const;
	void SetInsideProp(Prop* val);
	void Update(float deltaTime);
private:
	Prop* m_pInsideProp;	//方块内的道具
	bool m_Animate;
};