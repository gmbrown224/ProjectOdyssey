#pragma once

#ifdef TE_PLATFORM_WINDOWS
	#ifdef TE_BUILD_DLL
		#define TITUS_API _declspec(dllexport)
	#else
		#define TITUS_API _declspec(dllimport)
	#endif
#else
	#error Titus only supports Windows!
#endif