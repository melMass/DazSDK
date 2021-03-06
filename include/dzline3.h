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
	Defines the DzLine3 class.
**/

#ifndef DAZ_LINE3_H
#define DAZ_LINE3_H

/*****************************
	Include files
*****************************/

#include "dzvec3.h"

/*****************************
	Class definitions
*****************************/

class Q_DECL_EXPORT DzLine3 {
public:
	//
	// CREATORS
	//

	DzLine3();
	DzLine3( const DzVec3 &origin, const DzVec3 &end );
	DzLine3( const DzLine3 &vin );

	//
	// MANIPULATORS
	//

	void	setOrigin( const DzVec3 &pnt );
	void	setEnd( const DzVec3 &pnt );
	void	setEnds( const DzVec3 &origin, const DzVec3 &end );
	
public slots:
	void	negate();
	void	setLength( float length );
	void	swapEnds();

public:
	//
	// ACCESSORS
	//

	const DzVec3&	getOrigin() const;
	const DzVec3&	getEnd() const;
	bool			operator==( const DzLine3 &line ) const;
	bool			operator!=( const DzLine3 &line ) const;

public slots:	
	float			minDistance( const DzLine3 &line1, float &s, float &t ) const;
	float			minDistance( const DzVec3 &pnt, float &s, bool clampEnds = false ) const;
	float			minDistanceSquared( const DzVec3 &pnt, float &s, bool clampEnds = false ) const;
	bool			segmentsIntersect( const DzLine3 &line, DzVec3 &intersection, float tolerance = 0.0f ) const;
	bool			linesIntersect( const DzLine3 &line, DzVec3 &intersection, float tolerance = 0.0f ) const;
	bool			planeIntersect( const DzVec3 &planePoint, const DzVec3 &planeNormal, float &t, DzVec3 &intersection ) const;
	float			length( float t = 1.0f ) const;
	DzVec3			getPoint( float t ) const;
	DzVec3			getDirection() const;

private:

	DzVec3	m_origin, m_end;
};

Q_DECLARE_METATYPE( DzLine3 );

#endif // DAZ_LINE3_H
