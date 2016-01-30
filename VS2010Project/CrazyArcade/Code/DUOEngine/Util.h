
#pragma once
#include <tchar.h>

#define CHECK_TO_RETURN(point) if (!point)	return;

#define SAFE_DELETE(point) delete (point); (point) = 0;

namespace Util
{
	//delete Map中指针值
	template<typename T>
	void MapSecondDelete(T &delMap)
	{
		for(T::iterator itr = delMap.begin(); itr != delMap.end(); itr++)
		{
			SAFE_DELETE(itr->second);
		}
	}

	//delete vector中指针值
	template<typename T>
	void VectorDelete(T &vec)
	{
		for (T::iterator itr = vec.begin(); itr != vec.end(); itr++)
		{
			SAFE_DELETE(*itr);
		}
	}

	bool _trace(char *format, ...);

}

//---------------------------------------------------单实例模式-Begin---------------------------------------------------
#define SINGLETON_PART_CTOR(className) \
private: \
	className() {} \
	~className() {} 

#define SINGLETON_PART_NOCTOR_NORMAL(className) \
private: \
	className(); \
	~className(); 

#define SINGLETON_PART_NOCTOR_INHERIT(className) \
protected: \
	className(); \
	~className(); 

#define SINGLETON_PART_COPY_NORMAL(className) \
private: \
	className(className const&); \
	className& operator=(className const&);

#define SINGLETON_PART_COPY_INHERIT(className) \
protected: \
	className(className const&); \
	className& operator=(className const&);

#define SINGLETON_PART_INSTANCE_NORMAL(className) \
public: \
	static className* Instance() { static className instance; return &instance; }

#define SINGLETON_PART_INSTANCE_INHERIT(className) \
public: \
	static className* Instance() { if(!m_instance) { static className instance; m_instance = &instance; } return m_instance; } \
protected: \
	static className* m_instance;

#define SINGLETON_PART_REGISTER(className) \
public: \
	static void RegisterDerive() { static className instance; m_instance = &instance; }

#define SINGLETON_CTOR(className) \
	SINGLETON_PART_INSTANCE_NORMAL(className) \
	SINGLETON_PART_CTOR(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON_NOCTOR(className) \
	SINGLETON_PART_INSTANCE_NORMAL(className) \
	SINGLETON_PART_NOCTOR_NORMAL(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON_INHERIT_BASE_HEADER_NOCTOR(className) \
	SINGLETON_PART_INSTANCE_INHERIT(className) \
	SINGLETON_PART_NOCTOR_INHERIT(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON_INHERIT_BASE_HEADER_CTOR(className) \
	SINGLETON_PART_INSTANCE_INHERIT(className) \
	SINGLETON_PART_CTOR(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON_INHERIT_BASE_CPP(className) className* className::m_instance = NULL;

#define SINGLETON_INHERIT_DERIVE_NOCTOR(className)\
	SINGLETON_PART_REGISTER(className) \
	SINGLETON_PART_NOCTOR_NORMAL(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON_INHERIT_DERIVE_CTOR(className)\
	SINGLETON_PART_REGISTER(className) \
	SINGLETON_PART_CTOR(className) \
	SINGLETON_PART_COPY_NORMAL(className)

#define SINGLETON(className) SINGLETON_NOCTOR(className)
#define SINGLETON_INHERIT_BASE_HEADER(className) SINGLETON_INHERIT_BASE_HEADER_NOCTOR(className)
#define SINGLETON_INHERIT_DERIVE(className) SINGLETON_INHERIT_DERIVE_NOCTOR(className)

//---------------------------------------------------单实例模式-End---------------------------------------------------