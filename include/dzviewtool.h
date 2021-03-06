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
	Defines the DzViewTool class.
**/

#ifndef DAZ_VIEW_TOOL_H
#define DAZ_VIEW_TOOL_H

/*****************************
	Include files
*****************************/

#include "dzbase.h"
#include "dzviewportmgr.h"

/****************************
	Forward declarations
****************************/

class DzActionMenu;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzMouseModifier : public QObject {
	Q_OBJECT
public:
	enum ModifierType { ButtonModifier, WheelModifier };

	DzMouseModifier( const QString &label, ModifierType type, DzViewportMgr::ViewMouseModifier defaultMod );
	~DzMouseModifier();

	QString			getLabel() const;
	ModifierType	getType() const;

	DzViewportMgr::ViewMouseModifier	getModifierKey() const;

	void	setModifier( DzViewportMgr::ViewMouseModifier mod );

private:

	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzViewTool : public DzBase {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzViewTool( const QString &name );
	virtual ~DzViewTool();

	//
	// MANIPULATORS
	//

	virtual void	activate();
	virtual void	deactivate();
	virtual bool	mousePress( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier) { return false; }
	virtual bool	wheelEvent( Dz3DViewport *view, QWheelEvent *e, DzViewportMgr::ViewMouseModifier modifier) { return false; }
	virtual bool	mouseDoubleClick( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier ) { return false; }
	virtual void	mouseMove( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier ) { }
	virtual void	mouseRelease( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier ) { }
	virtual void	mouseOver( Dz3DViewport *view, QMouseEvent *e, DzViewportMgr::ViewMouseModifier modifier ) { }
	virtual void	mouseLeave( Dz3DViewport *view, QEvent *e ) { }
	virtual void	keyPress( Dz3DViewport *view, QKeyEvent *e ) { }
	virtual void	keyRelease( Dz3DViewport *view, QKeyEvent *e ) { }
	virtual bool	tabletEvent( Dz3DViewport *view, QTabletEvent *e ) { return false; }
	virtual void	contextMenu( Dz3DViewport *view, DzMenu *menu, const QPoint &pos ) { }
	virtual void	aimCamera( Dz3DViewport *view );
	virtual void	frameCamera( Dz3DViewport *view );

	//
	// ACCESSORS
	//

public slots:

	DzActionMenu*		getOptionsMenu() const;

public:

	virtual void		draw( const DzDrawStyle &style, Dz3DViewport *view ) const = 0;
	virtual QString		whatsThisText() const { return QString(); }
	virtual QWidget*	getPane( QWidget *parent ) const { return NULL; }
	virtual QWidget*	getPaneFooterGuide() const { return NULL; }
	virtual void		buildOptionsMenu( DzActionMenu *menu ) const { }
	virtual int			getOptionsMenuVersion() const { return 0; }
	virtual void		added( DzViewportMgr *mgr ) { }
	void				emitRebuildMenu();
	
	int					getNumMouseModifiers() const;
	DzMouseModifier*	getMouseModifier( int idx ) const;
	DzMouseModifier*	findMouseModifier( const QString &label ) const;
	bool				validateMouseBtnModifier( DzViewportMgr::ViewMouseModifier modifier );
	bool				validateMouseWheelModifier( DzViewportMgr::ViewMouseModifier modifier );

signals:

	void	drawnDataChanged();
	void	activated();
	void	deactivated();
	void	rebuildMenu();

protected:

	void	addMouseModifier( DzMouseModifier *mod );
	void	removeMouseModifier( DzMouseModifier *mod );

private:

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_VIEW_TOOL_H
