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
	Defines the DzVec3 class.
**/

#ifndef DAZ_VEC3_H
#define DAZ_VEC3_H

/*****************************
	Include files
*****************************/

#include "dzgeneraldefs.h"

/*****************************
	Forward declarations
*****************************/

class DzQuat;
class DzMatrix3;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzVec3 {
public:
	//
	// CREATORS
	//

	DzVec3();
	DzVec3( float x, float y, float z );
	DzVec3( const DzPnt3 p );
	DzVec3( const DzVec3 &v );

	//
	// MANIPULATORS
	//

	void			setValue( float x, float y, float z );
	void			setValue( const DzPnt3 pnt );
	void			makeZero();
	void			makeIdentity();
	void			negate();
	void			setLength( float length );
	float			normalize();
	void			square();
	void			abs();
	operator		float*();
	void			operator+=( float val );
	void			operator+=( const DzVec3 &obj );
	void			operator+=( const DzPnt3 pnt );
	void			operator-=( float val );
	void			operator-=( const DzVec3 &obj );
	void			operator-=( const DzPnt3 pnt );
	void			operator*=( float val );
	void			operator*=( const DzVec3 &obj );
	void			operator*=( const DzPnt3 pnt );
	void			operator/=( float val );
	void			operator/=( const DzVec3 &v );
	void			operator/=( const DzPnt3 v );
	void			operator*=( const DzMatrix3 &mtx );
	float&			operator[]( int i );

	//
	// ACCESSORS
	//

	const float*	getValue() const;
	void			getValue( float &x, float &y, float &z ) const;
	void			getValue( DzPnt3 pnt ) const;
	float			length() const;
	double			dlength() const;
	float			lengthSquared() const;
	DzVec3			normalized() const;
	DzVec3			cross( const DzVec3 &vec ) const;
	float			dot( const DzVec3 &vec ) const;
	float			dot( const DzPnt3 vec ) const;
	float			getAngleTo( const DzVec3 &vec ) const;
	DzQuat			getRotationTo( const DzVec3 &vec ) const;
	DzVec3			operator+( float val ) const;
	DzVec3			operator+( const DzVec3 &v ) const;
	DzVec3			operator+( const DzPnt3 v ) const;
	Q_DECL_EXPORT friend DzVec3	operator+( float val, const DzVec3 &v );
	DzVec3			operator-( float val ) const;
	DzVec3			operator-( const DzVec3 &v ) const;
	DzVec3			operator-( const DzPnt3 v ) const;
	DzVec3			operator*( float val ) const;
	DzVec3			operator*( const DzVec3 &v ) const;
	DzVec3			operator*( const DzPnt3 v ) const;
	Q_DECL_EXPORT friend DzVec3	operator*( float val, const DzVec3 &v );
	DzVec3			operator/( float val ) const;
	DzVec3			operator/( const DzVec3 &v ) const;
	DzVec3			operator/( const DzPnt3 v ) const;
	Q_DECL_EXPORT friend DzVec3	operator/( float val, const DzVec3 &v );
	bool			operator==( const DzVec3 &v2 ) const;
	bool			operator!=( const DzVec3 &v2 ) const;
	DzVec3			operator-() const;
	float			operator[]( int i ) const;
	bool			equals( const DzVec3 &vec, float tolerance = 1e-6 ) const;

	//
	// STATIC
	//

	static DzVec3	identity();
	static DzVec3	zero();
	static DzVec3	linearInterp( float t, const DzVec3 &v1, const DzVec3 &v2 );

	//
	// DATA MEMBERS
	//

	float	m_x, m_y, m_z, m_w;
};

Q_DECLARE_METATYPE( DzVec3 );

inline void operator+=( DzPnt3 &pnt, const DzVec3 &vec )
{
	pnt[0] += vec.m_x;
	pnt[1] += vec.m_y;
	pnt[2] += vec.m_z;
}

inline void operator-=( DzPnt3 &pnt, const DzVec3 &vec )
{
	pnt[0] -= vec.m_x;
	pnt[1] -= vec.m_y;
	pnt[2] -= vec.m_z;
}

inline void operator*=( DzPnt3 &pnt, const DzVec3 &vec )
{
	pnt[0] *= vec.m_x;
	pnt[1] *= vec.m_y;
	pnt[2] *= vec.m_z;
}

inline void operator/=( DzPnt3 &pnt, const DzVec3 &vec )
{
	pnt[0] /= vec.m_x;
	pnt[1] /= vec.m_y;
	pnt[2] /= vec.m_z;
}

#endif // DAZ_VEC3_H
