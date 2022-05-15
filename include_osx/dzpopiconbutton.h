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
	Defines the DzPopIconButton class.
**/

#ifndef DAZ_POP_ICON_BUTTON_H
#define DAZ_POP_ICON_BUTTON_H

/*****************************
	Include files
*****************************/

#include <QtGui/QPushButton>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPopIconButton : public QPushButton {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzPopIconButton( QWidget *parent, const QString &name, bool isDragButton = false );
	virtual ~DzPopIconButton();

	//
	// MANIPULATORS
	//

	void	addMode( const QString &label, const QPixmap &icon );
	void	addMode( const QString &label, const QPixmap &defIcon, const QPixmap &disIcon,
				const QPixmap &hilIcon );
	void	setIcons( int mode, const QPixmap &icon );
	void	setIcons( int mode, const QPixmap &defIcon, const QPixmap &disIcon,
				const QPixmap &hilIcon );

	//
	// ACCESSORS
	//

	int	getNumModes() const;
	int	getActiveMode() const;

signals:

	void	dragged( const QPoint &pnt );

protected:
	//
	// MANIPULATORS
	//

	virtual void	enterEvent ( QEvent *e );
	virtual void	leaveEvent ( QEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseMoveEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	paintEvent( QPaintEvent *e );

private slots:

	void	setButton( QAction *which );
	void	timerDone();

private:

	void	doPopup();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_POP_ICON_BUTTON_H


