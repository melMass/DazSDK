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
	Defines the DzActionMenu class.
**/

#ifndef DAZ_ACTION_MENU_H
#define DAZ_ACTION_MENU_H

/****************************
	Include files
****************************/

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzActionMgr;
class QDomDocument;
class QDomElement;
class QMenu;
class QPoint;

/****************************
	Class definitions
****************************/

class DzActionMenu;

class DZ_EXPORT DzActionMenuItem : public QObject {
	Q_OBJECT
	Q_ENUMS( Type );
	Q_PROPERTY( QString action READ getAction WRITE setAction )
	Q_PROPERTY( QString subMenuLabel READ getSubMenuLabel WRITE setSubMenuLabel )
	Q_PROPERTY( int type READ typeAsInt )
	friend class DzActionMenu;
public:
	enum	Type { Separator, Action, CustomAction, SubMenu };

	DzActionMenuItem( Type type );
	DzActionMenuItem( const DzActionMenuItem &item );
	~DzActionMenuItem();

	void	saveItem( QDomDocument &doc, QDomElement &parent ) const;

	void	setAction( const QString &action );
	void	setSubMenuLabel( const QString &text );

	QString	getAction() const;
	QString	getSubMenuLabel() const;
	Type	type() const;
	int		typeAsInt() const { return (int) type(); } // for DAZ Script

public slots:

	void			setSubMenu( DzActionMenu *menu );
	DzActionMenu	*getSubMenu() const;

private:

	struct	Data; 
	Data	*m_data;

	void	addToMenu( DzActionMgr *mgr, QMenu *menu ) const;
	void	addToMenu( DzActionMgr *mgr ) const;
};

typedef QListIterator<DzActionMenuItem*> DzActionMenuIterator;

class DZ_EXPORT DzActionMenu : public QObject {
	Q_OBJECT
	Q_ENUMS( MenuType );
	Q_PROPERTY( int menuType READ menuTypeAsInt )
	friend class DzActionMgr;
	friend class DzActionMenuItem;
public:
	enum MenuType { CustomMenu = 0, PaneMenu, ViewToolMenu, SaveAsMenu };

	DzActionMenu();
	DzActionMenu( MenuType type );
	DzActionMenu( const DzActionMenu &menu );
	virtual ~DzActionMenu();

	// from QObject
	virtual	bool	event( QEvent *e );

	DzActionMenuIterator	itemListIterator() const;

	void		insertDomElem( QDomElement &elem, int at = -1 );
	void		saveMenu( QDomDocument &doc, QDomElement &parent ) const;

	MenuType	menuType() const;
	int			menuTypeAsInt() const { return (int) menuType(); } // for DAZ Script

public slots:

	void			clear();
	void			insertItem( DzActionMenuItem *item, int at = -1 );
	void			removeItem( DzActionMenuItem *item );
	void			insertAction( const QString &action, int at = -1 );
	void			insertCustomAction( const QString &action, int at = -1 );
	void			insertMenu( const QString &text, DzActionMenu *menu, int at = -1 );
	void			insertSeparator( int where = -1 );
	DzActionMenu*	getSubMenu( const QString &name );
	void			simplifySeparators();

	bool				hasItems() const;
	int					getNumItems() const;
	DzActionMenuItem*	getItem( int which ) const;
	QObjectList			getItemList() const;
	DzActionMenu*		findSubMenu( const QString &name ) const;
	void				exec() const;
	void				exec( const QPoint &pos ) const;
	QMenu*				getMenu() const;

signals:

	void	itemListChanged();

protected:

	virtual void	buildMenu( QMenu *menu );

private slots:

	void	checkForUpdates();
	void	removeCustomAction( const QString &name );

private:

	DzActionMenu( DzActionMgr *mgr );

	void	init();
	void	buildMenu();
	void	markChanged();
	void	buildPaneMenu( DzActionMgr *mgr );
	void	buildViewToolMenu( DzActionMgr *mgr );
	void	buildSaveAsMenu( DzActionMgr *mgr );
	void	insertItemInternal( DzActionMenuItem *item, int at = -1 );
	void	removeItemInternal( DzActionMenuItem *item );
	void	insertActionInternal( const QString &action, int at = -1 );
	void	insertCustomActionInternal( const QString &action, int at = -1 );
	void	insertMenuInternal( const QString &text, DzActionMenu *menu, int at = -1 );
	void	insertSeparatorInternal( int at = -1 );
	void	insertDomElemInternal( QDomElement &elem, int at = -1 );

	struct	Data; 
	Data	*m_data;
};

#endif // DAZ_ACTION_MENU_H