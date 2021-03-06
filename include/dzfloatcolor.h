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
	Defines the DzFloatColor class.
**/

#ifndef DAZ_GL_COLOR_H
#define DAZ_GL_COLOR_H

/*****************************
	Include files
*****************************/

#ifndef DSON_IMPORTER
#include <QtGui/QColor>
#endif

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzFloatColor {
public:
	//
	// CREATORS
	//

	DzFloatColor();
	DzFloatColor( const float color[4] );
	DzFloatColor( float r, float g, float b, float a = 1.0f );
	DzFloatColor( int r, int g, int b, int a = 255 );
#ifndef DSON_IMPORTER
	DzFloatColor( const QColor &color );
	DzFloatColor( QRgb rgba );
#endif
	DzFloatColor( const DzFloatColor &color );

	//
	// MANIPULATORS
	//

	void		setValue( float r, float g, float b, float a = 1.0f );
#ifndef DSON_IMPORTER
	void		setValue( QRgb color ); // RGBA
#endif
	void		setRed( float val );
	void		setGreen( float val );
	void		setBlue( float val );
	void		setAlpha( float val );

	DzFloatColor&	operator=( const DzFloatColor &obj );
#ifndef DSON_IMPORTER
	DzFloatColor&	operator=( const QColor &col );
#endif
	DzFloatColor	operator+( float val ) const;
	DzFloatColor&	operator+=( float val );
	DzFloatColor	operator+( const DzFloatColor &obj ) const;
	DzFloatColor&	operator+=( const DzFloatColor &obj );
	DzFloatColor	operator-( float val ) const;
	DzFloatColor&	operator-=( float val );
	DzFloatColor	operator-( const DzFloatColor &obj ) const;
	DzFloatColor&	operator-=( const DzFloatColor &obj );
	DzFloatColor	operator*( float val ) const;
	DzFloatColor&	operator*=( float val );
	DzFloatColor	operator*( const DzFloatColor &obj ) const;
	DzFloatColor&	operator*=( const DzFloatColor &obj );
	float&			operator[]( int i );

	//
	// ACCESSORS
	//

	const float*	getValue() const;
	void			getValue( float &r, float &g, float &b, float &a ) const;
	void			getValue( float &r, float &g, float &b ) const;
	void			getValue( float rgba[4] ) const;
#ifndef DSON_IMPORTER
	QRgb			rgba() const;
#endif
	float			getGreyscale() const;

	float			red() const;
	float			green() const;
	float			blue() const;
	float			alpha() const;

	inline float	redF() const{ return red(); }
	inline float	greenF() const{ return green(); }
	inline float	blueF() const{ return blue(); }
	inline float	alphaF() const{ return alpha(); }

	bool			operator==( const DzFloatColor &c ) const;
	bool			operator!=( const DzFloatColor &c ) const;
	float			operator[]( int i ) const;

private:

	float	m_color[4];
};

#endif // DAZ_GL_COLOR_H
