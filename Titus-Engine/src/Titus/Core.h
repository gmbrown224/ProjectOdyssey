#pragma once

#include "TEpch.h"

#ifdef TE_PLATFORM_WINDOWS
	#ifdef TE_BUILD_DLL
		#define TITUS_API _declspec(dllexport)
	#else
		#define TITUS_API _declspec(dllimport)
	#endif
#else
	#error Titus only supports Windows!
#endif

#ifdef TE_ENABLE_ASSERTS
	#define TE_ASSERT(x, ...) { if(!(x)) { TE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TE_CORE_ASSERT(x, ...) { if(!(x)) { TE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TE_ASSERT(x, ...)
	#define TE_CORE_ASSERT(x, ...)
#endif

#define TE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)