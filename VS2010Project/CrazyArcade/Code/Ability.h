#pragma once

class Ability
{
public:
	enum E_AbilityType {E_BubbleNum, E_Power, E_RunSpeed };
	Ability();
	//！！！！！！！！！！！！！！！！！！GetAndSet
	int const& GetBubbleNum() const;
	void SetBubbleNum(int val);
	void Decrease(E_AbilityType abilityType);	//嬬薦受1
	void Crease(E_AbilityType abilityType);	//嬬薦奐1
	int const& GetPower() const;
	void SetPower(int val);
	int const& GetRunSpeed() const;
	void SetRunSpeed(int val);
private:
	int m_bubbleNum;
	int m_power;
	int m_runSpeed;
};