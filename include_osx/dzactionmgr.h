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
	Defines the DzActionMgr class.
**/

#ifndef DAZ_ACTION_MGR_H
#define DAZ_ACTION_MGR_H

/****************************
	Include files
****************************/

#include <QtGui/QMenuBar>

#include "dzactionmenu.h"
#include "dzviewportmgr.h"

/****************************
	Forward declarations
****************************/

class DzAction;
class DzMainWindow;
class DzPersistentMenu;
class DzToolBar;
class QDomDocument;
class QDomElement;
class QDomNode;
class QToolBar;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzActionMgr : public QMenuBar {
	Q_OBJECT
	friend class DzApp;
	friend class DzMainWindow;
	friend class DzPaneMgr;
	friend class DzAction;
	friend class DzActionInternalClassFactory;
private:
	//
	// CREATORS
	//

	DzActionMgr( DzMainWindow *mainWindow, QWidget *parent );
	~DzActionMgr();

	void			init();

public:

	void			buildDefaultInterface();
	bool			addActionToMenu( const QString &className, QMenu *menu ) const;
	bool			addActionToToolBar( const QString &className, QToolBar *toolbar ) const;
	bool			addCustomActionToMenu( const QString &name, QMenu *menu ) const;
	bool			addCustomActionToToolBar( const QString &name, QToolBar *toolbar ) const;
	void			setAccel( const QString &className, QKeySequence key );
	void			unsetAccel( QKeySequence key );
	QString			addCustomAction( const QString &text, const QString &desc, const QString &script,
						bool isFile, QKeySequence shortcut, const QString &iconFile = QString::null );
	void			setCustomActionAccel( int which, QKeySequence shortcut );
	QKeySequence	getCustomActionAccel( int which ) const;
	void			getCustomActionScript( int which, QString &script, bool &isFile ) const;
	DzAction*		getCustomAction( int which );

public slots:

	void			setAccel( const QString &className, const QString &key );
	void			unsetAccel( const QString &key );
	QString			addCustomAction( const QString &text, const QString &desc, const QString &script,
						bool isFile = true, const QString &shortcut = QString::null,
						const QString &iconFile = QString::null );
	void			setCustomActionText( int which, const QString &text );
	void			setCustomActionDesc( int which, const QString &desc );
	void			setCustomActionScript( int which, const QString &script, bool isFile = true );
	void			setCustomActionAccel( int which, const QString &shortcut );
	void			setCustomActionIcon( int which, const QString &iconFile );
	void			setCustomActionShowTextWithIcon( int which, bool onOff );
	void			removeCustomAction( int which );
	void			removeAllCustomActions();
	int				getCustomAction( const QString &name );
	bool			loadInterfaceFile( const QString &filename );

	int				getNumActions() const;
	DzAction*		getAction( int which ) const;
	DzAction*		findAction( const QString &className ) const;
	int				getNumPersistentMenus() const;
	DzPersistentMenu*	getPersistentMenu( int which ) const;
	DzPersistentMenu*	findPersistentMenu( const QString &className ) const;
	int				getNumCustomActions() const;
	int				findCustomAction( const QString &name ) const;
	QString			getCustomActionName( int which ) const;
	QString			getCustomActionText( int which ) const;
	QString			getCustomActionDesc( int which ) const;
	QString			getCustomActionScript( int which ) const;
	QString			getCustomActionFile( int which ) const;
	QString			getCustomActionShortcut( int which ) const;
	QString			getCustomActionIcon( int which ) const;
	bool			saveInterfaceFiles() const;
	bool			saveMenusFile( const QString &filename ) const;
	bool			saveToolBarsFile( const QString &filename ) const;
	bool			saveActionsFile( const QString &filename ) const;
	bool			saveCustomActionsFile( const QString &filename ) const;
	DzActionMenu*	getMenu() const;
	void			setActiveMenu( DzActionMenu *menu );
	DzActionMenu*	getActiveMenu();
	void			clearActiveMenu();

signals:

