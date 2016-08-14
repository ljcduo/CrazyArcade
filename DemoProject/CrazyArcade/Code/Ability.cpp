#include "Ability.h"




int const& Ability::GetBubbleNum() const
{
	return m_bubbleNum;
}

void Ability::SetBubbleNum(int val)
{
	m_bubbleNum = val;
}

Ability::Ability()
	:m_bubbleNum(1),m_power(5),m_runSpeed(1)
{
	
}


int const& Ability::GetPower() const
{
	return m_power;
}

void Ability::SetPower(int val)
{
	m_power = val;
}

void Ability::Decrease(E_AbilityType abilityType)
{
	switch(abilityType)
	{
	case E_BubbleNum:
		{
			--m_bubbleNum;
			break;
		}
	case E_Power:
		{
			--m_power;
			break;
		}
	case E_RunSpeed:
		{
			--m_runSpeed;
		}
	}
}

void Ability::Crease(E_AbilityType abilityType)
{
	switch(abilityType)
	{
	case E_BubbleNum:
		{
			if (m_bubbleNum <= 5)
			{
				++m_bubbleNum;
			}
			break;
		}
	case E_Power:
		{
			if (m_power <= 5)
			{
				++m_power;
			}
			break;
		}
	case E_RunSpeed:
		{
			if (m_runSpeed <= 5)
			{
				++m_runSpeed;
			}
			break;
		}
	}
}

void Ability::SetRunSpeed(int val)
{
	m_runSpeed = val;
}

int const& Ability::GetRunSpeed() const
{
	return m_runSpeed;
}
