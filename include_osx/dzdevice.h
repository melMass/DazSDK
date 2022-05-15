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
	Defines the DzDeviceMgr class.
**/

#ifndef DAZ_DEVICE_H
#define DAZ_DEVICE_H

/****************************
	Include files
****************************/

#include "dzoptionsframe.h"

/****************************
	Forward declarations
****************************/

class DzSettings;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzDeviceFrame : public DzOptionsFrame {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzDeviceFrame( const QString &label, QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzDeviceFrame();

	virtual void	setOptions( const DzSettings &settings ) = 0;
	virtual void	getOptions( DzSettings &settings ) const = 0;
};

class DZ_EXPORT DzDevice : public QObject {
	Q_OBJECT
	friend class DzDeviceMgr;
protected:
	//
	// CONSTRUCTORS
	//

	DzDevice();
	virtual ~DzDevice();

public:

	//
	// ACCESSORS
	//

	virtual DzDeviceFrame*	getOptionsFrame() const;

public slots:

	//
	// MANIPULATORS
	//

	virtual void	setSettings( const DzSettings &settings ) = 0;
	void			setSettings(const DzSettings *settings ){ setSettings(*settings); }
	//
	// ACCESSORS
	//

	virtual QString	getDeviceName() const = 0;
	virtual QString	getDescription() const = 0;
	virtual void	getSettings( DzSettings &settings ) const = 0;
	virtual void	getDefaultSettings( DzSettings &settings ) const = 0;
	void	getSettings( DzSettings *settings) const { getSettings( *settings); }
	void	getDefaultSettings( DzSettings *settings) const { getDefaultSettings( *settings); }
};

#endif // DAZ_DEVICE_H