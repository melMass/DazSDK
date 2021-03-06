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
	Declares global functions for switching byte order of multi-byte values.
**/

#ifndef DAZ_BYTE_UTIL_H
#define DAZ_BYTE_UTIL_H

#include "dzgeneraldefs.h"

/******************************************
	Function Declarations
******************************************/

DZ_EXPORT void	switchEndian( unsigned short *val );
DZ_EXPORT void	switchEndian( unsigned int *val );
DZ_EXPORT void	switchEndian( quint64 *val );

/******************************************
	Inline convenience functions
******************************************/

inline void	switchEndian( short *val )		{ ::switchEndian( (unsigned short *) val ); }
inline void	switchEndian( int *val )		{ ::switchEndian( (unsigned int *) val ); }
inline void	switchEndian( qint64 *val )		{ ::switchEndian( (quint64 *) val ); }
inline void	switchEndian( float *val )		{ ::switchEndian( (unsigned int *) val ); }
inline void	switchEndian( double *val )		{ ::switchEndian( (quint64 *) val ); }

inline void	switchEndian( unsigned short &val )	{ ::switchEndian( &val ); }
inline void	switchEndian( unsigned int &val )	{ ::switchEndian( &val ); }
inline void	switchEndian( quint64 &val )		{ ::switchEndian( &val ); }
inline void	switchEndian( short &val )			{ ::switchEndian( &val ); }
inline void	switchEndian( int &val )			{ ::switchEndian( &val ); }
inline void	switchEndian( qint64 &val )			{ ::switchEndian( &val ); }
inline void	switchEndian( float &val )			{ ::switchEndian( &val ); }
inline void	switchEndian( double &val )			{ ::switchEndian( &val ); }

/******************************************
	Portability Macros
******************************************/

#ifdef Q_OS_WIN

#define DZ_SWITCH_IF_BIG_ENDIAN( val )
#define DZ_SWITCH_IF_LITTLE_ENDIAN( val ) ::switchEndian( val );

#else

#define DZ_SWITCH_IF_BIG_ENDIAN( val ) \
	if( QSysInfo::ByteOrder == QSysInfo::BigEndian ){ \
		::switchEndian( val ); \
	}
#define DZ_SWITCH_IF_LITTLE_ENDIAN( val ) \
	if( QSysInfo::ByteOrder == QSysInfo::LittleEndian ){ \
		::switchEndian( val ); \
	}

#endif

#endif // DAZ_BYTE_UTIL_H
