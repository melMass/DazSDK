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
	Defines the DzJsonReader class for parsing JSON from an I/O device.
**/

#ifndef DAZ_JSON_READER_H
#define DAZ_JSON_READER_H

/****************************
	Include files
****************************/

#include "idzjsonio.h"

/****************************
	Forward declarations
****************************/

class QIODevice;
class DzProgress;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzJsonReader {
public:

	DzJsonReader( QIODevice *device );
	virtual ~DzJsonReader();

	DzError	read( IDzJsonIO *interpreter );
	void	setProgressBar( DzProgress *progress );

private:

	bool	parse();
	bool	parseObject();
	bool	parseArray();
	bool	parseValue( const QString &memberName = QString::null );
	bool	parseString( QString &str );
	bool	parseFragment( const char *str );
	void	interpreterError();
	void	lineError( const QString &errMsg );
	
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_JSON_READER_H
