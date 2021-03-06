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
/*****************************
	Include files
*****************************/
#include "dzinfopane.h"

#include <QtCore/QObject>

#include "dzapp.h"
#include "dzfacetmesh.h"
#include "dzobject.h"
#include "dzscene.h"
#include "dzshape.h"
#include "dzskeleton.h"
#include "dzstyle.h"

#include "dzversion.h"

/****************************
	File static variables
****************************/

static const int c_minWidth = 200;
static const int c_minHeight = 150;

/****************************
	Local Classes
****************************/

/**
	Simple event custom event.  We use this to know to rebuild our information
**/
class DzRefeshSceneInfoEvent: public QEvent {
public:
	DzRefeshSceneInfoEvent():
		QEvent( QEvent::Type( s_type ) )
	{}

	static int s_type;
};

int DzRefeshSceneInfoEvent::s_type = QEvent::registerEventType();

///////////////////////////////////////////////////////////////////////
// DzSceneInfoPane
///////////////////////////////////////////////////////////////////////

/**
**/
DzSceneInfoPane::DzSceneInfoPane() : DzPane( tr( "Scene Info" ) ),
	m_refreshBlocked( false ), m_refreshEventPosted( false ),
	m_needSceneUpdate( true ), m_needCurrentNodeUpdate( true ), //haven't read scene yet so these updates are needed
	m_totalVerts( 0 ), m_totalTris( 0 ), m_totalQuads( 0 ),
	m_totalCacheVerts( 0 ), m_totalCacheTris( 0 ), m_totalCacheQuads( 0 )
{
	// Declarations
	const int margin = style()->pixelMetric( DZ_PM_GeneralMargin );

	// Define the layout for the pane
	QVBoxLayout* mainLyt = new QVBoxLayout();
	mainLyt->setMargin( margin );
	mainLyt->setSpacing( margin );

	// Use a text browser for the output window - this supports basic html/rtf formatting
	m_output = new QTextBrowser();
	m_output->setObjectName( "SceneInfoTxtBrwsr" );
	m_output->setMinimumSize( c_minWidth, c_minHeight );
	mainLyt->addWidget( m_output );

	// Set the layout for the pane
	setLayout( mainLyt );

	// Do an initial update of the scene stats
	refreshInternal();

	// Listen for the node list in the scene to change so that we can update our information
	DzConnect( dzScene, SIGNAL(nodeListChanged()), this, SLOT(sceneChanged()) );

	// Listen for the topology changes in the scene so that we can update our information
	// Note: sceneTopologyChanged() does not exist until 4.6.0.91
	DzConnect( dzScene, SIGNAL(sceneTopologyChanged()), this, SLOT(sceneChanged()) );

	// Listen for the primary selection to change so that we can update our information
	DzConnect( dzScene, SIGNAL(primarySelectionChanged(DzNode*)), this, SLOT(primarySelectionChanged()) );

	// Listen for file load operations so that we can block our refresh function from executing.
	// During a scene load, the node list will change many times - we only want to refresh
	// once at the end of the load, so that we do not slow down the file load.
	DzConnect( dzScene, SIGNAL(sceneLoadStarting()), this, SLOT(blockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneClearStarting()), this, SLOT(blockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneLoaded()), this, SLOT(unblockRefresh()) );
	DzConnect( dzScene, SIGNAL(sceneCleared()), this, SLOT(unblockRefresh()) );

	setMinimumSize( c_minWidth, c_minHeight );
}

/**
**/
DzSceneInfoPane::~DzSceneInfoPane()
{
}

/**
**/
void DzSceneInfoPane::showEvent( QShowEvent* e )
{
	if ( m_refreshEventPosted || m_needSceneUpdate || m_needCurrentNodeUpdate )
	{
		//We didn't update when we were hidden, so post the refresh event now
		m_refreshEventPosted = false;
		refresh();
	}

	QWidget::showEvent( e );
}

/**
**/
bool DzSceneInfoPane::event( QEvent* e )
{
	if ( e->type() == DzRefeshSceneInfoEvent::s_type )
	{
		refreshInternal();
		m_refreshEventPosted = false;
		return true;
	}

	return DzPane::event( e );
}

