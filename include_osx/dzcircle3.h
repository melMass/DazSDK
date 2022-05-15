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
	Defines the DzCircle3 class.
**/

#ifndef DAZ_CIRCLE3_H
#define DAZ_CIRCLE3_H

/*****************************
	Include files
*****************************/

#include "dzvec3.h"

/****************************
	Forward declarations
****************************/

class DzLine3;

/*****************************
	Class definitions
*****************************/

class Q_DECL_EXPORT DzCircle3 {
public:
	//
	// CREATORS
	//

	DzCircle3();
	DzCircle3( const DzVec3 &center, const DzVec3 &normal, float radius );
	DzCircle3( const DzCircle3 &vin );

	//
	// MANIPULATORS
	//

	void			setCenter( const DzVec3 &pnt );
	void			setNormal( const DzVec3 &pnt );
	void			setRadius( float val );
	void			setAttributes( const DzVec3 &center, const DzVec3 &normal, float radius );

	//
	// ACCESSORS
	//

	const DzVec3&	getCenter() const;
	const DzVec3&	getNormal() const;
	float			getRadius() const;
	bool			minDistToLine( const DzLine3 &line, DzVec3 &lineClosest,
						DzVec3 &circleClosest ) const;
	bool			operator==( const DzCircle3 &circle ) const;
	bool			operator!=( const DzCircle3 &circle ) const;

private:

	double			evaluate( int degree, double *a, const double &x ) const;
	int				bisection( int digits, double epsilon, double x0, double x1,
						int degree, double *a, double &xroot ) const;
	void			getRootsOnInterval( int digits, double epsilon, double xmin,
						double xmax, int degree, double *a, int &count, double *root ) const;
	void			getAllRoots( int digits, double epsilon, int degree, double *a,
						int &count, double *root ) const;

	DzVec3			m_normal, m_center;
	float			m_radius;
};

Q_DECLARE_METATYPE( DzCircle3 );

#endif // DAZ_CIRCLE3_H
