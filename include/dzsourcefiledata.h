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
	Defines the DzSourceFileData class.
**/

#ifndef DAZ_SOURCE_FILE_DATA_H
#define DAZ_SOURCE_FILE_DATA_H

/*****************************
	Include files
*****************************/

#include "dzcustomdata.h"

/*****************************
	Definitions
*****************************/

#define DZ_SOURCE_FILE_DATA_NAME		"SourceFileData"
#define DZ_GEOM_SOURCE_FILE_DATA_NAME	"GeomSourceFileData"

/*****************************
	Forward declarations
*****************************/

class DzInFile;
class DzOutFile;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSourceFileData : public DzElementData {
	Q_OBJECT
	Q_PROPERTY( QString sourceFilePath READ getSourceFilePath WRITE setSourceFilePath )
public:
	DzSourceFileData( const QString &filePath = QString::null );
	~DzSourceFileData();

	void	loadSection( DzInFile *file, short sectionID );
	void	postLoadFile( const DzInFile *file );
	void	save( DzOutFile *file ) const;

	virtual QString	getSourceFilePath() const;
	virtual void	setSourceFilePath( const QString &filePath );
	virtual DzElementData* duplicate( DzElement* owner ) const;

public slots:

	virtual QString	getPoserRuntimeRelativePath();
	virtual void	setGeometryChanged( bool onoff );
	virtual bool	getGeometryChanged() const;

protected:
	DzSourceFileData( const QString &name, const QString &filePath );

private:
	QString	m_sourceFilePath;
	bool	m_geomChanged;
};

class DZ_EXPORT DzGeomSourceFileData : public DzSourceFileData {
	Q_OBJECT
	Q_PROPERTY( QString groupName READ getGroupName WRITE setGroupName )
public:
	DzGeomSourceFileData( const QString &filePath = QString::null, const QString &groupName = QString::null );
	~DzGeomSourceFileData();

	void	loadSection( DzInFile *file, short sectionID );
	void	save( DzOutFile *file ) const;

	QString	getGroupName() const;
	void	setGroupName( const QString &groupName );
	
	virtual DzElementData* duplicate( DzElement* owner ) const;

private:
	QString m_groupName;
};

#endif // DAZ_SOURCE_FILE_DATA_H