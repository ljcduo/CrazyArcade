#pragma once

#include "LGHead.h"
#include "State.h"

class LGCenter;
class Object;

class Scene : public State<LGCenter>
{
public:
	Scene();
	virtual ~Scene();
	
	// Get(Hava)函数
	std::vector<Object*> const& GetAllObject();
	std::vector<Object*> const& GetUnLoadObject() const;
	std::vector<Object*> const& GetAllDirtyObject();
	bool const& GetGameEnd() const;
	std::vector<Object*>& HaveAllObject();
	Object* HavaObject(std::wstring objName);
	Object* HavaObject(int objID);

	// Set函数
	void SetGameEnd(bool val);

	// 插入和删除
	void InsertObject(Object* pInsertObj);
	bool DeleteObject(std::wstring objName);
	bool DeleteObject(int objID);

	//其它
	void SortObject(std::vector<Object*>* objVec); //对对象进行按层和y轴排序
	void hadLoadAll(); //已经载入所有未载入的对象

	//-------------------------------脏矩形算法-begin------------------------------

	//脏矩形算法分四步：
	//1.对象污染场景中的矩形
	void DirtyScene(LGRect dirtyRect);
	//2.场景再污染回接触污染位置的所有对象
	void DirtyObject();
	//3.标记污染对象
	void InsertDirtyObject(Object* obj); //加入标记场景脏对象，用于渲染快速检索
	//4.清理工作
	void ClearDirty();

	//-------------------------------脏矩形算法-end------------------------------
private:
	std::vector<LGRect> m_DitryRectVec;		//场景中的脏矩形用于污染对象

	// 场景中的对象分为下面这三类
	std::vector<Object*> m_allObject;		//全部对象用于查找信息
	std::vector<Object*> m_UnLoadObject;	//未载入对象用于载入时初始化对象
	std::vector<Object*> m_allDirtyObject;	//脏对象用于渲染

	bool m_gameEnd;	//控制游戏结束
};