/**
**/
void DzSceneInfoPane::refresh()
{
	if ( !isVisible() )
		//if the user not viewing this pane, don't update it
	{
		return;
	}

	if ( m_refreshBlocked || m_refreshEventPosted )
		//Event already posted or we are blocking refreshes for a scene load
	{
		return;
	}

	if ( dzApp->isClosing() )
		//Don't post refresh events when the application is closing down
		//it can cause issues/crashes in Qt
	{
		return;
	}

	m_refreshEventPosted = true;
	QApplication::postEvent( this, new DzRefeshSceneInfoEvent() );
}

/**
**/
void DzSceneInfoPane::refreshSelected( DzNode* node )
{
	int tNumVerts = 0, tNumTris = 0, tNumQuads = 0, cNumVerts = 0, cNumTris = 0, cNumQuads = 0;
	QString	html;

	// Write the html output for the scene-wide stats
	writeSceneStats();

	if ( node )
	{
		QLocale locale = QLocale::system();

		// Get the stats for the primary selection
		getNodeInfo( node, tNumVerts, tNumTris, tNumQuads, cNumVerts, cNumTris, cNumQuads );

		// Write the html output for the primary selection stats
		html = "<b>Primary Selection : </b><br/><table>";
		html += QString( "<tr><td>Name : </td><td>%1</td></tr>" ).arg( node->objectName() );
		html += QString( "<tr><td>Label : </td><td>%1</td></tr>" ).arg( node->getLabel() );
		html += QString( "<tr><td>Class : </td><td>%1</td></tr>" ).arg( node->className() );

		html += QString( "<tr><td>Vertices : </td><td><b>%1</b> / %2</td></tr>" )
				.arg( locale.toString( cNumVerts ) ).arg( locale.toString( tNumVerts ) );
		html += QString( "<tr><td>Triangles : </td><td><b>%1</b> / %2</td></tr>" )
				.arg( locale.toString( cNumTris ) ).arg( locale.toString( tNumTris ) );
		html += QString( "<tr><td>Quads : </td><td><b>%1</b> / %2</td></tr>" )
				.arg( locale.toString( cNumQuads ) ).arg( locale.toString( tNumQuads ) );
		html += QString( "<tr><td>Total Faces : </td><td><b>%1</b> / %2</td></tr>" )
				.arg( locale.toString( cNumTris + cNumQuads ) ).arg( locale.toString( tNumTris + tNumQuads ) ); 
	}
	else // No primary selection
	{
		html = "<b>Primary Selection : </b>None<br/>";
	}

	m_output->append( html );
	m_needCurrentNodeUpdate = false;
}

/**
**/
void DzSceneInfoPane::writeSceneStats()
{
	QLocale locale = QLocale::system();

	m_output->clear();

	// Generate the 'Scene Info' table:
	QString html = "<b>Scene Items : </b><br/><table>";
	html += QString( "<tr><td>Nodes : </td><td>%1</td></tr>" )
			.arg( locale.toString( dzScene->getNumNodes() ) );
	html += QString( "<tr><td>Lights : </td><td>%1</td></tr>" )
			.arg( locale.toString( dzScene->getNumLights() ) );
	html += QString( "<tr><td>Cameras : </td><td>%1</td></tr>" )
			.arg( locale.toString( dzScene->getNumCameras() ) );
	html += QString( "<tr><td>World-Space Modifiers : </td><td>%1</td></tr>" )
			.arg( locale.toString( dzScene->getNumWSModifiers() ) );
	html += "</table><br/><br/>";

	// Generate the 'Scene Geometry' table:
	html += "<b>Scene Geometry : <b>Active</b> / Base</b><br/><table>";
	html += QString( "<tr><td>Total Vertices : </td><td><b>%1</b> / %2</td></tr>" )
			.arg( locale.toString( m_totalCacheVerts ) ).arg( locale.toString( m_totalVerts ) );
	html += QString( "<tr><td>Total Triangles : </td><td><b>%1</b> / %2</td></tr>" )
			.arg( locale.toString( m_totalCacheTris ) ).arg( locale.toString( m_totalTris ) );
	html += QString( "<tr><td>Total Quads : </td><td><b>%1</b> / %2</td></tr>" )
			.arg( locale.toString( m_totalCacheQuads ) ).arg( locale.toString( m_totalQuads ) );
	html += QString( "<tr><td>Total Faces : </td><td><b>%1</b> / %2</td></tr>" )
			.arg( locale.toString( m_totalCacheTris + m_totalCacheQuads ) ).arg( locale.toString( m_totalTris + m_totalQuads ) );
	html += "</table><br/><br/>";

	m_output->append( html );
}

