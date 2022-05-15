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
	Defines the DzExportMgr class.
**/

#ifndef DAZ_EXPORTER_MGR_H
#define DAZ_EXPORTER_MGR_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzClassFactory;
class DzExporter;
class DzFileFilter;
class DzFileIOSettings;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzExportMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	//
	// CREATORS
	//

	DzExportMgr();
	~DzExportMgr();

public slots:
	//
	// MANIPULATORS
	//

	DzError	exportFile( const QString &fileName, int exporterIndex );
	DzError	exportFile( const QString &fileName, int exporterIndex, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	QString	getExportPath() const;
	void	setExportPath( const QString &path );

	bool    isExporting() const;

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumExporters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzExporter*		getExporter( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	bool			canExport( const QString &filename );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int				findExporterIndex( const QString &filename );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzExporter*		findExporter( const QString &filename );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzExporter*		findExporterByClassName( const QString &className );


// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	void			makeExportFileFilter( DzFileFilter &filter, 
							const QString &defaultFilter = QString::null );

public:

	static void		getExporterInfo( int i, QString &extension, QString &description );

signals:

	void	fileExportStarting();
	void	fileExported();

protected:

	static void	addClass( DzClassFactory *type );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_EXPORTER_MGR_H
