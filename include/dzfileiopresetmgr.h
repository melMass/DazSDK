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
	Defines the DzFileIOPresetMgr class.
**/

/*****************************
	Include files
*****************************/

#include "dzfileiosettings.h"

/*****************************
	Forward declarations
*****************************/

class DzImporter;
class DzExporter;

/*****************************
	Definitions
*****************************/

#ifndef DAZ_FILE_IO_PRESET_MGR_H
#define DAZ_FILE_IO_PRESET_MGR_H

#define DZ_PRESET_MGR_COMMON_LABEL				"Common"
#define DZ_PRESET_MGR_CUSTOM_LABEL				"Custom"
#define DZ_PRESET_MGR_CUSTOM_ID					0

#define DZ_PRESET_MGR_LAT_AXIS_KEY				"LatAxis"
#define DZ_PRESET_MGR_VERT_AXIS_KEY				"VertAxis"
#define DZ_PRESET_MGR_DEPTH_AXIS_KEY			"DepthAxis"
#define DZ_PRESET_MGR_INVERT_LAT_AXIS_KEY		"InvertLatAxis"
#define DZ_PRESET_MGR_INVERT_VERT_AXIS_KEY		"InvertVertAxis"
#define DZ_PRESET_MGR_INVERT_DEPTH_AXIS_KEY		"InvertDepthAxis"
#define DZ_PRESET_MGR_SCALE_KEY					"Scale"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFileIOPresetMgr : public QObject
{
	Q_OBJECT
	friend class DzApp;
private:
	DzFileIOPresetMgr();
	~DzFileIOPresetMgr();

	void	initMgr();

public slots:
	QStringList	getAvailablePresets( const QString &className = QString::null ) const;
	QStringList getUserPresets( const QString &className = QString::null ) const;
	QStringList getSystemPresets( const QString &className = QString::null ) const;
	QStringList getAvailableClasses( const QString &presetName ) const;

	bool	isUserPreset( const QString &presetName ) const;
	bool	isSystemPreset( const QString &presetName ) const;

	bool	presetExists( const QString &presetName, const QString &className = QString::null ) const;
	bool	presetExists( int id, const QString &className = QString::null ) const;

	bool	saveUserPreset( const QString &presetName, const QString &className, bool keepCommonSettings, bool overwrite, const DzFileIOSettings *settings );
	bool	removeUserPreset( const QString &presetName, const QString &className );

	QString	getPresetName( int id, const QString &className = QString::null ) const;
	int		getPresetID( const QString &presetName, const QString &className = QString::null ) const;

	bool	getSpecificSettings( const QString &presetName, const QString &className, DzFileIOSettings *settings ) const;
	bool	getCommonSettings( const QString &presetName, DzFileIOSettings *settings ) const;
	bool	getCommonSettings( const QString &presetName, const QString &className, DzFileIOSettings *settings ) const;
	bool	getAllSettings( const QString &presetName, const QString &className, DzFileIOSettings *settings ) const;

	bool	getSpecificDefaults( const QString &className, DzFileIOSettings *settings ) const;
	bool	getCommonDefaults( const QString &className, DzFileIOSettings *settings ) const;
	bool	getAllDefaults( const QString &className, DzFileIOSettings *settings ) const;

	bool	getAllCurrentSettings( const QString &className, DzFileIOSettings *settings ) const;
	bool	getCurrentCommonSettings( const QString &className, DzFileIOSettings *settings ) const;
	bool	getCurrentSpecificSettings( const QString &className, DzFileIOSettings *settings ) const;

	void	getCommonApplicationDefaults( DzFileIOSettings *settings ) const;

	QString	getCustomPresetLabel() const;
	QString	getLateralAxisKey() const;
	QString	getVerticalAxisKey() const;
	QString	getDepthAxisKey() const;
	QString	getInvertLateralAxisKey() const;
	QString	getInvertVerticalAxisKey() const;
	QString	getInvertDepthAxisKey() const;
	QString	getScaleKey() const;

signals:
	void	presetLoadFinished();
	void	presetRemoved( const QString &presetName, const QString &className );
	void	presetAdded( const QString &presetName, const QString &className );

private:
	void	copySpecificSettings( const DzFileIOSettings *copyFrom, DzFileIOSettings *copyTo ) const;
	void	copyCommonSettings( const DzFileIOSettings *copyFrom, DzFileIOSettings *copyTo ) const;
	bool	isCommonKey( const QString &key ) const;
	bool	getImporterDefaults( const QString &className, DzFileIOSettings *settings ) const;
	bool	getExporterDefaults( const QString &className, DzFileIOSettings *settings ) const;
	bool	getCurrentImporterSettings( const QString &className, DzFileIOSettings *settings ) const;
	bool	getCurrentExporterSettings( const QString &className, DzFileIOSettings *settings ) const;

	DzImporter*	getImporter( const QString &className ) const;
	DzExporter*	getExporter( const QString &className ) const;

	struct Data;
	Data *m_data;
};

#endif //DAZ_FILE_IO_PRESET_MGR_H