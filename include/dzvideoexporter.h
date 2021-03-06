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
	Defines the DzVideoExporter class.
**/

#ifndef DAZ_VIDEO_EXPORTER_H
#define DAZ_VIDEO_EXPORTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"

/****************************
	Forward declarations
****************************/

class DzVideoClip;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzVideoExporter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzVideoExporter( const QString &extension );
	virtual ~DzVideoExporter();

public slots:
	//
	// MANIPULATORS
	//

	DzError	saveClip( const QString &filename, const DzVideoClip *clip );
	DzError	saveClip( const QString &filename, const DzVideoClip *clip, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	QString	getExtension() const;

	virtual QString getDescription() const = 0;
	virtual bool	isFileExporter() const = 0;

protected:

	virtual DzError	write( const QString &filename, const DzVideoClip *clip, const DzFileIOSettings *options ) = 0;

private:
	QString	m_extension;
};

#endif // DAZ_VIDEO_EXPORTER_H
