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
	std::vector<Object*> const& GetAllObject_Sort();
	std::vector<Object*> const& GetAllObject();
	std::vector<Object*>& HaveAllObject();
	Object* HavaObject(std::wstring objName);
	Object* HavaObject(int objID);
	void InsertObject(Object* pInsertObj);
	bool DeleteObject(std::wstring objName);
	bool DeleteObject(int objID);
	bool const& GetGameEnd() const;
	void SetGameEnd(bool val);
	void hadLoadAll();
	std::vector<Object*> const& GetUnLoadObject() const;

	//-------------------------------脏矩形算法-begin------------------------------
	std::vector<Object*> const& GetAllDirtyObject();
	void InsertDetectDirtyRect(LGRect dirtyRect); //矩形加入脏矩形检测集合
	void DirtyRectInfect(); // 脏矩形影响其它相交矩形
	void ClearDirtyRect();
	void InsertDetectDirtyObject(Object* obj); //对象加入脏矩形检测集合
	void ClearDirtyObject();
	//-------------------------------脏矩形算法-end------------------------------
protected:
	bool SameName(Object* const& lhs, std::wstring const& name);
	bool ObjectSort(Object* const& lhs, Object* const& rhs);
private:
	std::vector<Object*> m_allObject;
	bool m_gameEnd;
	std::vector<LGRect> m_allDetectDirtyRect;
	std::vector<Object*> m_UnLoadObject;
	std::vector<Object*> m_allDirtyObject;
public:
	static Scene* m_currentScene;
};

