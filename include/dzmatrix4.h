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
	Defines the DzMatrix4 class.
**/

#ifndef DAZ_MATRIX4_H
#define DAZ_MATRIX4_H

/*****************************
	Include files
*****************************/

#include "dzvec3.h"

/*****************************
	Type definitions
*****************************/

typedef float DzMat4[4][4];

/*****************************
	Forward declarations
*****************************/

class DzQuat;
class DzInFile;
class DzOutFile;
class DzMatrix3;

/*****************************
	Class definitions
*****************************/

class Q_DECL_EXPORT DzMatrix4 {
public:
	//
	// CREATORS
	//

	DzMatrix4( bool makeIdentity = false );
	DzMatrix4( const DzMatrix4 &m );
	DzMatrix4( const DzMat4 &m );
	DzMatrix4( const float vals[16] );
	DzMatrix4( const DzQuat &rot );
	DzMatrix4( const DzVec3 &xAxis, const DzVec3 &yAxis, const DzVec3 &zAxis );

	//
	// MANIPULATORS
	//

	DzMatrix4&	operator=( const DzMat4 &m );
	DzMatrix4&	operator=( const DzMatrix4 &m );
	void		makeIdentity();
	float*		operator[]( int i ) { return m_mtx[i]; }
	operator	float*() { return *m_mtx; }
	void		setValue( const float vals[16] );
	void		setRow( int i, const DzVec3 &vec ) {
					m_mtx[i][0] = vec.m_x;
					m_mtx[i][1] = vec.m_y;
					m_mtx[i][2] = vec.m_z; }
	void		setTrans( const DzVec3 &t );
	void		translate( const DzVec3 &t );
	void		preTranslate( const DzVec3 &t );
	void		rotateX( float radians );
	void		rotateY( float radians );
	void		rotateZ( float radians );
	void		rotate( const DzQuat &rot );
	void		scale( float scale );
	void		scale( const DzVec3 &vec );
	void		scale( float scale, const DzVec3 &direction );
	void		preScale( float scale );
	void		preScale( const DzVec3 &vec );
	void		preScale( float scale, const DzVec3 &direction );
	void		shearXY( float xShear, float yShear );
	void		shearXZ( float xShear, float zShear );
	void		shearYZ( float yShear, float zShear );
	void		preShearXY( float xShear, float yShear );
	void		preShearXZ( float xShear, float zShear );
	void		preShearYZ( float yShear, float zShear );
	void		invert();
	operator	const float*() const { return *m_mtx; }
	DzMatrix4&	operator*=( const DzMatrix4 &m );
	DzMatrix4&	operator*=( float c );
	DzMatrix4&	operator+=( const DzMatrix4 &m );
	DzMatrix4&	operator-=( const DzMatrix4 &m );
	DzMatrix4	operator*( const DzMatrix4 &m2 ) const;
	DzMatrix4	operator*( float c ) const;
	DzMatrix4	operator+( const DzMatrix4 &m ) const;
	DzMatrix4	operator-( const DzMatrix4 &m ) const;
	float		trace() const;
	DzMatrix4	transpose() const;
	DzMatrix4	inverse() const;
	void		decompose( DzVec3 &pos, DzQuat &rot ) const;
	bool		orthogonal();
	DzVec3		multMatrixVec( const DzVec3 &src ) const;
	DzVec3		multVecMatrix( const DzVec3 &src ) const;
	void		multMatrixPnt( DzPnt3 &src ) const;
	void		multPntMatrix( DzPnt3 &src ) const;
	DzMatrix3	matrix3() const;

	//
	// ACCESSORS
	//

	void			value( DzMat4 &m ) const;
	const DzMat4&	value() const { return m_mtx; }
	void			value( float vals[16] ) const;
	DzVec3			row( int i ) const { return DzVec3( m_mtx[i] ); }
	float*			rowPointer( int i ) const { return (float*) &(m_mtx[i]); }
	const float*	operator[]( int i ) const { return m_mtx[i]; }
	bool			isIdentity() const;

	//
	// STATIC
	//

	static DzMatrix4	identity() { return DzMatrix4( true ); }
	static DzMatrix4	xRotation( float radians );
	static DzMatrix4	yRotation( float radians );
	static DzMatrix4	zRotation( float radians );
	static DzMatrix4	scaling( float scale );
	static DzMatrix4	scaling( const DzVec3 &scale );
	static DzMatrix4	scaling( float scale, const DzVec3 &direction );
	static DzMatrix4	translation( const DzVec3 &trans );
	static DzMatrix4	xyShear( float xShear, float yShear );
	static DzMatrix4	xzShear( float xShear, float zShear );
	static DzMatrix4	yzShear( float yShear, float zShear );

private:
	DzMat4		m_mtx;

	DzMatrix4&	multRight( const DzMatrix4 &m );
	DzMatrix4&	multLeft( const DzMatrix4 &m );
	DzMatrix4	luDecompose( int *indx, int &d ) const;
	void		luBackSubstitute( const int *indx, float *b ) const;
};

Q_DECLARE_METATYPE( DzMatrix4 );

#endif // DAZ_MATRIX4_H
