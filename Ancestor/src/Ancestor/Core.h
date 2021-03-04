#pragma once

#ifdef AC_PLATFORM_WINDOWS
	#ifdef AC_BUILD_DLL
		#define ANCESTOR_API __declspec(dllexport)
	#else
		#define ANCESTOR_API __declspec(dllimport)
	#endif
#else
	#error Ancestor only support Windows!
#endif