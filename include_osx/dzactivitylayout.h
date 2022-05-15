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
	Defines the DzActivityLayout class.
**/

#ifndef DAZ_ACTIVITY_LAYOUT_H
#define DAZ_ACTIVITY_LAYOUT_H

/****************************
	Include files
****************************/

//#include <QtCore/QObject>

#include "dzrefcounteditem.h"
#include "dztsharedpointer.h"

/****************************
	Forward declarations
****************************/

class DzActivityBar;
class DzDockedGroupList;
class DzMainWindow;
class DzPaneMgr;
class DzViewportMgr;
class QDomDocument;
class QDomElement;

/****************************
	Class definitions
****************************/

class DZ_EXPORT DzActivityLayout : public QObject, public DzRefCountedItem {
	Q_OBJECT
	Q_PROPERTY( QString label READ label WRITE setLabel )
	Q_PROPERTY( QString description READ description WRITE setDescription )
	friend class DzPaneMgr;
private:

	DzActivityLayout( const QDomElement &root );
	~DzActivityLayout();

public:

	DzActivityLayout( const QString &label, const QString &desc );

	void	setLabel( const QString &label );
	void	setDescription( const QString &desc );

public slots:
	void	setToolbarEnabled( const QString &toolbar, bool onOff );

public:
	QString	label() const;
	QString	description() const;

public slots:
	bool	isToolBarEnabled( const QString &toolbar ) const;
	void	clearMemorizedState();

signals:
	void	labelChanged( const QString &label );

private:

	void	memorize( DzMainWindow *iface );
	void	memorizePanes( DzPaneMgr *paneMgr );
	void	memorizeToolBars( DzMainWindow *iface, DzPaneMgr *paneMgr );
	void	memorizePaneGroups( DzPaneMgr *paneMgr );
	void	memorizeViewport( DzViewportMgr *viewMgr );
	void	memorizeActiveViewTool( DzViewportMgr *viewMgr );
	void	memorizeActivityBar( DzActivityBar *activityBar );

	void	restore( DzMainWindow *iface );
	void	restoreToolBars( DzMainWindow *iface, DzPaneMgr *paneMgr );
	void	restorePaneGroups( DzPaneMgr *paneMgr, DzDockedGroupList &dockedPanes );
	void	restorePanes( DzPaneMgr *paneMgr );
	void	restoreViewport( DzViewportMgr *viewMgr );
	void	restoreActiveViewTool( DzViewportMgr *viewMgr );
	void	restoreActivityBar( DzActivityBar *activityBar );

	void	toDOM( QDomDocument &doc, QDomElement &root );
	void	organizeToolBarList();
	void	clearPaneGroups();
	void	clearToolBars();
	void	clearPanes();
	void	setViewports( const QDomElement &root );
	void	setViewportRatios( const QDomElement &root );
	void	normalizeDockWindows( DzMainWindow *iface );

	QString		textEncode( const QByteArray &data );
	QByteArray	textDecode( const QString &text );

	struct	Data;
	Data	*m_data;
};

typedef DzTSharedPointer<DzActivityLayout> DzActivityLayoutPtr;

#endif // DAZ_ACTIVITY_LAYOUT_H
