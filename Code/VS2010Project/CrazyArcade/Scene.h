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
	std::vector<Object*> const& GetAllObject();
	Object* HavaObject(std::wstring objName);
	Object* HavaObject(int objID);
	void InsertObject(Object* pInsertObj);
	bool DeleteObject(std::wstring objName);
	bool DeleteObject(int objID);
	virtual void LoadScene() = 0;
	virtual void UnloadScene();
	bool const& GetGameEnd() const;
	void SetGameEnd(bool val);
	void InsertDetectDirtyRect(LGRect dirtyRect); //加入脏矩形检测集合
	void DirtyRectInfect();
	void ClearDirtyRect();
	void hadLoadAll();
	std::vector<Object*> const& GetUnLoadObject() const;
	std::vector<Object*> const& GetAllDirtyObject();
	void InsertDetectDirtyObject(Object* obj);
	void ClearDirtyObject();
protected:
	std::vector<Object*> m_allObject;
	//bool ObjectSort(Object* const& lhs, Object* const& rhs);
	bool SameName(Object* const& lhs, std::wstring const& name);
	bool ObjectSort(Object* const& lhs, Object* const& rhs);
	bool m_gameEnd;
	std::vector<LGRect> m_allDetectDirtyRect;
	std::vector<Object*> m_UnLoadObject;
	std::vector<Object*> m_allDirtyObject;
};

extern Scene* g_pCurrentScene;