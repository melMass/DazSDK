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
	Defines the DzPaneGroup class.
**/

#ifndef DAZ_PANE_GROUP_H
#define DAZ_PANE_GROUP_H

/*****************************
	Include files
*****************************/

#include "dzdockwindow.h"

/****************************
	Forward declarations
****************************/

class QTimer;

class DzPane;
class DzPaneMgr;
class DzAutoHideTabBar;
class DzAutoHideTab;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPaneGroup : public DzDockWindow {
	Q_OBJECT
public:
	//
	// CREATORS
	//

	DzPaneGroup( QWidget *parent, DzPaneMgr *mgr, const QString &name = QString::null );
	virtual ~DzPaneGroup();

	virtual void	minimize();
	virtual void	restore();

	//
	// MANIPULATORS
	//

	int		insertPane( DzPane *pane, int index = -1 );
	void	removePane( DzPane *pane );
	void	removeAllPanes();
	void	setAutoBarIndex(uint index);
	uint	getAutoBarIndex();

public slots:

	void	showPane( DzPane *pane );
	void	hidePane( DzPane *pane );
	void	hideAllPanes();
	void	setAutoHide( bool onOff );
	void	hideTabBar( bool hide );
	bool	tabBarHidden();
	void	setPaneEnabled( DzPane *pane, bool enabled );

	// TODO: SDK - review functions for exclusion from SDK
	void	dockAndDoAutoHide( DzLocation loc );
	void	ahShowPane( DzPane *pane, QPoint pos, DzLocation loc );
	void	ahHidePane();
	void	addAHTab( DzAutoHideTab *argtab );
	void	removeAHTab( DzAutoHideTab *argtab );

	//
	// ACCESSORS
	//

	int		getNumPanes() const;
	DzPane*	getPane( int i ) const;
	int		getNumShownPanes() const;
	DzPane*	getCurrentPane() const;
	QPoint	getDragOffset();
	bool	isAutoHideOn() const;

	// TODO: SDK - review functions for exclusion from SDK
	DzAutoHideTabBar*	getAHBar() const;
	bool				ahHasFocus() const;
	QTimer*				getTimer() const;
	bool				anyoneHasFocus() const;
	void				updateTabPosition();

private slots:
	void	undockTabPosition();
	void	dockTabPosition();

signals:
	void	emptyGroup();

protected:
	/////////////////////////
	// from QWidget

	virtual void	dragEnterEvent( QDragEnterEvent *event );
	virtual void	dropEvent( QDropEvent *event );
	virtual void	closeEvent( QCloseEvent *e );

	//Reimplemented to perform autohiding
	virtual void	enterEvent( QEvent *e );
	virtual void	leaveEvent( QEvent *e );
	virtual void	mousePressEvent( QMouseEvent *e );
	virtual void	mouseReleaseEvent( QMouseEvent *e );
	
	void setTabPostion( DzLocation loc );
	
private:
	//
	// DATA MEMBERS
	//
	struct	Data;
	Data	*m_data;
};

class DZ_EXPORT DzPaneGroupDlg : public QFrame {
	Q_OBJECT
public:
	DzPaneGroupDlg( const DzPaneGroup *group, QWidget *parent = NULL );
	DzPaneGroupDlg( DzPane *pane, QWidget *parent = NULL );
	virtual ~DzPaneGroupDlg();

public slots:
	DzPaneGroup*	getPaneGroup() const;

protected:
	virtual void	closeEvent( QCloseEvent *eve );

private:
	void	init();

	struct	Data;
	Data	*m_data;
};
	
#endif // DAZ_PANE_GROUP_H
