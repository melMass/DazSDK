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
	Defines the DzQuat class.
**/

#ifndef DAZ_QUAT_H
#define DAZ_QUAT_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzMatrix4;
class DzMatrix3;
class DzRotationOrder;
class DzVec3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzQuat {
public:

	DzQuat();
	DzQuat( const float quat[4], bool normalize = true );
	DzQuat( double q0, double q1, double q2, double q3, bool normalize = true );
	DzQuat( const DzVec3 &axis, float radians );
	DzQuat( DzRotationOrder order, const DzVec3 &angles );
	DzQuat( const DzMatrix4 &mtx );
	DzQuat( const DzMatrix3 &mtx );
	DzQuat( const DzQuat &quat );

	//
	// MANIPULATORS
	//

	void	setValue( float q0, float q1, float q2, float q3, bool normalize = true );
	void	setValue( const float vec[4], bool normalize = true );
	void	setValue( const DzVec3 &axis, float radians );
	void	setValue( int axis, float radians );
	void	setValue( const DzVec3 &vec );
	void	setValue( const DzVec3 &xAxis, const DzVec3 &yAxis );
	void	setValue( const DzMatrix4 &mtx );
	void	setValue( const DzMatrix3 &mtx );
	void	setValue( DzRotationOrder order, const DzVec3 &angles );
	void	setValue( const DzQuat &quat );
	void	invert();
	DzQuat&	operator*=( const DzQuat &q );
	void	makeClosest( const DzQuat &r );
	void	scaleAngle( float scaleFactor );
	void	makeIdentity();
	void	normalize();

	//
	// ACCESSORS
	//

	void	getValue( float &q0, float &q1, float &q2, float &q3 ) const;
	void	getValue( float vec[4] ) const;
	void	getValue( DzRotationOrder order, DzVec3 &angles ) const;
	void	getValue( DzVec3 &axis, float &radians ) const;
	void	getValue( DzVec3 &vec ) const;
	void	getValue( DzMatrix4 &m ) const;
	void	getValue( DzMatrix3 &m ) const;
	void	getXAxis( DzVec3 &vec ) const;
	void	getYAxis( DzVec3 &vec ) const;
	void	getZAxis( DzVec3 &vec ) const;
	DzQuat	inverse() const;
	DzQuat	operator*( const DzQuat &q ) const;
	bool	operator==( const DzQuat &rot ) const;
	bool	operator!=( const DzQuat &rot ) const;
	bool	equals( const DzQuat &q, float tolerance = 1e-05 ) const;
	DzVec3	multVec( const DzVec3 &src ) const;
	void	multPnt( DzPnt3 &src ) const;
	bool	isIdentity() const;

	//
	// STATIC
	//

	static DzQuat	slerp( const DzQuat &rot0, const DzQuat &rot1, float t );
	static DzQuat	identity();
	static void		removeGimbal( DzRotationOrder order, const DzVec3 &rotVec1, DzVec3 &rotVec2 );
	static void		makeCloseToZero( DzRotationOrder order, DzVec3 &rotVec );
	double			&operator[]( int i );
	double			operator[]( int i ) const;

	//
	// DATA MEMBERS
	//

	double	m_x, m_y, m_z, m_w;

private:

	float	norm() const;
	DzVec3	getDirectionVec() const;
	float	dot( const DzQuat &r ) const;
};

Q_DECLARE_METATYPE( DzQuat );

#endif // DAZ_QUAT_H
