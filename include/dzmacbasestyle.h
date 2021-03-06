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

#ifndef DAZ_MAC_BASE_STYLE_H
#define DAZ_MAC_BASE_STYLE_H

/*****************************
	Include files
*****************************/

#include <QtGui/QMacStyle>

/*****************************
	Class definitions
*****************************/

class DzMacBaseStyle : public QMacStyle
{
	Q_OBJECT
public:
	DzMacBaseStyle();
	virtual ~DzMacBaseStyle();
	
	void	polish( QWidget *w );
	void	unpolish( QWidget *w );
	void	polish( QApplication *app );
	void	unpolish( QApplication *app );
	void	polish( QPalette &pal );
	void	drawPrimitive( PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
						const QWidget *w = 0 ) const;
	void	drawControl( ControlElement element, const QStyleOption *opt, QPainter *p,
						const QWidget *w = 0 ) const;
	QRect	subElementRect( SubElement r, const QStyleOption *opt, const QWidget *widget = 0 ) const;
	void	drawComplexControl( ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
							const QWidget *w = 0 ) const;
	SubControl	hitTestComplexControl( ComplexControl cc, const QStyleOptionComplex *opt,
									 const QPoint &pt, const QWidget *w = 0 ) const;
	QRect	subControlRect( ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
							const QWidget *w = 0 ) const;
	QSize	sizeFromContents( ContentsType ct, const QStyleOption *opt,
							const QSize &contentsSize, const QWidget *w = 0 ) const;
	int		pixelMetric( PixelMetric pm, const QStyleOption *opt = 0, const QWidget *widget = 0 ) const;
	QPalette	standardPalette() const;
	int		styleHint( StyleHint sh, const QStyleOption *opt = 0, const QWidget *w = 0,
					QStyleHintReturn *shret = 0 ) const;
	QPixmap	standardPixmap( StandardPixmap sp, const QStyleOption *opt,
							const QWidget *widget = 0 ) const;
	QPixmap	generatedIconPixmap( QIcon::Mode iconMode, const QPixmap &pixmap,
								const QStyleOption *opt ) const;
	void	drawItemText( QPainter *p, const QRect &r, int flags, const QPalette &pal,
						bool enabled, const QString &text, QPalette::ColorRole textRole  = QPalette::NoRole ) const;

protected slots:
	QIcon	standardIconImplementation( StandardPixmap standardIcon, const QStyleOption *opt = 0,
										 const QWidget *widget = 0 ) const;
	int		layoutSpacingImplementation( QSizePolicy::ControlType control1,
									QSizePolicy::ControlType control2, 
									Qt::Orientation orientation,
									const QStyleOption *option = 0, 
									const QWidget *widget = 0 ) const;
};

#endif // DAZ_MAC_BASE_STYLE_H
