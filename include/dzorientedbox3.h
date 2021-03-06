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
	Defines the DzOrientedBox3 class.
**/

#ifndef DAZ_ORIENTED_BOX3_H
#define DAZ_ORIENTED_BOX3_H

/*****************************
	Include files
*****************************/

#include "dzmatrix3.h"

/****************************
	Forward declarations
****************************/

class DzVec3;
class DzQuat;
class DzBox3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzOrientedBox3 {
public:
	//
	// CREATORS
	//

	// Constructor(s)

	DzOrientedBox3();
	DzOrientedBox3( const DzVec3 &translation, const DzQuat &rotation, const DzVec3 &scale );
	DzOrientedBox3( const DzMatrix3 &transform );
	DzOrientedBox3( const DzBox3 &box, const DzVec3 &translation, const DzQuat &rotation, const DzVec3 &scale );
	DzOrientedBox3( const DzBox3 &box, const DzMatrix3 &transform );
	DzOrientedBox3( const DzOrientedBox3 &box );

	//
	// MANIPULATORS
	//

	void	setBox( const DzBox3 &box );
	void	setLocalMin( const DzVec3 &pnt );
	void	setLocalMax( const DzVec3 &pnt );
	void	include( const float pnt[3] );
	void	include( const DzVec3 &pnt );
	void	include( const DzBox3 &box );
	void	include( const DzOrientedBox3 &box );
	void	includeLocal( const float pnt[3] );
	void	includeLocal( const DzVec3 &pnt );
	void	includeLocal( const DzBox3 &box );
	void	rotate( const DzQuat &rot );
	void	translate( const DzVec3 &vec );
	void	scale( const DzVec3 &scale );
	void	transform( const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale );
	void	transform( const DzMatrix3 &transform );

	void	setTransform( const DzVec3 &pos, const DzQuat &rot, const DzVec3 &scale );
	void	setTransform( const DzMatrix3 &transform );

	//
	// ACCESSORS
	//

	bool		isValid() const;
	void		getPoints( DzVec3 pnts[8] ) const;
	DzMatrix3	getTransform() const;
	DzBox3		getBox() const;
	DzVec3		getLocalMin() const;
	DzVec3		getLocalMax() const;
	float		getSize() const;
	bool		operator==( const DzOrientedBox3 &v2 ) const;
	bool		operator!=( const DzOrientedBox3 &v2 ) const;

private:

	float		m_min[3], m_max[3];
	DzMatrix3	m_transform, m_transformInv;
	bool		m_initialized;
};

Q_DECLARE_METATYPE( DzOrientedBox3 );

#endif // DAZ_ORIENTED_BOX3_H
