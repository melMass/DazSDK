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
	Defines the DzSaveFilter class.
**/

#ifndef DAZ_SAVE_FILTER_H
#define DAZ_SAVE_FILTER_H

/****************************
	Include files
****************************/

#include "dzfileio.h"
#include "dzscript.h"

/****************************
	Forward declarations
****************************/

class DzProgressIndicator;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzSaveFilter : public DzFileIO {
	Q_OBJECT
	Q_ENUMS( ScriptFileMode )

public:

	//NOTE: This enum is duplicated from DzScript for use in scripts!
	enum ScriptFileMode { UseExtension, TextScriptFile, DAZScriptFile, EncDAZScriptFile };

	//
	// CREATORS/DESTRUCTORS
	//

	DzSaveFilter( const QString &description );
	virtual ~DzSaveFilter();

	virtual bool getShouldSaveTextScriptOnly() const{ return false; }

public slots:

	//
	// MANIPULATORS
	//

	DzError	writeFile( const QString &filename, ScriptFileMode mode );
	DzError	writeFile( const QString &filename, ScriptFileMode mode, const DzFileIOSettings *options );

	//
	// ACCESSORS
	//

	QString	getDescription() const { return m_description; }
	QString	getLoadSavePath() const;
	void	setLoadSavePath( const QString &str );


protected:
	//
	// MANIPULATORS
	//

	virtual DzError	write( const QString &filename, DzScript::ScriptFileMode mode, const DzFileIOSettings *options ) = 0;

public:
	// TODO This is helper function to call the protected version
	//		of the base class DZFileIO, a more clean way of doing this
	//		is more desirable in the future.
	QString			GetPreIOErrorString();

private:

	QString	m_description;
};

class DZ_EXPORT DzContentTypedSaveFilter : public DzSaveFilter {
	Q_OBJECT
public:
	//
	// CREATORS/DESTRUCTORS
	//
	DzContentTypedSaveFilter( const QString &description );
	virtual ~DzContentTypedSaveFilter();

	virtual bool getShouldSaveTextScriptOnly() const{ return true; }

public slots:
	virtual QString		getContentType() const = 0;
	virtual QString		getStandardSaveRelativePath() const = 0;
	virtual QString		getCompatiblityBase() const = 0;
	virtual QStringList	getCompatibleWith() const;
};

#endif // DAZ_SAVE_FILTER_H
