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
	Defines the DzButtonBar class.
**/

#ifndef DAZ_BUTTON_BAR_H
#define DAZ_BUTTON_BAR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QAbstractButton>

#include "dzgeneraldefs.h"

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzButtonBar : public QWidget {
	Q_OBJECT
public:

	enum SeparatorType { Vertical, SlantRight, SlantLeft };

	DzButtonBar( QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzButtonBar();

	void			addWidget( QWidget *widget, int id = -1 );
	void			addSeparator( SeparatorType sep = Vertical, int id = -1 );

	void			hideItem( int id );
	void			showItem( int id );

	virtual bool	event( QEvent *e );

protected:

	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	virtual void	paintEvent( QPaintEvent *e );
	virtual void	resizeEvent( QResizeEvent *e );
	virtual void	styleChange( QStyle &old );

private:

	void			updateMinSize();
	void			updateLayout();
	void			doLayout();
	void			createMask();
	void			activateButton( const QPoint &pos );
	void			activateButton( int which, const QPoint &pos );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzBarButton : public QAbstractButton {
	Q_OBJECT
public:

	DzBarButton( QWidget *parent = 0, const QString &name = QString::null );
	DzBarButton( const QPixmap &icon, QWidget *parent = 0, const QString &name = QString::null );
	DzBarButton( const QIcon &icon, QWidget *parent = 0, const QString &name = QString::null );
	virtual ~DzBarButton();

	virtual void	setIcon( const QPixmap &pix );
	virtual void	setIcon( const QIcon &icon );

protected:

	virtual void	paintEvent( QPaintEvent *e );
	virtual void	styleChange( QStyle &old );

private:

	void			updateMinSize();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_BUTTON_BAR_H
