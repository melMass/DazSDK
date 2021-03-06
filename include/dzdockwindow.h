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
	Defines the DzDockWindow class.
**/

#ifndef DAZ_DOCK_WINDOW_H
#define DAZ_DOCK_WINDOW_H

/*****************************
	Include files
*****************************/

#include <QtGui/QFrame>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzDockArea;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDockWindow : public QFrame {
	Q_OBJECT
	friend class DzDockAreaColumn;
public:
	//
	// CREATORS
	//

	DzDockWindow( QWidget *parent, const QString &name = QString::null );
	virtual ~DzDockWindow();

	//
	// MANIPULATORS
	//

	void		setWidget( QWidget *widget );

	bool		event( QEvent *e );

public slots:

	void			setLength( int length );
	virtual void	dock();
	virtual void	dock( DzDockArea *area, bool newColumn = false );
	virtual void	dock( DzDockArea *area, int columnNum );
	virtual void	undock();
	void			toggleDock();
	virtual void	minimize();
	virtual void	restore();
	void			toggleMinimized();
	void			toggleStateForAH( DzLocation loc );
	void			setColumnNum( int columnNum );
	int				getColumnNum();
	void			setColumnDimension(int dimension);
	int				getColumnDimension();

public:
	//
	// ACCESSORS
	//

	QWidget*		getWidget() const;
	Qt::Orientation	orientation() const;
	void			hideTitleBar();

public slots:

	int			getLength() const;
	int			getMinimumLength() const;
	bool		isLengthFixed() const;
	bool		isMinimized() const;
	bool		isDocked() const;
	DzDockArea*	getArea() const;
	QSize		getLastSize() const;

signals:

	void	lengthChanged();
	void	minimized( DzDockWindow *window );
	void	restored( DzDockWindow *window );
	void	docked();
	void	undocked();
	void	unpinnedAboutToHide();

protected:

	void	setPrev( DzDockWindow *win );
	void	normalize();

	//
	// REIMPLEMENTATIONS
	//

	virtual void	styleChange( QStyle &oldStyle );
	virtual void	closeEvent( QCloseEvent *e );

private slots:

	void	startOutlineDraw( const QPoint &offset, const QPoint &mousePos );
	void	moveOutline( const QPoint &mousePos );
	void	moveWindow( const QPoint &mousePos );
	void	endOutlineDraw();
	void	adjustLength( int amount );

private:
	void	startDockingHighlight( QPoint const &p1, QPoint const &p2 );
	void	stopDockingHighlight();

	void		dock( DzDockArea *area, const QPoint &mousePos );
	void		undock( const QPoint &globalPos );
	DzDockArea*	areaAt( const QPoint &gp ) const;
	QSize		calcMinSize() const;
	void		setDividerWidgetType( DzLocation location );
	void		updateDividerState();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DOCK_WINDOW_H


