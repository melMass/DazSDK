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
	Defines the DzBox3 class.
**/

#ifndef DAZ_BOX3_H
#define DAZ_BOX3_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzVec3;
class DzLine3;
class DzMatrix3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzBox3 {
public:
	//
	// CREATORS
	//

	// Constructor(s)

	DzBox3();
	DzBox3( float xmin, float ymin, float zmin, float xmax, float ymax, float zmax );
	DzBox3( const float min[3], const float max[3] );
	DzBox3( const DzVec3 &min, const DzVec3 &max );
	DzBox3( const DzBox3 &box );

	//
	// MANIPULATORS
	//

	void		setMin( const DzVec3 &pnt );
	void		setMax( const DzVec3 &pnt );
	void		include( const float pnt[3] );
	void		include( const DzVec3 &pnt );
	void		include( const DzBox3 &box );
	void		operator+=( const DzVec3 &obj );
	void		operator-=( const DzVec3 &obj );

	//
	// ACCESSORS
	//

	bool		isValid() const;
	DzVec3		getMin() const;
	DzVec3		getMax() const;
	float		getSize() const;
	DzVec3		getCenter() const;
	bool		operator==( const DzBox3 &box ) const;
	bool		operator!=( const DzBox3 &box ) const;
	DzBox3		operator*( const DzMatrix3 &mat ) const;

	bool		testIntersection( const DzLine3 &ray, float tolerance ) const;
	bool		getIntersection( const DzLine3 &ray, DzVec3 *firstIntersection, DzVec3 *lastIntersection ) const;

private:

	bool		testPlaneIntersection( const DzVec3 &norm, float d, const DzVec3 &origin,
					const DzVec3 &delta, DzVec3 *lastIntersection, DzVec3 *firstIntersection ) const;
	bool		testPlaneIntersection( const DzVec3 &norm, const DzLine3 &ray, float tolerance ) const;

	float		m_min[3], m_max[3];
	bool		m_initialized;
};

Q_DECLARE_METATYPE( DzBox3 );

#endif // DAZ_BOX3_H
