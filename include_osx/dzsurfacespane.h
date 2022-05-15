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
	Defines the DzSurfacesPane class.
**/

#ifndef DAZ_SURFACES_PANE_H
#define DAZ_SURFACES_PANE_H

/*****************************
	Include files
*****************************/

#include "dzactionmgr.h"
#include "dzpane.h"
#include "dzsimpleworkflowactions.h"
#include "dzsurfacesidenavhierarchy.h"

/*****************************
	Forward declarations
*****************************/

class DzBakerOptions;
class DzContentTab;
class DzInfoDivider;
class QTabWidget;

/*****************************
	Class definitions
*****************************/
class DZ_EXPORT DzSurfacesPane : public DzPane
{
	Q_OBJECT

public:
	DzSurfacesPane();
	virtual ~DzSurfacesPane();

	virtual DzSurfaceSideNavHierarchy*	getNodeEditor() const;
	QTabWidget*				getTabWidget() const;

public slots:
	void			setDisplayMode(DzSurfaceSideNavHierarchy::DisplayMode mode);
	DzSurfaceSideNavHierarchy::DisplayMode getDisplayMode() const;
	virtual	void	refresh();
	virtual void	showHidden(bool onOff);
	void			toggleShowHidden();
	bool			showingHidden() const;
	void			expandAll();
	void			expandAllSelected();
	void			collapseAll();
	void			collapseAllSelected();

	virtual DzInfoDivider*	getInfoDivider() const;

	DzContentTab*	getContentTab() const;

	void			setCurrentTab(int idx);

	DzGuidePage*	getPresetGuidePage() const;
	DzGuidePage*	getEditorGuidePage() const;

	bool			getAutoBake();
	void			setAutoBake( bool onOff );
	bool			getUseBake();
	void			setUseBake( bool onOff );
	void			refreshBakeTexture();
	DzBakerOptions*	getBakerOption() const;
	void			updateSurfaces();
	void			updateSimpleWorkflowMode( DzSimpleWorkflowMgr::SimpleWorkflowModes mode );

protected:
	void	buildOptionsMenu( DzActionMenu *menu ) const;
	int		getOptionsMenuVersion() const;

	virtual void	restoreSettings( const DzPaneSettings &settings );
	virtual void	saveSettings( DzPaneSettings &settings ) const;

private slots:
	void	tabWidgetChanged(int idx);
	void	updateTip(int idx);
	void	workflowEnabledStateChanged(bool onOff);

signals:
	void	showingHiddenChanged( bool onOff );
	void	editModeChanged( bool onOff );
	void	groupSettingChanged(int mode);
	void	currentTabChanged(int idx);
	void	autoBakeChanged( bool onOff );
	void	useBakeChanged( bool onOff );
	void	displayModeChanged(DzSurfaceSideNavHierarchy::DisplayMode mode);

private:
	struct Data;
	Data *m_data;
};

class DzSurfacesPaneContextMenu : public DzPersistentMenu
{
	Q_OBJECT
public:
	DzSurfacesPaneContextMenu(const QString& name = "Surfaces Pane Context");
	virtual ~DzSurfacesPaneContextMenu();

	virtual void	buildPersistentMenu( DzActionMenu *menu ) const;
	virtual int		getPersistentMenuVersion() const;

public slots:
	DzSurfacesPane*	getPane();

private:
	static DzSurfacesPane		*s_pane;
};

#endif //DAZ_SURFACES_PANE_H
