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
	Defines the DzRsrThumb class.
**/

#ifndef DAZ_RSR_THUMB_H
#define DAZ_RSR_THUMB_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QImage;
class QRect;
class QString;
class DzRsrThumbFileIO;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzRsrThumb {
public:

	//
	// CREATORS
	//

	DzRsrThumb();
	~DzRsrThumb();

	//
	// MANIPULATORS
	//

	bool	load( const QString &path );

	//
	// ACCESSORS
	//

	QImage	getImage() const;


private:

	//
	// MANIPULATORS
	//

	bool	readRsrFile( DzRsrThumbFileIO *fileIO );
	bool	readHeader( DzRsrThumbFileIO *fileIO );
	bool	readDirectBits( DzRsrThumbFileIO *fileIO );
	bool	readPixMapBlock( DzRsrThumbFileIO *fileIO );
	bool	readPixData( DzRsrThumbFileIO *fileIO, int width, int height );
	void	setScanLine( char *bytes, int width, int lineNum );
	bool	readRect( DzRsrThumbFileIO *fileIO, QRect &rect );
	bool	unpackBytes( char *unpackedBuf, const char *packedBuf, int numPackedBytes, int maxUnpackedSize );

	struct	Data;
	Data	*m_data;
};

#endif //_DAZ_RECT_H

