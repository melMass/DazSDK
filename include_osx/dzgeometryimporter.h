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
	Defines the DzGeometryImporter class.
**/

#ifndef DAZ_GEOMETRY_IMPORTER_H
#define DAZ_GEOMETRY_IMPORTER_H

/****************************
	Include files
****************************/

#include "dzimporter.h"

/****************************
	Forward declarations
****************************/

class DzShape;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzGeometryImporter : public DzImporter {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzGeometryImporter();
	virtual ~DzGeometryImporter();

public slots:

	//
	// MANIPULATORS
	//

	virtual DzError	readFile( const QString &filename, DzShape **shape );
	virtual DzError	readFile( const QString &filename, DzShape **shape,
						const DzFileIOSettings *options );

protected:

	virtual DzError	read( const QString &filename, const DzFileIOSettings *options );
	virtual DzError	read( const QString &filename, DzShape **shape,
						const DzFileIOSettings *options ) = 0;
};

#endif // DAZ_GEOMETRY_IMPORTER_H
