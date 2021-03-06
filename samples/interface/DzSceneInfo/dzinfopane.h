/**********************************************************************
	Copyright (c) 2002-2020 Daz 3D, Inc. All Rights Reserved.

	This file is part of the Daz Studio SDK.

	This file may be used only in accordance with the Daz Studio SDK
	license provided with the Daz Studio SDK.

	The contents of this file may not be disclosed to third parties,
	copied or duplicated in any form, in whole or in part, without the
	prior written permission of Daz 3D, Inc, except as explicitly
	allowed in the Daz Studio SDK license.

	See http://www.daz3d.com to contact Daz 3D, Inc or for more
	information about the Daz Studio SDK.
**********************************************************************/
#pragma once

/*****************************
	Include files
*****************************/

#include "dzpane.h"
#include "dzaction.h"

/****************************
	Forward declarations
****************************/

class QTextBrowser;

class DzNode;
class DzGeometry;

/*****************************
	Class definitions
*****************************/
/**
	Our new action inherits from DzPaneAction so that it will automatically be
	added to the '&Window/&Panes (Tabs)' menu when the plugin is loaded the first
	time. It also inherits from DzPaneAction so that it will toggle on/off display
	of our pane in the interface.
**/
class DzSceneInfoPaneAction : public DzPaneAction {
	Q_OBJECT
public:

	DzSceneInfoPaneAction() :
		DzPaneAction( "DzSceneInfoPane" ) {}
};


/**
	This class is the interface pane
**/
class DzSceneInfoPane : public DzPane {
	Q_OBJECT
public:

	// Constructor
	DzSceneInfoPane();

	// Destructor
	~DzSceneInfoPane();

public slots:

	// From DzPane
	virtual void	refresh();

private slots:

	// slots for refreshing/redrawing our data
	void			writeSceneStats();

	// slots for blocking/unblocking our refresh functions during file load operations
	void			blockRefresh();
	void			unblockRefresh();

	void			primarySelectionChanged();
	void			sceneChanged();

protected:

	virtual void	showEvent( QShowEvent* e );
	virtual bool	event( QEvent* e );

private:

	void			getNodeInfo( DzNode* node,
						int &numVerts, int &numTris, int &numQuads,
						int &cacheNumVerts, int &cacheNumTris, int &cacheNumQuads );
	void			getQuadAndTriCountForMesh( DzGeometry* geom, int &numQuads, int &numTris );
	void			refreshSelected( DzNode* node );
	void			refreshInternal();

	bool			m_refreshBlocked;
	bool			m_refreshEventPosted;
	bool			m_needSceneUpdate;
	bool			m_needCurrentNodeUpdate;
	QTextBrowser*	m_output;

	//Scene totals for base and cached "Active" meshes
	int				m_totalVerts;
	int				m_totalTris;
	int				m_totalQuads;
	int				m_totalCacheVerts;
	int				m_totalCacheTris;
	int				m_totalCacheQuads;
};

