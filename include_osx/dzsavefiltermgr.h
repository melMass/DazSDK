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
	Defines the DzSaveFilterMgr class.
**/

#ifndef DAZ_SAVE_FILTER_MGR_H
#define DAZ_SAVE_FILTER_MGR_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzClassFactory;
class DzSaveFilter;
class DzProgressIndicator;
class DzAppSettingsMgr;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzSaveFilterMgr : public QObject {
	Q_OBJECT
	Q_ENUMS( ScriptFileMode )
	friend class DzApp;

public:

	//NOTE: This enum is duplicated from DzScript for use in scripts!
	enum ScriptFileMode { UseExtension, TextScriptFile, DAZScriptFile, EncDAZScriptFile };
	
	DzError	doSaveWithFilename( int filterIndex, QString &saveFileName, QString dir = QString::null, QString category = QString::null );

private:
	//
	// CREATORS
	//

	DzSaveFilterMgr();
	~DzSaveFilterMgr();

public slots:
	//
	// MANIPULATORS
	//

	DzError	writeFile( ScriptFileMode mode, const QString &fileName, const QString &filterName = "" );
	DzError	doSave( int filterIndex, QString dir = QString::null );
	
	//
	// ACCESSORS
	//

	QString	getSavePath() const;

	//
	// STATIC
	//

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		getNumFilters();

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	QString	getFilterName( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	DzSaveFilter*	getFilter( int i );

// MOC_SKIP_BEGIN
	static
// MOC_SKIP_END
	int		findFilter( const QString &className );

protected:

	static void	addClass( DzClassFactory *type );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SAVE_FILTER_MGR_H
