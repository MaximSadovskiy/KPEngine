#pragma once

#include "logging/Logger.h"

#define KPE_CHECK_WIN_PLATFORM _WIN32 || _WIN64 || __CYGWIN__ || __MINGW32__ || __BORLANDC__
#define KPE_CHECK_LIN_PLATFORM

#if KPE_CHECK_WIN_PLATFORM
	#define __KPE_WINDOW_PLATFORM__
#else
	#error "Not supported"
#endif

#ifdef __KPE_DEBUG__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_TRACE
	#define KPE_CONFIGURATION_STR "Debug"

	#ifdef __KPE_WINDOW_PLATFORM__
		#include <intrin.h>
		#define KPE_DEBUGBREAK() __debugbreak()
	#else
		#define KPE_DEBUGBREAK()
	#endif
#endif
#ifdef __KPE_RELEASE__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_DEBUG
	#define KPE_CONFIGURATION_STR "Release"
	#define KPE_DEBUGBREAK()
#endif
#ifdef __KPE_DIST__
	#define KPE_INITIAL_LOG_LEVEL Kpe::LEVEL_ERROR
	#define KPE_CONFIGURATION_STR "Distribution"
	#define KPE_DEBUGBREAK()
#endif