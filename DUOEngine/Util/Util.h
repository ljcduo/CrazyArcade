
#pragma once
#include <tchar.h>
#include <sstream>
#include <thread>
#include <cstdio>
#include <cstdarg>
#include <cwchar>
#include <cstdlib>
#include <windows.h>

#define CHECK_TO_RETURN(point) if (!point)	return;

#define SAFE_DELETE(point) if (point) {delete (point); (point) = 0;}

namespace Util
{
	//delete Map中指针值
	template<typename T>
	void MapSecondDelete(T &delMap)
	{
		for (T::iterator itr = delMap.begin(); itr != delMap.end(); itr++)
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

	struct DebugOutImpl {
		DebugOutImpl(const char* location, int line, bool enabled_ = true)
			:enabled(enabled_)
		{
			ss << location << line << "): " /*<< std::this_thread::get_id() << " - " */;
		}
		~DebugOutImpl() { ss << '\n'; OutputDebugStringA(ss.str().c_str()); }
		void operator()(const char* msg) { if (enabled) ss << msg; }
		void operator()(const wchar_t* msg) { if (enabled) ss << wtoa(msg); }
		std::ostringstream& operator()() { return ss; }
		template<class char_type>
		void operator()(const char_type* format, ...) {
			if (enabled) {
				char_type buf[4096];
				va_list ap;
				va_start(ap, format);
				vsnprintf_s(buf, 4096, format, ap);
				va_end(ap);
				operator()(buf);
			}
		}
	private:
		static std::string wtoa(const wchar_t* ptr, size_t len = -1) {
			if (len == -1) len = wcslen(ptr);
			std::string r(WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, len, nullptr, 0, 0, 0), '\0');
			if (r.size() == 0) throw std::system_error(GetLastError(), std::system_category());
			if (0 == WideCharToMultiByte(CP_THREAD_ACP, 0, ptr, len, &r[0], r.size(), 0, 0))
				throw std::system_error(GetLastError(), std::system_category(), "error converting wide string to narrow");
			return r;
		}
		static inline std::string wtoa(const std::wstring& wstr) { return wtoa(&wstr[0], wstr.size()); }
		static int vsnprintf_s(char* buffer, int bufsize, const char* format, va_list ap) { return ::vsnprintf_s(buffer, bufsize, _TRUNCATE, format, ap); }
		static int vsnprintf_s(wchar_t* buffer, int bufsize, const wchar_t* format, va_list ap) { return ::vswprintf_s(buffer, bufsize, format, ap); }

		std::ostringstream ss;
		bool enabled;
	};
	#define DebugOut DebugOutImpl(__FILE__ "(", __LINE__)	
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