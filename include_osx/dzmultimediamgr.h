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
	@file
	Defines the DzMultiMediaMgr class.
**/

#ifndef DAZ_MULTI_MEDIA_MGR_H
#define DAZ_MULTI_MEDIA_MGR_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzAudioClip;
class DzAudioImporter;
class DzClassFactory;
class DzFileFilter;
class DzVideoClip;
class DzVideoExporter;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzMultiMediaMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
	friend class DzMMInternalClassFactory;
private:
	//
	// CREATORS
	//

	DzMultiMediaMgr();
	~DzMultiMediaMgr();

public slots:
	//
	// MANIPULATORS
	//

	DzError	exportVideoClip( const QString &fileName, const DzVideoClip *clip, int exporterIndex = -1 );
	DzError	importAudioClip( const QString &fileName, DzAudioClip *clip, int importerIndex = -1 );

	//
	// ACCESSORS
	//

	QString	getVideoClipSavePath() const;
	QString	getAudioClipLoadPath() const;

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumVideoExporters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzVideoExporter*	getVideoExporter( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzVideoExporter*	findVideoExporter( const QString &filename );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumAudioImporters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzAudioImporter*	getAudioImporter( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzAudioImporter*	findAudioImporter( const QString &filename );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	void	makeAudioImportFileFilter( DzFileFilter &filter, 
					const QString &defaultFilter = QString::null, 
					bool makeAllFilesEntry = true );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	void	makeVideoExportFileFilter( DzFileFilter &filter, 
					const QString &defaultFilter = QString::null );

public:

	static void	getVideoExporterInfo( int i, QString &extension, QString &description );
	static void	getAudioImporterInfo( int i, QString &extension, QString &description );

protected:

	static void	addClass( DzClassFactory *type );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_MULTI_MEDIA_MGR_H
