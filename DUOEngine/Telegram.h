#pragma once
#include <iostream>
#include <math.h>
#include "LGHead.h"

struct Telegram
{
	int          Sender;
	int          Receiver;
	int          Msg;
	double       DispatchTime;	// 设置消息发送的时间，可以是立即也可以是多久之后的时间点
	void*        ExtraInfo;		// 额外的消息

	Telegram():DispatchTime(-1),
		Sender(-1),
		Receiver(-1),
		Msg(-1)
	{}

	Telegram(double time,
		int    sender,
		int    receiver,
		int    msg,
		void*  info = NULL): DispatchTime(time),
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		ExtraInfo(info)
	{}

};

// 电报被储存在优先队列，当重载比较操作符时，这个值决定了电报的时间是否是相等的
const double SmallestDelay = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return ( fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay) &&
		(t1.Sender == t2.Sender)        &&
		(t1.Receiver == t2.Receiver)    &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}
	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}