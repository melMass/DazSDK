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
	Defines the DzToolBar class.
**/

#ifndef DAZ_TOOL_BAR_H
#define DAZ_TOOL_BAR_H

/****************************
	Include files
****************************/

#include <QtGui/QToolBar>

#include "dzgeneraldefs.h"

/****************************
	Class definitions
****************************/

class QDomElement;
class QDomDocument;
class DzToolBar;

/****************************
	Forward declarations
****************************/

class DZ_EXPORT DzToolBarItem : public QObject {
	Q_OBJECT
	Q_ENUMS( Type )
	Q_PROPERTY( QString action READ getAction WRITE setAction )
	Q_PROPERTY( QString uiScript READ getUIScript WRITE setUIScript )
	Q_PROPERTY( int type READ typeAsInt )
	friend class DzToolBar;
public:
	enum	Type { Separator, Action, CustomAction, CustomWidget, ViewportLeftAlignSpacer, ViewportCenterAlignSpacer };

	DzToolBarItem( Type type );
	~DzToolBarItem();

	//
	// MANIPULATORS
	//

	void	setAction( const QString &action );
	void	setUIScript( const QString &uiScript );

	//
	// ACCESSORS
	//

	QString	getAction() const;
	QString	getUIScript() const;
	Type	type() const;
	int		typeAsInt() const { return (int) type(); } // for DAZ Script
	void	saveItem( QDomDocument &doc, QDomElement &parent ) const;

private:

	void		setToolBarAction( QAction *action );
	QAction*	getToolBarAction() const;
	void		setWidget( QWidget *wgt );
	QWidget*	getWidget() const;

	struct	Data;
	Data	*m_data;
};

typedef QListIterator<DzToolBarItem*> DzToolBarIterator;

class DZ_EXPORT DzToolBar : public QToolBar {
	Q_OBJECT
	Q_ENUMS( DockArea )
	friend class DzPaneMgr;
protected:
	DzToolBar( const QString &label );
public:
	enum DockArea { ToolBarTop, ToolBarBottom, ToolBarLeft, ToolBarRight, NoToolBarArea };

	virtual ~DzToolBar();

	//
	// REIMPLEMENTATIONS
	//
	virtual bool	event( QEvent *e );
	virtual void	customEvent( QEvent *e );

public slots:

	//
	// MANIPULATORS
	//

	virtual void	clear();

	void	insertItem( DzToolBarItem *item, int index = -1 );
	void	insertAction( const QString &action, int index = -1 );
	void	insertCustomAction( const QString &action, int index = -1 );
	void	insertSeparator( int index = -1 );
	void	insertCustomWidget( const QString &uiScript, int index = -1 );
	void	insertViewportCenterAlignSpacer( int index = -1 );
	void	insertViewportLeftAlignSpacer( int index = -1 );
	void	insertViewportAlignmentSpacer( Qt::Alignment alignment, int index = -1 );
	void	insertDomElem( QDomElement &elem, int index = -1 );
	void	removeItem( int index );
	void	removeItem( DzToolBarItem *item );
	void	load( QDomElement &elem );
	void	setClosed( bool onOff );
	void	dock( DzToolBar::DockArea area, const QString &beforeBar = QString::null );
	void	undock( QPoint &pos );
	DockArea	dockedArea();

	//
	// ACCESSORS
	//

	bool			hasItems() const;
	int				getNumItems() const;
	DzToolBarItem*	getItem( int which ) const;
	QObjectList		getItemList() const;
	void			saveToolBar( QDomDocument &doc, QDomElement &parent ) const;
	bool			isClosed() const;

public:

	DzToolBarIterator	itemListIterator() const;

signals:

	void	itemListChanged();

private slots:

	void	updateUILock();

private:

	void		buildBar();
	void		clearItems();
	void		markChanged();
	QAction*	addCustomWidget( DzToolBarItem *item, const QString &uiScript, QAction *before = NULL );

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzDockBar : public QToolBar {
	Q_OBJECT
	Q_ENUMS( DockArea )
	friend class DzPaneMgr;
public:
	enum DockArea { ToolBarTop, ToolBarBottom, ToolBarLeft, ToolBarRight, NoToolBarArea };

	DzDockBar( const QString &name );
	~DzDockBar();

	//
	// REIMPLEMENTATIONS
	//
	virtual bool	event( QEvent *e );

public slots:

	void		dock( DzDockBar::DockArea area, const QString &beforeBar = QString::null );
	void		undock( QPoint &pos );
	DockArea	dockedArea();
	void		setClosed( bool onOff );
	bool		isClosed() const;

private slots:

	void	updateUILock();

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_TOOL_BAR_H
