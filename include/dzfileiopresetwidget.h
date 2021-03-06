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
	Defines the DzFileIOPresetWidget class.
**/

#ifndef DAZ_FILE_IO_PRESET_WGT_H
#define DAZ_FILE_IO_PRESET_WGT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/*****************************
	Constants
*****************************/

#define DZ_PRESET_WGT_LAT_AXIS_KEY				"LatAxis"
#define DZ_PRESET_WGT_VERT_AXIS_KEY				"VertAxis"
#define DZ_PRESET_WGT_DEPTH_AXIS_KEY			"DepthAxis"
#define DZ_PRESET_WGT_INVERT_LAT_AXIS_KEY		"InvertLatAxis"
#define DZ_PRESET_WGT_INVERT_VERT_AXIS_KEY		"InvertVertAxis"
#define DZ_PRESET_WGT_INVERT_DEPTH_AXIS_KEY		"InvertDepthAxis"
#define DZ_PRESET_WGT_SCALE_KEY					"Scale"

/*****************************
	Forward declarations
*****************************/

class DzFileIOSettings;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFileIOPresetWidget : public QWidget {
	Q_OBJECT
public:
	enum ConversionType {
		Import = 0,
		Export,
	};

	enum Axis {
		X_Axis = 0,
		Y_Axis,
		Z_Axis,
		INVALID_AXIS
	};
		
	//
	// CREATORS
	//

	DzFileIOPresetWidget( QWidget *parent, ConversionType type, const QString &className, const QString &name = QString::null );
	virtual ~DzFileIOPresetWidget();

	//
	// ACCESSORS
	//

	QString			getPresetName() const;
	QString			getPresetClassName() const;
	void			getPresetNameSetting( DzFileIOSettings *settings ) const;
	void			getSpecificSettings( DzFileIOSettings *settings, 
										bool includeName = false ) const;

	void			getCommonSettings( DzFileIOSettings *settings, 
										bool includeName = false ) const;

	void			getAllSettings( DzFileIOSettings *settings, 
									bool includeName = false ) const;

	virtual void	getSpecificDefaults( DzFileIOSettings *settings, 
										bool includeName = false ) const;

	void			getCommonDefaults( DzFileIOSettings *settings, 
										bool includeName = false ) const;

	void			getAllDefaults( DzFileIOSettings *settings, 
									bool includeName = false ) const;

	QString			getLatAxis() const;
	QString			getVertAxis() const;
	QString			getDepthAxis() const;
	bool			getInvertLatAxis() const;
	bool			getInvertVertAxis() const;
	bool			getInvertDepthAxis() const;
	float			getScaleVal() const;

	ConversionType	getConversionType() const;
	virtual QSize	minimumSizeHint() const;
	void			setSettings( const DzFileIOSettings *options );

	bool			showIndividualSettings() const;

	//
	// MANIPULATORS
	//
	void	setConversionType( ConversionType type );
	void	addWidget( QWidget *wgt );
	void	setImportTitle( const QString &title );
	void	setExportTitle( const QString &title );
	void	setShowIndividualSettings( bool show );

public slots:
	bool	usePreset( const QString &presetName );
	bool	usePreset( int id );
	bool	saveUserPreset( const QString &presetName, bool keepCommonSettings, 
							bool keepSpecificSettings, bool makeActive = true);
	bool	removeUserPreset( const QString &presetName );
	bool	removeUserPreset( int id );

protected slots:
	void			userChangedPresetOptions();
	virtual void	showInterface( bool show );

signals:
	void			showSettingsToggled();

protected:
	virtual void	getSettingsFromInterface( DzFileIOSettings *settings ) const;
	virtual void	updateInterface( DzFileIOSettings *settings, bool blockSigs );

private:
	void	init();
	void	updateInterface( DzFileIOSettings *settings = NULL);
	void	setActivePreset( int id );
	void	setupPresets();
	void	lateralAxisComboChanged( int index, bool setToCustom );
	void	verticalAxisComboChanged( int index, bool setToCustom );
	void	depthAxisComboChanged( int index, bool setToCustom );
	void	updateTitle();
	void	addPresetToMenu( int id );
	
	void	updateScale( float scale, bool blockSignals );
	void	updateLateralAxis( const QString &axis, bool blockSigs );
	void	updateVerticalAxis( const QString &axis, bool blockSigs );
	void	updateDepthAxis( const QString &axis, bool blockSigs );
	void	updateLateralAxisInversion( bool invert, bool blockSigs );
	void	updateVerticalAxisInversion( bool invert, bool blockSigs );
	void	updateDepthAxisInversion( bool invert, bool blockSigs );
	Axis	convertStringToAxis( const QString &axis ) const;
	void	updatePresetLabel();

private slots:
	void	aboutToShowPresetMenu();
	void	menuIDSelected( int id );
	void	lateralAxisChanged( int index );
	void	verticalAxisChanged( int index );
	void	depthAxisChanged( int index );
	void	updateSaveButtonState();
	void	saveUserPreset();
	void	removeUserPreset();
	void	toggleShowSettings();
	void	presetListChanged(const QString &presetName, const QString &className);

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_FILE_IO_PRESET_WGT_H