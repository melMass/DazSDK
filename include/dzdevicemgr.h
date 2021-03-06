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

#ifndef DAZ_DEVICE_MGR_H
#define DAZ_DEVICE_MGR_H

/****************************
	Include files
****************************/

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzDevice;
class DzClassFactory;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzDeviceMgr : public QObject {
	Q_OBJECT
	friend class DzApp;
private:
	//
	// CONSTRUCTORS
	//

	DzDeviceMgr();
	~DzDeviceMgr();

public slots:

	//
	// ACCESSORS
	//

	int			getNumDevices();
	DzDevice*	getDevice( int which );

protected:

	//
	// MANIPULATORS
	//

	DzError	startup();

	//
	// STATIC
	//

	static void	addClass( DzClassFactory *type );
	
private:

	void	loadSettings( DzDevice *device ) const;
	void	saveSettings( DzDevice *device ) const;

	//
	// DATA MEMBERS
	//

	//
	// DATA MEMBERS
	//

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DEVICE_MGR_H