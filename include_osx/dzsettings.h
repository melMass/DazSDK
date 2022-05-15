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
	Defines the DzSettings class.
**/

#ifndef DAZ_SETTINGS_H
#define DAZ_SETTINGS_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class QDomDocument;
class QDomElement;
class DzSetting;
class DzScript;
class IDzJsonIO;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzSettings : public QObject {
	Q_OBJECT
	Q_ENUMS( Type )
public:
	enum Type { StringValue, IntValue, BoolValue, FloatValue, SettingsValue };

	//
	// CREATORS
	//

	DzSettings();
	DzSettings( const DzSettings *settings );
	virtual ~DzSettings();

	bool	fromDOM( const QDomElement &root );
	void	toDOM( QDomDocument &doc, QDomElement &root ) const;
	bool	toJson( IDzJsonIO *io, const QString &tag = QString::null ) const;

	void	copySetting( const QString &key, DzSettings &copyTo ) const;
	void	copySetting( int which, DzSettings &copyTo ) const;

public slots:

	void		setStringValue( const QString &key, const QString &value );
	void		setIntValue( const QString &key, int value );
	void		setBoolValue( const QString &key, bool value );
	void		setFloatValue( const QString &key, double value );
	DzSettings*	setSettingsValue(const QString &key, const DzSettings *settings);
	DzSettings*	setSettingsValue(const QString &key);
	void		removeValue( const QString &key );
	void		clear();

	QString		getStringValue( const QString &key, const QString &def = QString::null ) const;
	int			getIntValue( const QString &key, int def = 0 ) const;
	bool		getBoolValue( const QString &key, bool def = false ) const;
	double		getFloatValue( const QString &key, float def = 0.0f ) const;
	DzSettings*	getSettingsValue( const QString &key) const;
	int			getSettingIndex( const QString &key ) const;

	int			getNumValues() const;
	int			hasKey( const QString &key ) const;
	QString		getKey( int which ) const;
	Type		getValueType( int which ) const;
	QString		getValue( int which ) const;

	bool		fromString( const QString &settings );
	QString		toString() const;

	void		copySetting( const QString &key, DzSettings *copyTo ) const;
	void		copySetting( int which, DzSettings *copyTo ) const;

	void		replaceWithSettings(const DzSettings *settings);
	void		toScript( const QString &varName, DzScript *script, int indent, bool writeCreatation = false ) const;

private:

	DzSetting*	findSetting( const QString &name ) const;
	void		stringToScript( const QString &varName, DzScript *script, int indent, const DzSetting &setting ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_SETTINGS_H
