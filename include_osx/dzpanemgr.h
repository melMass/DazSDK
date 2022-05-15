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
	Defines the DzPaneMgr class.
**/

#ifndef DAZ_PANE_MGR_H
#define DAZ_PANE_MGR_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzerrorcodes.h"

/****************************
	Forward declarations
****************************/

class DzActivityBar;
class DzActivityLayout;
class DzClassFactory;
class DzDockBar;
class DzDockedGroupList;
class DzMainWindow;
class DzPane;
class DzPaneGroup;
class DzPaneGroupDlg;
class DzToolBar;
class QDomElement;

/****************************
	Type definitions
****************************/

typedef QListIterator<DzPane*>		DzPaneListIterator;
typedef QListIterator<DzPaneGroup*>	DzPaneGroupListIterator;
typedef QListIterator<DzToolBar*>	DzToolBarListIterator;
typedef QListIterator<DzDockBar*>	DzDockBarListIterator;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPaneMgr : public QWidget {
	Q_OBJECT
	Q_ENUMS( DockSide );
	friend class DzApp;
	friend class DzMainWindow;
	friend class DzPaneInternalClassFactory;
	friend class DzPaneGroupTabBarWgt;
private:

	//
	// CREATORS
	//

	DzPaneMgr( DzMainWindow *mainWindow, QWidget *parent );
	~DzPaneMgr();

public:

	enum DockSide {	NO_DOCKING, DOCK_LEFT, DOCK_TOP, DOCK_RIGHT, DOCK_BOTTOM };

	//
	// MANIPULATORS
	//

	DzError			startup();

	void			hideAllPaneGroups();
	void			refreshAll();

	virtual bool	event( QEvent *e );

public slots:

	DzError		setSessionLayout( const QString &filename );

	DzError		saveLayout( const QString &filename, const QString &description = QString::null );
	DzError		restoreLayout( const QString &filename );
	DzError		restoreLayout( const QString &filename, bool executeScript );

	DzError		showPane( const QString &className );
	DzError		showPane( DzPane *pane );

	void		showAllPanes();
	DzError		hidePane( const QString &className );
	DzError		hidePane( DzPane *pane );
	void		hideAllPanes();
	DzError		togglePane( const QString &className );
	DzError		togglePane( DzPane *pane );
	DzError		togglePane( int index );
	DzError		tearOffPane( const QString &className, int x = 0, int y = 0 );
	DzError		tearOffPane( DzPane *pane, int x = 0, int y = 0 );
	DzError		tearOffPane( int index, int x = 0, int y = 0 );
	DzError		showPaneGroup( int which );
	DzError		showPaneGroup( DzPaneGroup *group );
	DzError		hidePaneGroup( int which );
	DzError		hidePaneGroup( DzPaneGroup *group );
	void		clearAllGroups();
	DzError		movePaneGroup( DzPaneGroup *group, DockSide dock = NO_DOCKING );
	DzError		movePaneGroup( DzPaneGroup *group, DockSide dock, int index, bool newLine = false );

	DzToolBar*	createToolBar( const QString &name );
	void		removeToolBar( const QString &name );
	void		removeAllToolBars();
	void		hideAllToolBars();
	
	DzActivityLayout*	createActivityLayout( const QString &name, const QString &description );

	void	addActivityLayout( DzActivityLayout *layout );
	bool	removeActivityLayout( const QString &name );
	bool	removeActivityLayout( int which );
	void	removeAllActivityLayouts();
	void	setActiveActivityLayout( int which );
	void	setActiveActivityLayout( DzActivityLayout *which );

	void	enableActivityBar( bool onOff );
	void	setActivityBarImage( const QString &img );
	void	loadNextActivityBarImage();

	DzError	setPaneEnabled( const QString &className, bool enabled );
	DzError	setPaneEnabled( DzPane *pane, bool enabled );

public:

	//
	// ACCESSORS
	//

	DzPaneListIterator		paneListIterator() const;
	DzPaneGroupListIterator	paneGroupListIterator() const;
	DzToolBarListIterator	toolBarListIterator() const;
	DzDockBarListIterator	dockBarListIterator() const;
	DzActivityBar*			getActivityBar() const;

public slots:

	QString			getSessionLayout() const;

	QStringList		getDefaultLayoutNames() const;
	QString			getDefaultLayout() const;
	QString			getSimpleLayout() const;
	QString			getBasicLayout() const;
	QString			getStandardLayout() const;
	QString			getAdvancedLayout() const;

	int				getNumPanes() const;
	QObjectList		getPaneList() const;
	QObjectList		getPaneGroupList() const;
	DzPane*			findPane( const QString &className ) const;
	int				getNumPaneGroups() const;
	DzPaneGroup*	getPaneGroup( int which ) const;

	bool			isUnpinnedMenu( DzPane *pane ) const;

	int				getNumToolBars() const;
	DzToolBar*		getToolBar( int i ) const;
	DzToolBar*		findToolBar( const QString &name ) const;
	
	int				getNumDockBars() const;
	DzDockBar*		getDockBar( int i ) const;
	DzDockBar*		findDockBar( const QString &className ) const;
	DzDockBar*		findDockBarByName( const QString &name) const;

	int					getNumActivityLayouts() const;
	DzActivityLayout*	getActivityLayout( int which ) const;
	DzActivityLayout*	findActivityLayout( const QString &name ) const;
	DzActivityLayout*	getActiveActivityLayout() const;
	int					getActiveActivityLayoutIndex() const;

	bool			isActivityBarEnabled() const;
	QString			getActivityBarImage() const;
	QStringList		getActivityBarImageList() const;

	DzPaneGroup*	createEmptyPaneGroup() const;
	
	void				closeAllPaneGroupDlgs();
	DzPaneGroupDlg*		getPaneGroupDlg( int which ) const;
	int					getNumPaneGroupDlgs() const;
	void				addPaneGroupDlg( DzPaneGroupDlg *dlg );
	void				removePaneGroupDlg( DzPaneGroupDlg *dlg );
	void				removePaneGroup( DzPaneGroup *group );

	void	setShowLessonStrip( bool onOff );
	bool	getShowLessonStrip() const;
	bool	selectLesson( const QString &path );

	void	setOrientTabsAlongTop( bool onOff );
	bool	getOrientTabsAlongTop() const;
	
	void	setUseWorkflowAssistance( bool onOff );
	bool	getUseWorkflowAssistance();

signals:

	void	layoutListChanged();
	void	activeLayoutAboutToChange( int newLayoutIdx );
	void	activeLayoutChanged( int which );
	void	toolbarListChanged();
	void	activityBarEnabled( bool onOff );
	void	layoutRestored( const QString &filename );
	void	orientTabsAlongTopChanged( bool onOff );
	void	workflowAssistanceModeChanged();
	void	workflowAssistanceEnableStateChanged( bool onOff );

protected:

	virtual void	timerEvent( QTimerEvent *e );

	static void		addClass( DzClassFactory *type );

private slots:

	void	saveLayout();
	void	restoreLayout();
	void	executeLayoutScript( const QString &filename);
	void	removePane( QObject *pane );

private:

	void	restoreLayout( const QDomElement &root );
	void	restoreGroup( DzPaneGroup *grp, const QDomElement &root, DzDockedGroupList &dockedList );
	void	restoreToolBar( DzPaneGroup *grp, const QDomElement &root );
	void	addPane( DzPane *pane );
	bool	IsBryceClassFactoryNoSlave( DzClassFactory const *factory ) const;

	QObject*	getTabBarEventFilter() const;

	void	setupSimpleModes();
	void	enableWorkflowAssistance();
	void	disableWorkflowAssistance();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PANE_MGR_H
