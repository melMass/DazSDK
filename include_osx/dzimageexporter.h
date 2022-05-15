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
	Defines the DzImageExporter class.
**/

#ifndef DAZ_IMAGE_EXPORTER_H
#define DAZ_IMAGE_EXPORTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzImageExporter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzImageExporter( const QString &extension );
	virtual ~DzImageExporter();

public slots:
	//
	// MANIPULATORS
	//

	DzError	saveImage( const QString &filename, const QImage &image );
	DzError	saveImage( const QString &filename, const QImage &image, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	QString			getExtension() const;
	virtual QString	getDescription() const = 0;
	virtual bool	isFileExporter() const = 0;

protected:

	virtual DzError	write( const QString &filename, const QImage &image, const DzFileIOSettings *options ) = 0;

private:
	//
	// DATA MEMBERS
	//

	// The extension to force the filename to when opening the file for writing.
	// If no extension is given, the filename is left alone.
	QString	m_extension;
};

#endif // DAZ_IMAGE_EXPORTER_H
