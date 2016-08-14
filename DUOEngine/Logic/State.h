#pragma once

#include "Telegram.h"

template <class entity_type>
class State
{
public:

	virtual void Enter(entity_type*)=0;
	virtual void Execute(entity_type*,float deltatime = 0.0f)=0;
	virtual void Exit(entity_type*)=0;

	virtual bool OnMessage(entity_type* agent, const Telegram& msg) = 0;
};
