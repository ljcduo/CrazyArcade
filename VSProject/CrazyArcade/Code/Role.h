#pragma once

#include "GameObject.h"
#include "StateMachine.h"
#include "Ability.h"

class Prop;

class Role : public GameObject
{
public:
	enum E_RoleDirection {E_Up, E_Down, E_Left, E_Right};
	enum E_RoleSpriteType {E_RedBaby, E_BrownPirate};
	Role(std::wstring objName, int mapPosX, int mapPosY, E_RoleSpriteType spriteType);
	virtual ~Role();
	virtual void Update(float deltaTime);
	void Move(float deltaTime);
	bool HandleMessage(const Telegram& telegram);
	void EatProp(Prop* prop);
	void StopWalk();
	bool IsFullyArrive();
	void FullyArrive();
	void UpdateRectCollision(int offsetX = 0, int offsetY = 0, int offsetWidth = 0, int offsetHeight = 0);
	void RecoveDirect(); 
	//————————————————————————GetAndSet
	bool const& GetCanMove() const;
	void SetCanMove(bool val);

	float const& GetWalkSpeed() const;
	void SetWalkSpeed(float val);

	StateMachine<Role>* const& GetStateMachine() const;

	Role::E_RoleDirection const& GetDirection() const;
	void SetDirection(Role::E_RoleDirection val);

	Ability* const& GetAbility() const;
	void SetAbility(Ability* val);

	Point const& Role::GetStandOnBubble() const;
	void SetStandOnBubble(bool val);
	bool IsStandOnBubble();

	bool FullyEnter() const { return m_FullyEnter; }
	void FullyEnter(bool val) { m_FullyEnter = val; }
private:
	float m_WalkSpeed;
	StateMachine<Role>*  m_pStateMachine;
	E_RoleDirection m_direction;
	bool m_CanMove;		//如果遇到障碍物就不能移动
	Ability* m_pAbility;
	static Point m_standOnBubble;
	bool m_FullyEnter; //完全贴合
};