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
	Defines the DzDockArea class.
**/

#ifndef DAZ_DOCK_AREA_H
#define DAZ_DOCK_AREA_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzDockWindow;
class DzDockAreaColumn;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzDockArea : public QWidget {
	Q_OBJECT
	friend class DzDockWindow;
	friend class DzDockAreaColumn;
public:
	//
	// CREATORS
	//

	DzDockArea( QWidget *parent, DzLocation location, const QString &name = QString::null );
	virtual ~DzDockArea();

	virtual QSize		sizeHint() const;
	virtual QSize		minimumSizeHint() const;
	virtual QSizePolicy sizePolicy() const;

	//
	// ACCESSORS
	//

	DzLocation			location() const;
	void				getDockPreview( DzDockWindow *window, const QPoint &globalPos, QPoint &p1, QPoint &p2 ) const;
	void				normalize();

public slots:

	int					getNumColumns() const;
	DzDockAreaColumn*	getColumn( int which ) const;

protected:
	virtual void	resizeEvent( QResizeEvent *e );

	void	dockWindow( DzDockWindow *window, bool newColumn );
	void	dockWindow( DzDockWindow *window, int columnNum );
	void	dockWindow( DzDockWindow *window, const QPoint &globalPos );
	void	removeWindow( DzDockWindow *window );
	void	moveDockWindow( DzDockWindow *window, const QPoint &globalPos );

private:
	void				doLayout();
	DzDockAreaColumn*	getNewColumn();
	QSize				calcSizeHint() const;

	struct	Data;
	Data	*m_data;
};


class DZ_EXPORT DzDockAreaColumn : public QWidget {
	Q_OBJECT
	friend class DzDockWindow;
public:

	DzDockAreaColumn( DzDockArea *parent, DzLocation location );
	~DzDockAreaColumn();

	//
	// MANIPULATORS
	//

	void	addWindow( DzDockWindow	*window, int offset = -1 );
	bool	removeWindow( DzDockWindow *window );
	void	updateMinDepth();
	bool	event( QEvent *e );
	void	normalize();

public slots:

	void	setPreferredDepth( int depth );
	void	minimize();
	void	restore();
	void	toggleMinimized();
	void	updateWindowsDividerStates();

public:
	//
	// ACCESSORS
	//

	virtual QSize		sizeHint() const;
	virtual QSize		minimumSizeHint() const;
	virtual QSizePolicy sizePolicy() const;

	DzLocation			location() const;
	void				getDockPreview( int offset, QPoint &p1, QPoint &p2 ) const;

public slots:

	int				getNumWindows() const;
	DzDockWindow*	getWindow( int which ) const;
	bool			isMinimized() const;
	int				depth() const;
	int				getPreferredDepth() const;
	int				minimumDepth() const;

protected:

	virtual void	showEvent( QShowEvent *e );

private slots:

	void	adjustHandle( int distance );
	void	windowLengthUpdate();
	void	windowMinimized( DzDockWindow *window );
	void	windowRestored( DzDockWindow *window );
	void	needLayout();
	void	tabOrientationChanged();

private:

	void	updateStretch();
	void	updateWindowPointers();
	int		getInsertIndex( int offset ) const;

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_DOCK_AREA_H

