#include "Scene.h"
#include <algorithm>
#include <xfunctional>
#include "Object.h"

using namespace std;

Scene* g_pCurrentScene = 0;

Scene::Scene() : m_gameEnd(false)
{
	
}

bool Scene::SameName(Object* const& lhs, wstring const& name)
{
	if (lhs->GetObjName() == name)
	{
		return true;
	}
	return false;
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


std::vector<Object*> const& Scene::GetAllObject_Sort()
{
	sort(m_allObject.begin(),m_allObject.end(),mem_fun(&Object::OrderCompare));
	return GetAllObject();
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

void Scene::DirtyRectInfect()
{
	if (m_allDetectDirtyRect.size() == 0 && m_allDirtyObject.size() == 0)
	{
		return;
	}

	vector<Object*> allCleanObject;

	//检测未脏对象
	for (vector<Object*>::const_iterator itr = m_allObject.begin(); itr != m_allObject.end(); itr++)
	{
		if (!(*itr)->GetDirty())
		{
			allCleanObject.push_back((*itr));
		}
	}

	//将脏对象的精灵矩形导出到脏矩形检测列表
	for (vector<Object*>::const_iterator itr = m_allDirtyObject.begin(); itr != m_allDirtyObject.end(); itr++)
	{
		InsertDetectDirtyRect((*itr)->GetSpriteRect());
	}

	//现在要将含有脏矩形列表中的矩形“感染”未脏对象
	for (vector<Object*>::const_iterator itr = allCleanObject.begin(); itr != allCleanObject.end(); itr++)
	{
		bool dirtyObj = false;
		for (vector<LGRect>::const_iterator itr2 = m_allDetectDirtyRect.begin();
			itr2 != m_allDetectDirtyRect.end();
			++itr2)
		{
			if (Util::isCollsionWithRect((*itr)->GetSpriteRect(),*itr2))
			{
				(*itr)->SetRectDirty(Util::CalCrossRect(*itr2,(*itr)->GetSpriteRect()));
				dirtyObj = true;
			}
		}
		if (dirtyObj)
		{
			InsertDetectDirtyObject(*itr);
		}
	}

	ClearDirtyRect();
}

void Scene::ClearDirtyRect()
{
	m_allDetectDirtyRect.clear();
}

void Scene::ClearDirtyObject()
{
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
	sort(m_allDirtyObject.begin(),m_allDirtyObject.end(),mem_fun(&Object::OrderCompare));
	return m_allDirtyObject;
}

void Scene::InsertDetectDirtyObject(Object* obj)
{
	m_allDirtyObject.push_back(obj);
}

void Scene::InsertDetectDirtyRect(LGRect dirtyRect)
{
	
	for (std::vector<LGRect>::const_iterator itr = m_allDetectDirtyRect.begin(); itr != m_allDetectDirtyRect.end(); )
	{
		if(Util::CollisionInsideRect(dirtyRect,*itr))
		{
			return;
		}
		else if(Util::CollisionInsideRect(*itr,dirtyRect))
		{
			m_allDetectDirtyRect.erase(itr);
			itr = m_allDetectDirtyRect.begin();
		}
		else
		{
			++itr;
		}
	}

	m_allDetectDirtyRect.push_back(dirtyRect);
}
