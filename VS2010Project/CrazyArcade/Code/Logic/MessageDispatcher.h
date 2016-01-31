#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#pragma warning (disable:4786)

#include <set>


#include "Telegram.h"
#include "LGHead.h"
#include "CrudeTimer.h"

class Object;

const double SEND_MSG_IMMEDIATELY = 0.0f;
const int   NO_ADDITIONAL_INFO   = 0;

#define MessageMachine MessageDispatcher::Instance()

class MessageDispatcher
{
	SINGLETON(MessageDispatcher);
private:  

	//this method is utilized by DispatchMessage or DispatchDelayedMessages.
	//This method calls the message handling member function of the receiving
	//entity, pReceiver, with the newly created telegram
	void Discharge(Object* pReceiver, const Telegram& msg);

public:

	//send a message to another agent. Receiving agent is referenced by ID.
	void MakeMessage(double  delay,
		int    sender,
		int    receiver,
		int    msg,
		void*  ExtraInfo);

	// 此函数每一帧被调用
	void Update();

private:
	std::set<Telegram> PriorityQ;

	CrudeTimer* m_GameTimer;
};

#endif