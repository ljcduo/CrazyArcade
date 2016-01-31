#include "Scene.h"
#include <algorithm>
#include <xfunctional>
#include "Object.h"
#include "LGCenter.h"

using namespace std;

Scene::Scene() : m_gameEnd(false)
{
	
}

void Scene::InsertObject(Object* pInsertObj)
{
	m_UnLoadObject.push_back(pInsertObj);
	m_allObject.push_back(pInsertObj);
}

Scene::~Scene()
{
	vector<Object*> copyObjVec = m_allObject;
	for (vector<Object*>::const_iterator itr = copyObjVec.begin(); itr != copyObjVec.end(); itr++)
	{
		DeleteObject((*itr)->GetObjID());
	}
	m_allObject.clear();
}

Object* Scene::HavaObject(std::wstring objName)
{
	for (vector<Object*>::iterator itr = m_allObject.begin(); itr != m_allObject.end(); itr++)
	{
		if ((*itr)->GetObjName() == objName)
		{
			return *itr;
		}
	}
	return NULL;
}

Object* Scene::HavaObject(int objID)
{
	for (vector<Object*>::iterator itr = m_allObject.begin(); itr != m_allObject.end(); itr++)
	{
		if ((*itr)->GetObjID() == objID)
		{
			return *itr;
		}
	}
	return NULL;
}


void Scene::SortObject(std::vector<Object*>* objVec)
{
	sort(objVec->begin(),objVec->end(),mem_fun(&Object::OrderCompare));
}

std::vector<Object*> const& Scene::GetAllObject()
{
	return m_allObject;
}

std::vector<Object*>& Scene::HaveAllObject()
{
	return m_allObject;
}

bool Scene::DeleteObject(std::wstring objName)
{
	for (vector<Object*>::iterator itr = m_allDirtyObject.begin(); itr != m_allDirtyObject.end(); itr++)
	{
		if ((*itr)->GetObjName() == objName)
		{
			m_allDirtyObject.erase(itr);
			break;
		}
	}

	for (vector<Object*>::iterator itr = m_UnLoadObject.begin(); itr != m_UnLoadObject.end(); itr++)
	{
		if ((*itr)->GetObjName() == objName)
		{
			m_UnLoadObject.erase(itr);
			break;
		}
	}

	for (vector<Object*>::iterator itr = m_allObject.begin(); itr != m_allObject.end(); itr++)
	{
		if ((*itr)->GetObjName() == objName)
		{
			Object* tempObj = *itr;
			m_allObject.erase(itr);
			SAFE_DELETE(tempObj);
			return true;
		}
	}
	return false;
}

bool Scene::DeleteObject(int objID)
{
	for (vector<Object*>::iterator itr = m_allDirtyObject.begin(); itr != m_allDirtyObject.end(); itr++)
	{
		if ((*itr)->GetObjID() == objID)
		{
			m_allDirtyObject.erase(itr);
			break;
		}
	}

	for (vector<Object*>::iterator itr = m_UnLoadObject.begin(); itr != m_UnLoadObject.end(); itr++)
	{
		if ((*itr)->GetObjID() == objID)
		{
			m_UnLoadObject.erase(itr);
			break;
		}
	}

	for (vector<Object*>::iterator itr = m_allObject.begin(); itr != m_allObject.end(); itr++)
	{
		if ((*itr)->GetObjID() == objID)
		{
			Object* tempObj = *itr;
			m_allObject.erase(itr);
			SAFE_DELETE(tempObj);
			return true;
		}
	}
	return false;
}

bool const& Scene::GetGameEnd() const
{
	return m_gameEnd;
}

void Scene::SetGameEnd(bool val)
{
	m_gameEnd = val;
}

void Scene::DirtyObject()
{
	if (m_DitryRectVec.size() == 0)
	{
		return;
	}

	//现在要将含有脏矩形列表中的矩形“污染”所有对象
	for (vector<Object*>::const_iterator itr = HaveAllObject().begin(); itr != HaveAllObject().end(); itr++)
	{
		bool dirtyObj = false;
		for (vector<LGRect>::const_iterator itr2 = m_DitryRectVec.begin();
			itr2 != m_DitryRectVec.end();
			++itr2)
		{
			if (Util::isCollsionWithRect((*itr)->GetSpriteRect(),*itr2))
			{
				(*itr)->ReceiveDirty(Util::CalCrossRect(*itr2,(*itr)->GetSpriteRect()));
				dirtyObj = true;
			}
		}
		if (dirtyObj)
		{
			InsertDirtyObject(*itr);
		}
	}

}

void Scene::ClearDirty()
{
	// 清除场景中的脏矩形
	m_DitryRectVec.clear();
	// 清除脏对象自身的脏部位
	if (g_pLGCenter->GetCurrentScene())
	{
		vector<Object*> currentObjVec = g_pLGCenter->GetCurrentScene()->GetAllDirtyObject();
		for (vector<Object*>::const_iterator itrObj = currentObjVec.begin(); itrObj != currentObjVec.end(); ++itrObj)
		{
			(*itrObj)->clearDirty();
		}
	}
	// 清除标记的脏对象
	m_allDirtyObject.clear();
}

std::vector<Object*> const& Scene::GetUnLoadObject() const
{
	return m_UnLoadObject;
}

void Scene::hadLoadAll()
{
	m_UnLoadObject.clear();
}

std::vector<Object*> const& Scene::GetAllDirtyObject()
{
	SortObject(&m_allDirtyObject);
	return m_allDirtyObject;
}

void Scene::InsertDirtyObject(Object* obj)
{
	m_allDirtyObject.push_back(obj);
}

void Scene::DirtyScene(LGRect dirtyRect)
{
	
	for (std::vector<LGRect>::const_iterator itr = m_DitryRectVec.begin(); itr != m_DitryRectVec.end(); )
	{
		if(Util::CollisionInsideRect(dirtyRect,*itr))
		{
			return;
		}
		else if(Util::CollisionInsideRect(*itr,dirtyRect))
		{
			m_DitryRectVec.erase(itr);
			itr = m_DitryRectVec.begin();
		}
		else
		{
			++itr;
		}
	}

	m_DitryRectVec.push_back(dirtyRect);
}
