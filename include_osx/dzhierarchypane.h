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
	Defines the DzHierarchyPane class.
**/

#ifndef DAZ_HIERARCHY_PANE_H
#define DAZ_HIERARCHY_PANE_H

/*****************************
	Include files
*****************************/

#include "dzpane.h"

/****************************
	Forward declarations
****************************/

class DzMenu;
class DzNode;

/*****************************
	Class definitions
*****************************/

class DZ_EXPORT DzHierarchyPane : public DzPane {
	Q_OBJECT
	Q_ENUMS( SortType )
	friend class DzHPShowFiguresAction;
	friend class DzHPShowObjectsAction;
	friend class DzHPShowLightsAction;
	friend class DzHPShowCamerasAction;
	friend class DzHPShowDFormsAction;
	friend class DzHPShowIKAction;
	friend class DzHPShowHiddenAction;
	friend class DzHPTogglePIPAction;
public:
	enum SortType { SortNone, SortAscending, SortDescending };

	//
	// CREATORS
	//

	DzHierarchyPane();
	virtual ~DzHierarchyPane();

public slots:
	virtual void	refresh();

	void	setShowFigures( bool onOff );
	void 	setShowObjects( bool onOff );
	void	setShowLights( bool onOff );
	void	setShowCameras( bool onOff );
	void	setShowIK( bool onOff );
	void	setShowDForms( bool onOff );
	void	setShowHidden( bool onOff );
	void	setParentInPlace( bool onOff );
	void	sort( SortType sortType );
	void	sortNone() { sort( SortNone ); }
	void	sortAscending() { sort( SortAscending ); }
	void	sortDescending() { sort( SortDescending ); }
	void	expandAll();
	void	expandSelected();
	void	closeAll();
	void	closeSelected();

	//
	// ACCESSORS
	//

	bool	showingFigures() const;
	bool 	showingObjects() const;
	bool	showingLights() const;
	bool	showingCameras() const;
	bool	showingDForms() const;
	bool	showingHidden() const;
	bool	showingIK() const;
	bool	parentInPlace() const;

	SortType		sortType() const;

signals:

	void	contextMenuAboutToShow( DzMenu *menu, DzNode *node );
	void	showingFiguresChanged( bool onOff );
	void 	showingObjectsChanged( bool onOff );
	void	showingLightsChanged( bool onOff );
	void	showingCamerasChanged( bool onOff );
	void	showingDFormsChanged( bool onOff );
	void	showingHiddenChanged( bool onOff );
	void	showingIKChanged( bool onOff );
	void	parentInPlaceChanged( bool onOff );
	void	sortingChanged( DzHierarchyPane::SortType sortType );

protected:
	//
	// REIMPLEMENTATIONS
	//

	virtual void	resizeEvent( QResizeEvent *e );
	virtual void	restoreSettings( const DzPaneSettings &settings );
	virtual void	saveSettings( DzPaneSettings &settings ) const;

	void	buildOptionsMenu( DzActionMenu *menu ) const;
	int		getOptionsMenuVersion() const;

private slots:
	void	toggleShowFigures();
	void	toggleShowObjects();
	void	toggleShowLights();
	void	toggleShowCameras();
	void	toggleShowDForms();
	void	toggleShowHidden();
	void	toggleShowIK();
	void	toggleParentInPlace();

private:
	struct	Data;
	Data	*m_data;
};

#endif // DAZ_HIERARCHY_PANE_H
