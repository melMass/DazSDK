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
	Defines the DzImportMgr class.
**/

#ifndef DAZ_IMPORT_MGR_H
#define DAZ_IMPORT_MGR_H
/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzClassFactory;
class DzFileFilter;
class DzFileIOSettings;
class DzFileLoadFilter;
class DzImporter;
class DzShape;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzImportMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	//
	// CREATORS
	//

	DzImportMgr();
	~DzImportMgr();

public:

	//
	// MANIPULATORS
	//

	DzError	readGeometry( const QString &filename, DzShape **shape, int importerIdx = -1 );
	DzError	readGeometry( const QString &filename, DzShape **shape, int importerIdx, const DzFileIOSettings *options );

public slots:

	DzError		readFile( const QString &filename, int importerIdx = -1, DzFileLoadFilter *filter = NULL );
	DzError		readFile( const QString &filename, int importerIdx, const DzFileIOSettings *options, DzFileLoadFilter *filter = NULL );
	DzShape*	readGeometry( const QString &filename, int importerIdx = -1 );
	DzShape*	readGeometry( const QString &filename, int importerIdx, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	bool	isImporting() const;
	QString	getImportPath() const;
	void	setImportPath( const QString &path );

	QString	getImportFileName() const;
	void	setImportFileName( const QString &fileName );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	int				getNumImporters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzImporter*		getImporter( int i );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	bool			canImport( const QString &filename );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	int				findImporterIndex( const QString &filename );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	DzImporter*		findImporter( const QString &filename );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	DzImporter*		findImporterByClassName( const QString &className );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	void			makeImportFileFilter( DzFileFilter &filter, 
							const QString &defaultFilter = QString::null, 
							bool makeAllFilesEntry = true );

// MOC_SKIP_BEGIN
	static 
// MOC_SKIP_END
	void			makeGeometryFileFilter( DzFileFilter &filter, 
							const QString &defaultFilter = QString::null,
							bool makeAllFilesEntry = true );

public:

	static void		getImporterInfo( int i, QStringList &extensions, QString &description, 
							bool *isGeometryImporter = NULL );

signals:

	void	fileImportStarting();
	void	fileImported();

protected:

	static void	addClass( DzClassFactory *type );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_IMPORT_MGR_H
