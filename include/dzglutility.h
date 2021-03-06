/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This is UNPUBLISHED PROPRIETARY SOURCE CODE of DAZ 3D, Inc.
	the contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of DAZ 3D, Inc.
**********************************************************************/
#ifndef DAZ_GL_UTILITY_H
#define DAZ_GL_UTILITY_H

/*****************************
	Include files
*****************************/

#include "dzopengl.h"

/*****************************
	Forward Declarations
*****************************/

class DzBox3;
class DzOrientedBox3;
class DzLine3;
class DzVec3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzGLUtility {
public:

	static void		drawBox( const DzOrientedBox3 &box, bool solidShade = true );
	static void		drawBox( const DzBox3 &box, bool solidShade = true );

	static void		drawCircle( int nSegs, float radius = 1.0f, int axis = 0, bool solid = false, float offset = 0.0f );
	static void 	drawCircle( float minValue, float maxValue, int nSegs, float radius = 1.0f, int axis = 0, bool solid = false, float offset = 0.0f );
	static void		drawSphere( int nSegs, float radius = 1.0f, int axis = 0, bool solid = false );
	static void		drawDisk( float inner, float outer, int slices, int loops );

	static DzLine3	pixelToRay( int x, int y );
	static float	displayToPerspectiveSize( float displaySize, const DzVec3 &pos );

private:

	static void		drawWireBox( const DzBox3 &box );
	static void		drawSolidBox( const DzBox3 &box );

	static void	initCircleVals();
};

#endif // DAZ_GL_UTILITY_H
