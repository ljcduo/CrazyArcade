#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------
//
//  Name:   State.h
//
//  Desc:   abstract base class to define an interface for a state
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "Telegram.h"

template <class entity_type>
class State
{
public:

	virtual ~State(){}

	//this will execute when the state is entered
	virtual void Enter(entity_type*)=0;

	//this is the states normal update function
	virtual void Execute(entity_type*,float deltatime = 0.0f)=0;

	//this will execute when the state is exited. (My word, isn't
	//life full of surprises... ;o))
	virtual void Exit(entity_type*)=0;

	virtual bool OnMessage(entity_type* agent, const Telegram& msg) = 0;
};

#endif