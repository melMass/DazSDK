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
	Defines the DzFileIOSettings class.
**/

#ifndef DAZ_FILE_IO_SETTINGS_H
#define DAZ_FILE_IO_SETTINGS_H

/*****************************
	Include files
*****************************/

#include "dzsettings.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFileIOSettings : public DzSettings {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzFileIOSettings();
	DzFileIOSettings( const DzFileIOSettings *settings );
	~DzFileIOSettings();
};

#endif // DAZ_FILE_IO_SETTINGS_H
