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

#define g_pMessageMachine MessageDispatcher::Instance()

class MessageDispatcher
{
	SINGLETON(MessageDispatcher);
private:  

	// 处理一个消息
	void SendMessage(Object* pReceiver, const Telegram& msg);

public:

	// 产生一个待处理的消息
	void MakeMessage(double delay,
		int    sender,
		int    receiver,
		int msg,
		void* ExtraInfo);

	// 此函数每一帧被调用
	void Update();

private:
	std::set<Telegram> m_MsgPriorityQueue;
	CrudeTimer* m_GameTimer;
};

#endif