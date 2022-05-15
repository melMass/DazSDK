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
	Defines the DzMatrix3 class.
**/

#ifndef DAZ_MATRIX3_H
#define DAZ_MATRIX3_H

/*****************************
	Include files
*****************************/

#include "dzvec3.h"

/*****************************
	Type definitions
*****************************/

typedef float DzMat3[5][3];
typedef float DzMatRow[3];

/*****************************
	Forward declarations
*****************************/

class DzQuat;
class DzInFile;
class DzOutFile;
class DzMatrix4;

/*****************************
	Class definitions
*****************************/

class Q_DECL_EXPORT DzMatrix3 {
public:
	//
	// CREATORS
	//

	DzMatrix3( bool makeIdentity = false );
	DzMatrix3( const DzMatrix3 &m );
	DzMatrix3( const DzMat3 &m );
	DzMatrix3( const float vals[12] );
	DzMatrix3( const DzQuat &rot );
	DzMatrix3( const DzVec3 ax1, const DzVec3 ax2, const DzVec3 Ax3 );

	//
	// MANIPULATORS
	//

	DzMatrix3&	operator=( const DzMat3 &m );
	DzMatrix3&	operator=( const DzMatrix3 &m );
	void		makeIdentity();
	void		setValue( const float vals[16] );
	void		noTrans();
	void		noRot();
	void		noScale();
	void		orthogonalize();
	void		setTrans( const DzVec3 &pnt );
	void		translate( const DzVec3 &v );
	void		preTranslate( const DzVec3 &v );
	void		rotateX( float radians );
	void		rotateY( float radians );
	void		rotateZ( float radians );
	void		rotate( const DzQuat &rot );
	void		preRotateX( float radians );
	void		preRotateY( float radians );
	void		preRotateZ( float radians );
	void		preRotate( const DzQuat &rot );
	void		scale( float scale, bool affectTrans = false );
	void		scale( const DzVec3 &vec, bool affectTrans = false );
	void		scale( float scale, const DzVec3 &direction, bool affectTrans = false );
	void		shearXY( float xShear, float yShear );
	void		shearXZ( float xShear, float zShear );
	void		shearYZ( float yShear, float zShear );
	DzMatrix3&	operator*=( const DzMatrix3 &m );
	DzMatrix3&	operator*=( float c );
	DzMatrix3&	operator+=( const DzMatrix3 &m );
	DzMatrix3&	operator-=( const DzMatrix3 &m );
	operator	float*() { return *m_mtx; }
	float*		operator[]( int i ) { return m_mtx[i]; }

	// internal use only
	void		setFlags( int flags ) { m_flags = flags; }

	//
	// ACCESSORS
	//

	void			value( DzMat3 &m ) const;
	const DzMat3&	value() const { return m_mtx; }
	DzVec3			row( int i ) const { return DzVec3( m_mtx[i] ); }
	const float*	rowPointer( int i ) const { return m_mtx[i]; }
	float			det3() const;
	float			trace() const;
	DzMatrix3		inverse() const;
	bool			orthogonal() const;
	DzVec3			multVec( const DzVec3 &src ) const;
	void			multPnt( DzPnt3 &src ) const;
	DzMatrix3		operator*( const DzMatrix3 &m ) const;
	DzVec3			operator*( const DzVec3 &vec ) const;
	DzMatrix3		operator*( float c ) const;
	DzMatrix3		operator+( const DzMatrix3 &m ) const;
	DzMatrix3		operator-( const DzMatrix3 &m ) const;
	operator		const float*() const { return *m_mtx; }
	int				getFlags() const { return m_flags; }
	bool			isIdentity() const;
	DzMatrix4		matrix4() const;
	const float*	operator[]( int i ) const { return m_mtx[i]; }

	//
	// STATIC
	//

	static DzMatrix3 identity() { return DzMatrix3( true ); }
	static DzMatrix3 xRotation( float radians );
	static DzMatrix3 yRotation( float radians );
	static DzMatrix3 zRotation( float radians );
	static DzMatrix3 scaling( float scale );
	static DzMatrix3 scaling( const DzVec3 &scale );
	static DzMatrix3 scaling( float scale, const DzVec3 &direction );
	static DzMatrix3 translation( const DzVec3 &trans );
	static DzMatrix3 xyShear( float xShear, float yShear );
	static DzMatrix3 xzShear( float xShear, float zShear );
	static DzMatrix3 yzShear( float yShear, float zShear );

private:

	DzMat3	m_mtx;
	int		m_flags;
};

Q_DECLARE_METATYPE( DzMatrix3 );

/**
	*= operator for multiplying the point through the matrix.
**/
Q_DECL_EXPORT void operator*=( DzPnt3 &pnt, const DzMatrix3 &mat );

#endif // DAZ_MATRIX3_H
