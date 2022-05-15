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
	Defines the DzDividerBar class.
**/

#ifndef DAZ_DIVIDER_BAR_H
#define DAZ_DIVIDER_BAR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDividerBar : public QWidget {
	Q_OBJECT
	Q_ENUMS(BarStyle)
public:

	enum BarStyle { BSFull, BSSemi, BSThin };
	enum WidgetType { WTLeftOrTop, WTRightOrBottom, WTBoth, WTNone };

	DzDividerBar( QWidget *parent, Qt::Orientation o, const QString &name = QString::null, BarStyle barStyle = BSFull );
	virtual ~DzDividerBar();

	void	setToggledState( bool onOff );
	void	setSiblingState( WidgetType siblings );
	void	setToggleDirection( WidgetType toggleDir );
	void	setOrientation( Qt::Orientation o );
	void	setMoveDisabled( bool onOff = true);
	void	setBarStyle( BarStyle style );
	void	setToggleEnabled( bool onOff );
	
	Qt::Orientation	getOrientation() const;
	bool			toggleEnabled() const;
	bool			getToggledState() const;
	WidgetType		getSiblingState() const;
	WidgetType		getToggleDirection() const;
	BarStyle		getBarStyle() const;
	bool			getMoveDisabled() const;

signals:

	void	moved( int distance );
	void	toggleBarActivated();
	void	toggleBarRightClicked();

protected:

	//
	// REIMPLEMENTATIONS
	//

	virtual void	styleChange( QStyle &oldStyle );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	enterEvent( QEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	paintEvent( QPaintEvent *e );

private:
	void	updateToStyle();
	void	startOutlineDraw();
	void	endOutlineDraw();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DIVIDER_BAR_H