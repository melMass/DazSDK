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
	Defines the DzPresetWidget base class.
**/

#ifndef DAZ_PRESET_WIDGET_H
#define DAZ_PRESET_WIDGET_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzsettings.h"

/****************************
	Forward declarations
****************************/

class DzSettings;
class QDomElement;
class QFile;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPresetWidget : public QWidget {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzPresetWidget( QWidget *parent, const QString &presetFile, const QString &name = QString::null );
	virtual ~DzPresetWidget();

	//
	// ACCESSORS
	//

	QString	getActivePresetName() const;
	void	getSettings( DzSettings &settings, bool includeName = false ) const;
	void	setSettings( const DzSettings &settings );

	int		getPresetCount() const;
	int		getPresetIndex( const QString &name ) const;
	QString	getPresetName( int index ) const;
	QString	getCustomPresetName() const;

	bool	settingsShown() const;
	
	//
	// MANIPULATORS
	//
	void	addWidget( QWidget *widget, int stretch = 0 );
	void	addStretch( int stretch = 0 );

public slots:
	void	setPresetLabelWidth( int width );
	void	hideSettingsButton( bool hide );
	void	showSettings( bool shown );
	bool	usePreset( const QString &preset );
	bool	usePreset( int index );
	bool	savePreset( const QString &preset );
	bool	removePreset( const QString &preset );
	bool	removePreset( int index );

	void	initCustomPreset();

protected:
	void	getSettingsFromPreset( const QString &preset, DzSettings &settings ) const;
	bool	presetSavesToFile( const QString &name );
	void	setPresetSavesToFile( const QString &name, bool save );
	bool	prependPreset( const QString &name, bool userDefined = false, bool savesToFile = true );

	virtual void	getDefaultSettings( DzSettings &settings, bool includeName = false ) const = 0;
	virtual void	getSettingsFromInterface( DzSettings &settings ) const = 0;
	virtual void	updateInterface( const DzSettings &settings, bool blockSignals ) = 0;

protected slots:
	void	presetOptionsChanged();

private:
	void	init();
	void	setupPresets();
	void	loadPresets();
	void	loadPresetsFile( QFile &presetFile, bool userDefined );
	void	loadPresets( QDomElement &presetsElement, bool userDefined );
	void	loadPreset( QDomElement &presetElement, bool userDefined );
	void	writeUserPresets();

private slots:
	void	saveUserPreset();
	bool	removeUserPreset();
	void	toggleShowSettings();

signals:
	void	optionsChanged();
	void	showSettingsToggled();
	void	curPresetChanged();

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PRESET_WIDGET_H
