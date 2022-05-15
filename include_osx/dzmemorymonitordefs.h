/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ Studio SDK.

	This file may be used only in accordance with the DAZ Studio SDK
	license provided with the DAZ Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D or for more
	information about the DAZ Studio SDK.
**********************************************************************/

/**
	@internal
	@file
	Include this as first include in dzgeneraldefs.h to get a memory dump at close of a debug studio
**/

#ifndef DAZ_MEMORY_MONITOR_DEFS_H
#define DAZ_MEMORY_MONITOR_DEFS_H

/*****************************
	Includes
*****************************/

#if defined(Q_OS_WIN) && defined(_DEBUG) && !defined(TOOL_INCLUDE)
//these need to be included before define because new,free,etc are redefined.
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QRegExp>
#include <QtCore/QHash>
#include <QtCore/QMutex>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if defined( Q_OS_WIN )
#  ifdef DZ_MAKEDLL // Create a DLL library
#    define DZ_MEM_EXPORT  __declspec(dllexport)
#  else	// Use a DLL library
#    define DZ_MEM_EXPORT  __declspec(dllimport)
#  endif
#elif defined( Q_OS_MAC )
#  ifdef DZ_MAKEDLL // Create a DLL library
#    define DZ_MEM_EXPORT __attribute__((visibility("default")))
#  else	// Use a DLL library
#    define DZ_MEM_EXPORT
#  endif
#else
#  define DZ_MEM_EXPORT
#endif

DZ_MEM_EXPORT void* __cdecl dz_memNew(size_t _Size, int normBlock, const char *file, int lineNum, bool shouldTrack,bool keepStack);
DZ_MEM_EXPORT void* __cdecl dz_memNewArray(size_t _Size, int normBlock, const char *file, int lineNum, bool shouldTrack,bool keepStack);
DZ_MEM_EXPORT void __cdecl dz_memDel(void *p);
DZ_MEM_EXPORT void __cdecl dz_memDelArray(void *p);

inline void* __cdecl operator new(size_t _Size)
{ return dz_memNew(_Size,_NORMAL_BLOCK,__FILE__,__LINE__,false,false); }

inline void* __cdecl operator new[](size_t _Size)
{ return dz_memNewArray(_Size,_NORMAL_BLOCK,__FILE__ ,__LINE__ ,false,false); }

inline void * __cdecl operator new(size_t _Size,int block,const char *file,int line,bool shouldTrack,bool keepStack)
{ return dz_memNew(_Size,block,file,line,shouldTrack,keepStack); }

inline void * __cdecl operator new[](size_t _Size,int block,const char *file,int line,bool shouldTrack,bool keepStack)
{ return dz_memNewArray(_Size,block,file,line,shouldTrack,keepStack); }

inline void __cdecl operator delete(void *_P)
{ dz_memDel(_P); }

inline void __cdecl operator delete[](void *_P)
{ dz_memDelArray(_P); }

inline void __cdecl operator delete(void * _P, int, const char *, int,bool shouldTrack,bool keepStack)
{ ::operator delete(_P); }

inline void __cdecl operator delete[](void * _P, int, const char *, int,bool shouldTrack,bool keepStack)
{ ::operator delete[](_P); }

extern void dzCleanUpStaticDeleteList();

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__, true, false)
#define new DEBUG_NEW

#define DEBUG_STACK_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__, true, true)

#define DZ_MEM_FIX
#define DZ_MEM_MONITOR
#endif

#endif // DAZ_MEMORY_MONITOR_DEFS_H
