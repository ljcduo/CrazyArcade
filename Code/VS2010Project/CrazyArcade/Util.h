
#pragma once
#include <tchar.h>

#define SAFE_DELETE(point) delete (point); (point) = 0;


//单实例模式
#define SINGLETON(className) \
public: \
	static className* Instance() { static className instance; return &instance; } \
private: \
	className() {} \
	~className() {} \
	className(className const&); \
	className& operator=(className const&); 

#define SINGLETON_NOCTOR(className) \
public: \
	static className* Instance() { static className instance; return &instance; } \
private: \
	className(); \
	~className(); \
	className(className const&); \
	className& operator=(className const&); 


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