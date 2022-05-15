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
	Defines the DzColorGradient class.
**/

#ifndef DAZ_COLOR_GRADIENT_H
#define DAZ_COLOR_GRADIENT_H

/*****************************
	Include files
*****************************/

#include <QtGui/QColor>

#include "dzbase.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzColorGradient : public DzBase {
	Q_OBJECT
	Q_ENUMS( ColorModel )
public:

	enum ColorModel { RGB, HSV };

	DzColorGradient( ColorModel model = RGB );
	virtual ~DzColorGradient();

public slots:

	int			getNumGradients() const;
	QColor		getGradientColor( int index ) const;
	double		getGradientValue( int index ) const;
	QColor		getColor( float value ) const;
	ColorModel	getColorModel() const;

	void		addGradientColor( QColor color, float value );
	void		setGradientColor( int index, QColor color );
	void		removeGradientColor( int index );
	void		clear();
	void		setColorModel( ColorModel model );

signals:

	void		gradientChanged();

protected:

	QColor		getRGBInterpolation( float value, QRgb color0, QRgb color1 ) const;
	QColor		getHSVInterpolation( float value, QRgb color0, QRgb color1 ) const;

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_COLOR_GRADIENT_H
