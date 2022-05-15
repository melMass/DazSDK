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
	Utility functions for working with Qt ui files
**/

#ifndef DAZ_UI_UTILITIES_H
#define DAZ_UI_UTILITIES_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

namespace DzUiUtilities {
	/**
		@sdk
		Recursively converts the objectName of the baseObject and all of its children
		to match DAZ 3D internal naming standards.

		The current conversions are automatically done:
		Remove m_ or Dz from the beginning of the objectName
		Capitalize first letter of remaining objectName
	**/
	DZ_EXPORT void convertObjectNames( QObject *baseObject );
}

#endif // DAZ_UI_UTILITIES_H
