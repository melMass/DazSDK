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
	Defines the DzImageImporter class.
**/

#ifndef DAZ_IMAGE_IMPORTER_H
#define DAZ_IMAGE_IMPORTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzImageImporter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzImageImporter();
	virtual ~DzImageImporter();

public slots:
	//
	// MANIPULATORS
	//

	DzError	loadImage( const QString &filename, QImage &image );
	DzError	loadImage( const QString &filename, QImage &image, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	virtual bool	recognize( const QString &filename ) const = 0;
	virtual int		getNumExtensions() const = 0;
	virtual QString getExtension( int i ) const = 0;
	virtual QString getDescription() const = 0;

protected:

	virtual DzError	read( const QString &filename, QImage &img, const DzFileIOSettings *options ) = 0;

private:
	QString	m_extension;
};

#endif // DAZ_IMAGE_IMPORTER_H
