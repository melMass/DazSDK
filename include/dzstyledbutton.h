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
	Defines the DzStyledButton class.
**/

#ifndef DAZ_STYLED_BUTTON_H
#define DAZ_STYLED_BUTTON_H

/*****************************
	Include files
*****************************/

#include <QtGui/QPushButton>

#include "dzstyle.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzStyledButton : public QPushButton {
	Q_OBJECT
public:

	enum ButtonStyle { BCommand, BTool, BDefault, BBasic, BNoFrame, BCustom };

	//
	// CREATORS
	//

	DzStyledButton( QWidget *parent = NULL );
	DzStyledButton( const QString &text, QWidget *parent = NULL );
	virtual ~DzStyledButton();

	//
	// MANIPULATORS
	//

	virtual void	setButtonStyle( ButtonStyle style );
	virtual void	setButtonTextFormat( int align );

	void	setCustomPrimitive(QStyle::PrimitiveElement prim);
	void	setCustomDownArrowPrimitive(QStyle::PrimitiveElement prim);
	void	setCustomTextStyle(DzStyle::TextStyle textStyle);
	void	setElideMode(Qt::TextElideMode mode);
	void	setDisplayDownArrow(bool displayArrow);
	void	setIconMetric(QStyle::PixelMetric metric);
	void	setDownArrowMetric(QStyle::PixelMetric metric);
	
	//
	// ACCESSORS
	//

	ButtonStyle					getButtonStyle() const;
	int							getButtonTextFormat() const;
	QStyle::PrimitiveElement	getPrimitive() const;
	DzStyle::TextStyle			getTextStyle() const;
	Qt::TextElideMode			getElideMode() const;
	bool						getDisplayDownArrow() const;
	QStyle::PixelMetric			getIconMetric() const;
	QStyle::PixelMetric			getDownArrowMetric() const;

protected:
	virtual void	drawButton( QPainter *p );
	virtual void	drawButtonLabel( QPainter *p );
	virtual void	setButtonStateFlags(QStyle::State &flags);
	virtual void	setButtonLabelStateFlags(QStyle::State &flags);
	virtual void	paintEvent( QPaintEvent *evt );
	virtual QSize	sizeHint() const;
	virtual QSize	minimumSizeHint() const;

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_STYLED_BUTTON_H


