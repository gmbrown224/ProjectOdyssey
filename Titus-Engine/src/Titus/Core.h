#pragma once

#include "TEpch.h"

#if defined(_WIN32)
	#if defined(TE_BUILD_DLL)
		#define TITUS_API __declspec(dllexport)
	#elif defined(TE_USE_DLL)
		#define TITUS_API __declspec(dllimport)
	#else
		#define TITUS_API
	#endif
#else
	#define TITUS_API
#endif

#ifndef TE_API
	#define TE_API TITUS_API
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