/**
**/
void DzSceneInfoPane::blockRefresh()
{
	// A scene file is being loaded - block the refresh functions
	m_refreshBlocked = true;
}

/**
**/
void DzSceneInfoPane::unblockRefresh()
{
	// A scene file just finished loading - unblock the refresh functions,
	// and force an update of our data.
	m_refreshBlocked = false;
	refresh();
}

/**
**/
void DzSceneInfoPane::getNodeInfo( DzNode* node,
	int &numVerts, int &numTris, int &numQuads,
	int &cacheNumVerts, int &cacheNumTris, int &cacheNumQuads
)
{
	// Collect information about the node's geometry
	DzObject* obj = node->getObject();
	DzShape* shape = obj ? obj->getCurrentShape() : NULL;
	DzGeometry* geom = shape ? shape->getGeometry() : NULL;

	numVerts = 0;
	numTris = 0;
	numQuads = 0;
	cacheNumVerts = 0;
	cacheNumTris = 0;
	cacheNumQuads = 0;

	//get values for the base mesh
	if ( geom )
	{
		numVerts = geom->getNumVertices();
		getQuadAndTriCountForMesh( geom, numQuads, numTris );
	}

	//make sure cache geometry is ready
	node->update();
	node->finalize();

	//get values of the cached "Active" mesh
	if ( DzGeometry* cacheMesh = obj ? obj->getCachedGeom() : NULL )
	{
		cacheNumVerts = cacheMesh->getNumVertices();
		getQuadAndTriCountForMesh( cacheMesh, cacheNumQuads, cacheNumTris );
	}
}

/**
**/
void DzSceneInfoPane::getQuadAndTriCountForMesh( DzGeometry* geom, int &numQuads, int &numTris )
{
	DzFacetMesh* mesh = qobject_cast<DzFacetMesh*>( geom );
	if ( mesh )
	{
		const int nFacets = mesh->getNumFacets();

		//Non-subdivision or base meshes need to count tris vs. quads
		DzFacet* facets = mesh->getFacetsPtr();
		for ( int i = 0; i < nFacets; i++ )
		{
			if ( facets[i].isQuad() )
			{
				numQuads++;
			}
			else
			{
				numTris++;
			}
		}
	}
}

/**
**/
void DzSceneInfoPane::refreshInternal()
{
	if ( m_needSceneUpdate )
	{
		int numVerts;
		int numTris;
		int numQuads;
		int cNumVerts;
		int cNumTris;
		int cNumQuads;
		DzNodeListIterator nodeIt( dzScene->nodeListIterator() );

		// Clear out any previous data
		m_output->clear();
		m_totalVerts = 0;
		m_totalTris = 0;
		m_totalQuads = 0;
		m_totalCacheVerts = 0;
		m_totalCacheTris = 0;
		m_totalCacheQuads = 0;

		// Iterate over all the nodes in the scene and collect data for them
		while ( nodeIt.hasNext() )
		{
			getNodeInfo( nodeIt.next(), numVerts, numTris, numQuads, cNumVerts, cNumTris, cNumQuads );
			m_totalVerts += numVerts;
			m_totalTris += numTris;
			m_totalQuads += numQuads;
			m_totalCacheVerts += cNumVerts;
			m_totalCacheTris += cNumTris;
			m_totalCacheQuads += cNumQuads;
		}

		m_needSceneUpdate = false;
	}

	// Collect data for the primary selection
	refreshSelected( dzScene->getPrimarySelection() );
}

/**
**/
void DzSceneInfoPane::primarySelectionChanged()
{
	//do as little work as possible and let the event do the main work
	//mark current node as changed and call refresh
	m_needCurrentNodeUpdate = true;
	refresh();
}

/**
**/
void DzSceneInfoPane::sceneChanged()
{
	//do as little work as possible and let the event do the main work
	//mark scene as changed and call refresh
	m_needSceneUpdate = true;
	refresh();
}

#include "moc_dzinfopane.cpp"