	void			customActionListChanged();
	void			customActionAdded( const QString &name );
	void			customActionRemoved( const QString &name );

protected:

	virtual void	styleChange( QStyle &oldStyle );

private:

	void	saveActions( QDomDocument &doc, QDomElement &root ) const;
	void	saveCurrentActions( QDomDocument &doc, QDomElement &root ) const;
	void	saveCustomActions( QDomDocument &doc, QDomElement &root ) const;
	void	saveMainMenu( QDomDocument &doc, QDomElement &root ) const;
	void	saveToolBars( QDomDocument &doc, QDomElement &root ) const;
	void	savePaneMenus( QDomDocument &doc, QDomElement &root ) const;
	void	savePersistentMenus(QDomDocument &doc, QDomElement &root) const;
	void	saveViewToolMenus( QDomDocument &doc, QDomElement &root ) const;
	void	saveViewAccelerators( QDomDocument &doc, QDomElement &root ) const;
	void	saveViewAccelerator( QDomDocument &doc, QDomElement &viewAccelerators, DzViewportMgr *viewMgr,
				QString const elementName, DzViewportMgr::ViewOperation operation ) const;
	void	saveViewToolAccelerators( QDomDocument &doc, QDomElement &root ) const;
	void	saveViewToolAccelerators( DzViewTool *tool, QDomDocument &doc, QDomElement &viewToolAccelerators, DzViewportMgr *viewMgr ) const;
	
	static void		addClass( DzClassFactory *type );
	void			addPaneMenu( DzActionMenu *menu, const QString &paneClassName );
	void			addDefaultActions( const QStringList &actions );
	DzActionMenu*	getSubMenu( const QString &path );
	QString			getUniqueName();
	void			buildMainMenu( QDomElement root );
	void			resetViewTabsMenuType( QDomElement mainMenuNode );
	void			resetToolsMenuType( QDomElement mainMenuNode );
	void			resetSaveAsMenuType( QDomElement mainMenuNode );
	void			buildMenu( DzActionMenu *menu, QDomNode node );
	void			buildToolBars( QDomNode node );
	void			buildPaneMenus( QDomNode node );
	void			buildPersisentMenus( QDomNode node );
	void			buildToolMenus( QDomNode node );
	QStringList		buildActionList( QDomNode node );
	QStringList		buildCurrentActionList( QDomNode node );
	void			loadViewAccelerators( QDomNode node );
	void			loadViewToolAccelerators( QDomNode node);
	QString			readAction( QDomElement &elem );
	void			buildCustomActionList( QDomNode node );
	void			readCustomAction( QDomElement &elem );
	QString			getMenusPath() const;
	void			setActionShortcut( DzAction *action, QKeySequence shortcut, bool cancelIfConflicting );
	void			insertIconedActionIntoToolBar( const QString &action, DzToolBar *toolBar );
	void			addDefaultAccelsForMenu( DzActionMenu *menu );
	void			addDefaultAccelsForToolbar( DzToolBar *bar );

	struct	Data; 
	Data	*m_data;
};

class DZ_EXPORT DzPersistentMenu : public QObject {
	Q_OBJECT
public:
	DzPersistentMenu( const QString &name );
	virtual ~DzPersistentMenu();

	DzActionMenu*	getPersistentMenu() const;
	virtual void	buildPersistentMenu( DzActionMenu *menu ) const = 0;
	virtual int		getPersistentMenuVersion() const = 0;

public slots:

	virtual void		setActiveWgt( QWidget *wgt );
	virtual void		clearActiveWgt();
	virtual QWidget*	getActiveWgt() const;

private:
	struct	Data; 
	Data	*m_data;
};

struct DzPersistentActionMenuData;
class DzPersistentActionMenu : public DzActionMenu {
	Q_OBJECT
public:
	DzPersistentActionMenu( DzPersistentMenu *menu );
	virtual ~DzPersistentActionMenu();

public slots:
	DzPersistentMenu*	getPersistentMenu() const;

private:
	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_ACTION_MGR_H
