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
	@sdk
	@file
	General definitions for the DAZ Studio SDK.
**/

#ifndef DAZ_GENERAL_DEFS_H
#define DAZ_GENERAL_DEFS_H

/*****************************
	Includes
*****************************/
#include <assert.h>

#include <QtCore/QGlobalStatic>
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <QtCore/QString>

#ifdef Q_OS_MAC
#include <stddef.h>
#endif

/*****************************
	Type definitions
*****************************/
/** General interface location enumeration **/
typedef enum en_DzLocation {
	DzTop,		/**< Top Location **/
	DzBottom,	/**< Bottom Location **/
	DzLeft,		/**< Left Location **/
	DzRight,	/**< Right Location **/
	DzCenter	/**< Center Location **/
} DzLocation;

/** Basic 2 value floating point vector type **/
typedef float DzPnt2[2];

/** Basic 3 value floating point vector type **/
typedef float DzPnt3[3];

/**
	Scene Time type - represents scene time in 'ticks' which is defined as 4800 ticks per second.
	@sa DZ_TICKS_PER_SECOND
**/
typedef int DzTime;

/** Scene time in D|S is measured in ticks - this defines the number of 'ticks' per second of real time. **/
#define	DZ_TICKS_PER_SECOND 4800

/** The maximum valid scene time in ticks **/
#define DZ_MAX_TIME			::DzTime(0x7fffffff)

/** The minimum valid scene time in ticks **/
#define DZ_MIN_TIME 		::DzTime(0xffffffff)

/*****************************
	Definitions
*****************************/

#define	DZ_DBL_DEG_TO_RAD	0.017453292519943296
#define	DZ_FLT_DEG_TO_RAD	0.01745329f
#define	DZ_DBL_RAD_TO_DEG	57.295779513082321
#define	DZ_FLT_RAD_TO_DEG	57.2957795f
#define DZ_FLT_MAX 			3.402823466e+38F
#define DZ_FLT_MIN 			1.175494351e-38F
#define DZ_FLT_EPSILON		1.192092896e-07F
#define DZ_DBL_EPSILON		2.2204460492503131e-016
#define DZ_DBL_MAX			1.7976931348623158e+308
#define DZ_DBL_MIN			2.2250738585072014e-308
#define DZ_INT_MAX 			0x7fffffff
#define DZ_INT_MIN 			0x80000000
#define DZ_SHORT_MAX 		((short)0x7fff)
#define DZ_SHORT_MIN 		((short)0x8000)
#define DZ_USHORT_MAX 		0xffff
#define DZ_PI				3.14159265359
#define DZ_FLT_PI			3.1415927f
#define DZ_2_PI				6.28318530718
#define DZ_FLT_2_PI			6.2831853f
#define DZ_HALF_PI			1.57079632680
#define DZ_FLT_HALF_PI		1.5707963f
#define DZ_FLT_INV_HALF_PI	0.6366197f
#define	DZ_KILOBYTE			1024
#define DZ_MEGABYTE			1048576
#define DZ_GIGABYTE			1073741824

// Standard DAZ Studio file extensions
#define DZ_SCENE_EXT			"daz"
#define DZ_OBJECT_FILE_EXT		"dso"
#define DZ_DELTAS_FILE_EXT		"dsd"
#define DZ_VERTEX_MAP_EXT		"dsv"
#define DZ_CUSTOM_IMAGE_EXT		"dsi"
#define DZ_ASSET_FILE_EXT		"dsf"
#define DZ_USER_SCENE_FILE_EXT	"duf"

#define DZ_NUM_OF(array_) (sizeof(array_)/sizeof(array_[0]))

#if defined(Q_OS_WIN) && defined(_DEBUG)
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(char const *text);
#endif

inline void DzWarning(const char *file, unsigned line, QString const &text)
{	
#if defined(Q_OS_WIN) && defined(_DEBUG)
#pragma comment(lib, "kernel32.lib")
	QString message = QString("%1(%2): %3\n").arg(file).arg(line).arg(text);
	QByteArray messageBytes = message.toAscii();
	OutputDebugStringA(messageBytes.constData());
#else
	QString fileName = QString::fromLatin1(file);
	
#if defined(Q_OS_MAC)
	static const QString c_src = QString::fromLatin1("/src/");
	int srcIdx = fileName.lastIndexOf(c_src,-1,Qt::CaseInsensitive);
	if( srcIdx > 0 ){
		fileName = fileName.mid(srcIdx);
	}
#endif

	QString message = QString("%1(%2): %3").arg(fileName).arg(line).arg(text);
	QByteArray messageBytes = message.toAscii();
	qWarning("%s", messageBytes.constData());
#endif
}
#define DZ_WARNING(text_) DzWarning(__FILE__, __LINE__, text_)

#if defined( Q_OS_WIN64 ) || defined( Q_OS_MAC64 )
#define DZ_64_BIT
#endif

/**
	@sdk
	Does a QObject::DzConnect(), but asserts if the connection fails.
**/
inline void DzConnect(const QObject *sender, const char *signal,
						const QObject *receiver, const char *member)
{
	bool result = QObject::connect(sender,signal,receiver,member);
	assert(result && "QObject connection failed");
}

/**
	@sdk
	Does a QObject::connect(), but asserts if the connection fails.
**/
inline void DzConnect(const QObject *sender, const char *signal,
						const QObject *receiver, const char *member,Qt::ConnectionType connectionType)
{
	bool result = QObject::connect(sender,signal,receiver,member,connectionType);
	assert(result && "QObject connection failed");
}

/*****************************
	Required platform abstractions
*****************************/
// Define the things that will handle DLL symbols on Windows platforms.
#if defined( DZ_NO_EXPORT )
#	define DZ_EXPORT
#elif defined( Q_OS_WIN )
#	ifdef DZ_MAKEDLL // Create a DLL library
#		define DZ_EXPORT __declspec(dllexport)
#	else	// Use a DLL library
#		define DZ_EXPORT __declspec(dllimport)
#	endif
#elif defined( Q_OS_MAC )
#	ifdef DZ_MAKEDLL // Create a DLL library
#		define DZ_EXPORT __attribute__((visibility("default")))
#	else	// Use a DLL library
#		define DZ_EXPORT
#	endif
#else
#	define DZ_EXPORT
#endif

#ifndef DSON_IO
#define DSON_EXPORT
#else
#define DSON_EXPORT DZ_EXPORT
#endif

/*****************************
	Memory management for template classes
*****************************/
DZ_EXPORT void dzFree( void * );
DZ_EXPORT void *dzMalloc( size_t );

/**
	@sdk
	Registers an object to be deleted when dzcore.dll cleans up its static members.
**/
DZ_EXPORT void dzRegisterStaticObject( QObject *obj );

/**
	@sdk
	Template function to determine if a QObject is an instance of a particular class.
	@return	true if the object is an instance of the type, false if the class is not an
			instance of the type, or is an instance of a child class of the type.
**/
template <typename T>
bool dzIsA( const QObject *obj )
{
	if( !obj )
		return false;

	return (strcmp( T::staticMetaObject.className(), obj->metaObject()->className() ) == 0);
}

#ifndef DSON_IO
#define DSON_EXPORT
#else
#define DSON_EXPORT DZ_EXPORT
#endif

#endif // DAZ_GENERAL_DEFS_H
