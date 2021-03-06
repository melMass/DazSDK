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
	Defines the DzPane class.
**/

#ifndef DAZ_PANE_H
#define DAZ_PANE_H

/*****************************
	Include files
*****************************/

#include <QtGui/QWidget>

#include "dzgeneraldefs.h"

/****************************
	Forward declarations
****************************/

class DzActionMenu;
class DzPaneGroup;
class DzPaneSettings;
class DzSkin;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzPane : public QWidget {
	Q_OBJECT
	friend class DzPaneMgr;
	friend class DzPaneGroup;
	friend class DzPaneGroupTabWidget;
public:
	//
	// CREATORS
	//

	DzPane( const QString &name );
	virtual ~DzPane();

public slots:
	//
	// MANIPULATORS
	//

	virtual void	refresh() { }
	void			moveToGroup( DzPaneGroup *group );
	virtual void	restoreSettings( const DzPaneSettings &settings ) { }
	void			restoreSettings( const DzPaneSettings *settings ) { restoreSettings(*settings); }
	void			showPane();
	void			hidePane();
	void			setLabel( const QString &label );

	//
	// ACCESSORS
	//

	DzPaneGroup*	getPaneGroup() const;
	DzActionMenu*	getOptionsMenu() const;
	virtual void	buildOptionsMenu( DzActionMenu *menu ) const { }
	virtual int		getOptionsMenuVersion() const { return 0; }
	virtual void	saveSettings( DzPaneSettings &settings ) const { }
	void			saveSettings( DzPaneSettings *settings ) const { saveSettings(*settings); }
	QString			getLabel() const;
	
	void			setOverrideSkin( DzSkin *skin, bool reReadFromFile = false );
	void			setDefaultSkin( DzSkin *skin );
	DzSkin*			getDefaultSkin() const;
	DzSkin*			getOverrideSkin() const;

	void	refreshStyleSheet(bool reReadFromFile=false);
	void	makeGroupUndockable();
	void	makeUndockable( const QSize &defaultSize = QSize());

signals:

	void	visibilityChanged( bool onOff );
	void	menuChanged();
	void	labelChanged( const QString &newLabel );
	void	tabBarHiddenChanged( bool hidden );

protected:

	virtual void	paintEvent( QPaintEvent *event );
	virtual void	changeEvent( QEvent *event );

	virtual void	showEvent( QShowEvent *e );
	virtual void	hideEvent( QHideEvent *e );

	virtual bool	eventFilter( QObject *obj, QEvent *event );

	void	setOptionsMenu( DzActionMenu *menu );

	void	setBackgroundHeaderGuide( QWidget *guideWidget );
	void	setBackgroundFooterGuide( QWidget *guideWidget );

private slots:
	void	uiLockingChanged();

private:

	void	setGroup( DzPaneGroup *grp );
	void	setupMargins();

	struct	Data;
	Data	*m_data;
};

#endif // DAZ_PANE_H
