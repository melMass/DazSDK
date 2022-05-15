/**********************************************************************
	Copyright (C) 2002-2012 DAZ 3D, Inc. All Rights Reserved.

	This file is part of the DAZ|Studio SDK.

	This file may be used only in accordance with the DAZ|Studio SDK 
	license provided with the DAZ|Studio SDK.

	The contents of this file may not be disclosed to third parties, 
	copied or duplicated in any form, in whole or in part, without the 
	prior written permission of DAZ 3D, Inc, except as explicitly
	allowed in the DAZ|Studio SDK license.

	See http://www.daz3d.com to contact DAZ 3D, Inc or for more 
	information about the DAZ|Studio SDK.
**********************************************************************/
#ifndef DAZ_TEXT_STYLE_H
#define DAZ_TEXT_STYLE_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFont>
#include <QtGui/QColor>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzTextStyle {
public:
	DzTextStyle();
	DzTextStyle( const QFont &font, const QColor &color );
	DzTextStyle( const DzTextStyle &style );
	~DzTextStyle();

	DzTextStyle&		operator=( const DzTextStyle &style );
	
	void	setFont( const QFont &font );
	void	setColor( const QColor &col );

	const QFont&	font() const;
	const QColor&	color() const;

	QFontMetrics	fontMetrics() const;

private:

	QFont	m_font;
	QColor	m_color;
};

Q_DECLARE_METATYPE( DzTextStyle );

#endif // DAZ_TEXT_STYLE_H