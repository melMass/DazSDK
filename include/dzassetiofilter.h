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
	Defines the DzAssetIOFilter class.
**/

#ifndef DAZ_ASSET_IO_FILTER_H
#define DAZ_ASSET_IO_FILTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"
#include "dzuri.h"

/****************************
	Class definitions
****************************/
class DzBase;
class DzAssetOutFile;

class DZ_EXPORT DzAssetIOFilter : public DzFileIO {
	Q_OBJECT
public:
	//
	// CREATORS/DESTRUCTORS
	//

	DzAssetIOFilter( const QString &description );
	virtual ~DzAssetIOFilter();

	static const QString s_userFileExtentionTitle;

	void setShouldSaveThumbnail(bool onOff);
	bool getShouldSaveThumbnail()const;

public slots:

	//
	// MANIPULATORS
	//

	DzError			doSave( QString &filePath, const QString &startingDir = QString() );
	virtual DzError	doSave( DzFileIOSettings *options, const QString &filePath, const QString &startingDir = QString() ) = 0;

	virtual DzUri	getAssetInstanceUri( DzBase *base ) const = 0;
	virtual DzUri	getAssetDefinitionUri( DzBase *base ) const = 0;

	//
	// ACCESSORS
	//

	virtual QString	getStandardSaveRelativePath() const = 0;
	virtual QString	getDoSavePath() const = 0;

	QString			getDescription() const;
	QString			getLoadSavePath() const;
	void			setLoadSavePath( const QString &str );

	virtual QString	getCompatiblityBase() const { return QString(); }
	virtual QString	getContentType() const { return QString(); }
	virtual bool	isSupportAssetFilter() const = 0;

protected:

	bool			doFileDialog( QString &filename, const QString &startingDir = QString(), bool userFile = true );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzAssetFileOutFilter : public DzAssetIOFilter {
	Q_OBJECT
public:
	DzAssetFileOutFilter( const QString &description );
	virtual ~DzAssetFileOutFilter();

	void			setAssetOutFile( DzAssetOutFile *outFile );
	DzAssetOutFile*	getAssetOutFile()const;
	
	virtual DzUri	getAssetInstanceUri( DzBase *base ) const;
	virtual DzUri	getAssetDefinitionUri( DzBase *base ) const;

protected:
	struct Data;
	Data* m_data;
};

#endif // DAZ_ASSET_IO_FILTER_H
