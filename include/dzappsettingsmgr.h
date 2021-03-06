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
	Defines the DzAppSettingsMgr class.
**/

#ifndef DAZ_APP_SETTINGS_MGR_H
#define DAZ_APP_SETTINGS_MGR_H

/****************************
	Include files
****************************/

#include <QtCore/QObject>
#include <QtGui/QColor>

#include "dzgeneraldefs.h"

/****************************
	Class Definitions
****************************/

class DZ_EXPORT DzAppSettingsMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	//
	// CONSTRUCTORS
	//

	DzAppSettingsMgr();
	~DzAppSettingsMgr();

public slots:
	//
	// MANIPULATORS
	//

	void	pushPath( const QString &path );
	void	popPath();
	bool	setBoolValue( const QString &key, bool setting );
	bool	setIntValue( const QString &key, int setting );
	bool	setFloatValue( const QString &key, double setting );
	bool	setStringValue( const QString &key, const QString &setting );
	bool	setColorValue( const QString &key, const QColor &setting );
	bool	removeValue( const QString &key );

	//
	// ACCESSORS
	//

	bool	getBoolValue( const QString &key, bool def = false, bool *ok = NULL ) const;
	int		getIntValue( const QString &key, int def = 0, bool *ok = NULL ) const;
	double	getFloatValue( const QString &key, float def = 0.0f, bool *ok = NULL ) const;
	QString	getStringValue( const QString &key, const QString &def = QString::null, bool *ok = NULL ) const;
	QColor	getColorValue( const QString &key, const QColor &def = Qt::black, bool *ok = NULL ) const;

private:

	void	removeAllSettings();
	void	removeAllSettingsRecurse( const QString &key );
	QString	formatKey( const QString &key ) const;

	//
	// DATA MEMBERS
	//

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_APP_SETTINGS_MGR_H