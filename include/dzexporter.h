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
	Defines the DzExporter class.
**/

#ifndef DAZ_EXPORTER_H
#define DAZ_EXPORTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"

/****************************
	Define statements
****************************/
#define DZ_INCHES_PER_MM		0.0393700f
#define DZ_FEET_PER_MM			0.0032808f
#define DZ_METERS_PER_MM		0.0010000f
#define DZ_CM_PER_MM			0.1000000f

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzExporter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzExporter( const QString &extension );
	virtual ~DzExporter();

public slots:

	//
	// MANIPULATORS
	//

	DzError	writeFile( const QString &filename );
	DzError	writeFile( const QString &filename, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	QString			getExtension() const { return m_extension; }
	virtual QString getDescription() const = 0;
	virtual bool	isFileExporter() const = 0;

protected:
	//
	// MANIPULATORS
	//

	virtual DzError	write( const QString &filename, const DzFileIOSettings *options ) = 0;

private:

	QString	m_extension;
};

#endif // DAZ_EXPORTER_H
