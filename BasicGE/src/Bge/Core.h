#pragma once

#if 0
#	ifdef BGE_WIN64
#		if !defined(BGE_BUILD_STATIC) && defined(BGE_BUILD_SHARED) 
#			define BGE_API __declspec(dllexport)
#		elif defined(BGE_BUILD_SHARED)
#			define BGE_API __declspec(dllimport)
#		endif
#		
#		if defined(BGE_BUILD_STATIC)
#			define BGE_API
#		endif
#	else
#		error BGE does currently only supports win64
#	endif
#endif

#ifndef BGE_API
#	define BGE_API
#endif

#define BIT(x) (1 << x)

#ifdef BGE_ENABLE_ASSERTIONS
#	define BGE_ASSERT(cond) { if(!cond) { __debugbreak(); } }
#	define BGE_CORE_ASSERT(cond) { if(!cond) { __debugbreak(); } }
#else
#	define BGE_ASSERT(cond)
#	define BGE_CORE_ASSERT(cond)
#endif