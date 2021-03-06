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
	Defines the DzStorable class.
**/

#ifndef DAZ_STORABLE_H
#define DAZ_STORABLE_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzversion.h"
#include "dzrefcounteditem.h"
#include "dzuri.h"

/****************************
	Forward declarations
****************************/

class DzOutFile;
class DzInFile;
class DzStorable;
class DzUri;
class DzLegacySourceInfo;
class DzFileIOSettings;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStorable : public DzBase, public DzRefCountedItem {
	Q_OBJECT
	friend class DzInFile;
	friend class DzAssetFile;
public:
	//
	// CONSTRUCTOR/DESTRUCTOR
	//

	DzStorable();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	setStorablePaths( const QString &path );
	virtual void	save( DzOutFile *file ) const;
	virtual void	loadSection( DzInFile *file, short sectionID );
	
	//
	// MANIPULATORS
	//

	DzError	loadFromFile();

	void	setLegacySourceInfo( const DzLegacySourceInfo &legacySourceInfo );	
	void	setUri( const DzUri &uri, bool markChanged = true );

public slots:

	void	markChanged();
	void	resetFileName();

public:

	//
	// ACCESSORS
	//

	virtual bool	isShareable() const { return true; }
	
	DzLegacySourceInfo	getLegacySourceInfo() const;


public slots:

	virtual bool	usesDeferredLoading() const { return false; }
	virtual QString	getExtension() const = 0;
	virtual QString	getFiletype() const = 0;
	virtual bool	needsSave( const QString &filename ) const;
	bool			hasChanged() const;
	bool			hasFilename() const;
	QString			getFilename() const;
	QString			getFullFilename() const;
	DzVersion		getFileVersion() const;
	bool			fileExists() const;

	bool			hasUri() const;
	DzUri			getUri() const;

	bool			wasLoadedFromNativeFile()const;

	//
	// STATIC
	//

#ifndef Q_MOC_RUN
	static
#endif
	DzStorable*		find( const QString &filename );

#ifndef Q_MOC_RUN
	static
#endif
	DzStorable*		find( const DzUri &uri );

// MOC_SKIP_BEGIN
	static 
//MOC_SKIP_END
	int				getNumStorablesInScene();

signals:

	void			unableToFindFile( const QString &file );

protected:

	virtual ~DzStorable();

	//
	// MANIPULATORS
	//

	virtual void	writeData( DzOutFile *file ) const { }
	void			setFilename( const QString &filename, bool markChanged = true );

private:
	void	removeFromGlobalList();
	void	addToGlobalList();

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzLegacySourceInfo {
public:
	DzLegacySourceInfo();
	DzLegacySourceInfo( const DzLegacySourceInfo &legacySourceInfo );
	~DzLegacySourceInfo();

	DzLegacySourceInfo&	operator=( const DzLegacySourceInfo &legacySourceInfo );

	QString getFilePath() const;
	void setFilePath( const QString &filePath );
	void setFilePathFromAbsolutePath( const QString &absolutePath );

	QStringList getLocatorIDs() const;
	int getNumLocatorIDs() const;
	QString getLocatorID( int i ) const;
	void setLocatorIDs( const QStringList &locatorIDs );
	void appendLocatorID( QString locatorID );

	void fromString( const QString &sourceInfoString );
	QString toString() const;

	DzFileIOSettings& getSettings()const;
	void	setSettings( const DzFileIOSettings *settings );

	bool	isMeshModified()const;
	void	setMeshModified( bool yesNo );

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STORABLE_H
