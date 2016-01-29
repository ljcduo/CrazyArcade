#pragma once

#include "State.h"
#include "Bubble.h"

class BubbleState : public State<Bubble>
{
public:
	bool OnMessage(Bubble* agent, const Telegram& msg);
	void Execute(Bubble* bubble,float deltatime /* = 0.0f */);
	void Exit(Bubble * bubble);
};

class BubbleWait : public BubbleState
{
	SINGLETON(BubbleWait);
public:
	void Enter(Bubble* bubble);
	bool OnMessage(Bubble* agent, const Telegram& msg);
};

class BubbleExplosion : public BubbleState
{
	SINGLETON(BubbleExplosion);
public:
	void Enter(Bubble* bubble);
};

