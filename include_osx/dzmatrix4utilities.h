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

#ifndef DZ_MATRIX4_UTILITIES_H
#define DZ_MATRIX4_UTILITIES_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzVec3;
class DzQuat;
class DzMatrix4;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMatrix4Utilities{
public:
	DzMatrix4Utilities() {};
	~DzMatrix4Utilities() {};

	static void decomposeMatrix( const DzMatrix4 &mat, DzVec3 &position, DzVec3 &scale, DzVec3 &rotation, DzQuat &quatRotations );
};

#endif //#ifndef DZ_MATRIX4_UTILITIES_H