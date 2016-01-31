#include "MessageDispatcher.h"
#include "CrudeTimer.h"
#include "Object.h"
#include "LGCenter.h"

#include <iostream>

using std::set;

MessageDispatcher::MessageDispatcher()
{
	m_GameTimer = new CrudeTimer;
}

MessageDispatcher::~MessageDispatcher()
{
	delete m_GameTimer;
}

void MessageDispatcher::SendMessage(Object* pReceiver,
	const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
	{
		//消息无法被处理
		OutputDebugStringW(L"Message not handled");
	}
}

void MessageDispatcher::MakeMessage(double delay,
	int sender,
	int receiver,
	int msg,
	void* ExtraInfo)
{
	Object* pSender   = LGCenter::Instance()->GetCurrentScene()->HavaObject(sender);
	Object* pReceiver = LGCenter::Instance()->GetCurrentScene()->HavaObject(receiver);

	//创建电报
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//如果没有延时，则立即处理
	if (delay <= 0.0f)                                                        
	{
		if(pReceiver)
			SendMessage(pReceiver, telegram);
	}
	else //否则计算电报的实际发送时间点
	{
		double CurrentTime = m_GameTimer->GetTimePass(); 

		telegram.DispatchTime = CurrentTime + delay;

		// 然后放进队列里
		PriorityQ.insert(telegram);   

	}
}


void MessageDispatcher::Update()
{
	double CurrentTime = m_GameTimer->GetTimePass();

	while( !PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) )
	{
		const Telegram& telegram = *PriorityQ.begin();

		Object* pReceiver = LGCenter::Instance()->GetCurrentScene()->HavaObject(telegram.Receiver);

		if (pReceiver != NULL)
		{
			SendMessage(pReceiver, telegram);
		}

		PriorityQ.erase(PriorityQ.begin());
	}
}



